/* ========================================
 *
 * The following firmware was developed by Cypress Semiconductor
 * This work is licensed under a Creative Commons Attribution 3.0 Unported License.
 * 
 * http://creativecommons.org/licenses/by/3.0/deed.en_US
 * 
 * You are free to:
 * -To Share — to copy, distribute and transmit the work 
 * -To Remix — to adapt the work 
 * -To make commercial use of the work
 *
 * ========================================
 */
/* CY8CKIT-042 Proximity Theremin demo
 * By ANTO
 * Version **
 * Updated 5/22/2013
 * Credit: MAXK's CapSense proximity demo
 * 		MIDI array generation: SUBSYNTH - http://subsynth.sourceforge.net/midinote2freq.html
 *
 * References:
 *  HSV Model: http://www.ncsu.edu/scivis/lessons/colormodels/color_models2.html
 *  Theremin: http://www.ted.com/talks/pamelia_kurstin_plays_the_theremin.html
 *
 * Build your own theremin using the Pioneer Kit!
 * Using MAXK's proximity sensor demo, this project builds a theremin. 
 *
 * Features:
 * - Two proximity sensors: Pitch and volume
 * - Color equivalent of pitch is displayed using the tri-color LEDs
 * - Two modes - continuous pitch and discrete pitch controllable using hardware debounced SW2
 * - Pitch proximity values sent to the bridge control panel (BCP) for debugging 
 * - MIDI note convention used in discrete mode
 * - Range of ~5in with wires as antennae
 *   Range increases dramatically (upto a meter!) with better 'antennae' 
 *   (try large solid metal objects like a metal water bottle or pipe)
 *
 * Connect an unterminated wire to P1[0] and P0[4].
 * Connect a speaker and passives between P2[0] and GND (see schematic tab 'Kit External Connections')
 * SW2, RGB LED is already connected to appropriate pins
 *
 * Connect P4[1] to J11 pin 9 if you want to see proximity counts over UART in BCP.
 *
 * BCP settings:
 *  0. Select the COM port number corresponding to the Pioneer Kit
 *  1. In Tools>Protocol Configuration (RX8(UART)), ensure Bit rate is 115,200, Data Bits 8, Parity None, Stop Bit One
 *  2. In Chart>Variable Settings, set variable 1 to Active, change Name to 'prox', type int
 *  3. In the Editor tab, enter BCP read command: RX8 [h=43] @1prox @0prox
 *  4. Press 'Repeat', and switch to the Chart tab
 */
 
#include <device.h>
#include <LED_RGB.h>
#include <math.h>

extern uint16 CapSense_CSD_SensorSignal[CapSense_CSD_TOTAL_SENSOR_COUNT];

/* Capsense constants */
#define PROX_RANGE_INIT     100
#define UINT16_MAX          65535
#define NOISE_THRESH		5

/* Music constants */
#define PITCH_CUTOFF_THRESHOLD		0x000F
#define VOL_CUTOFF_THRESHOLD		0x0002
#define FREQ_A4						440 /* hz */
#define	NOTES_TO_OCTAVE				12
#define NOTES_TO_JARRING			2
#define	NOTES_TO_THIRD				4
#define ADJ_NOTES_FREQ_MULTIPLIER	1.0595	/* 1.0595^12 = 2 */
#define OCTAVE_FREQ_MULTIPLIER		2
#define DISCRETE_LOWEST_NOTE		50
#define	DISCRETE_NOTE_RANGE			45
#define DISCRETE_HIGHEST_NOTE		(DISCRETE_LOWEST_NOTE + DISCRETE_NOTE_RANGE)

#define PITCH_CLOCK_FREQ			200000	/* khz */ /* NOTE!! This value needs to be changed if the freq of Pitch_Clock is changed on the schematic */

/* globals */
CYBIT discrete = 0;

/* ISR changes play mode from continuous to discrete (toggles discrete) */
CY_ISR(SWITCH_PRESS)
{
	discrete = !discrete; 
}

void main()
{
    /* Variable declaration */
    uint8 x;
	int16 proximityCounts, proximityMax=1, volumeCounts, volumeMax=1, prox_prev, prox_pprev;
	uint16 hue, sat, val=0;
	uint32 tone;
	float midi[127];	 /* holds midi note array */
	float a = FREQ_A4; /* A4 (midi[69]) is 440 hz */
	
    /* Initial delay to allow user to press reset and get away from the sensor */
    CyDelay(2000);

    CyGlobalIntEnable;
	
	/* This for loop sets up all the midi notes, i.e. midi[MIDI_NOTE_NUMBER] = frequency of that note 
	 * Source: http://subsynth.sourceforge.net/midinote2freq.html
	 * A better implementation may be to save these as a macro LUT
	 * Idea: MIDI note numbers sent to the computer could be used to generate music/effects in the computer!
	 */
	for (x=0; x<127; x++)
	{
	   midi[x] = ((float)a/(float)32)*(pow(2,(((float)x-9)/(float)12)));
	}

    /* Start components */
    /* Start LED_RGB module */
    LED_RGB_Start();
	PlayMode_ISR_StartEx(SWITCH_PRESS);
	PWM_Tone_Start();
	PWM_Tone_Mix_Start();
    PWM_Tone_WriteCompare(0);		/* silence */
	PWM_Tone_Mix_WriteCompare(0);	/* silence */

    /* Start CSD proximity sensor */
    CapSense_CSD_Start();
    CapSense_CSD_EnableWidget(CapSense_CSD_SENSOR_PROXIMITYSENSOR0_0__PROX);	/* pitch proximity sensor */
    CapSense_CSD_EnableWidget(CapSense_CSD_SENSOR_PROXIMITYSENSOR1_0__PROX);	/* volume proximity sensor */
	CapSense_CSD_InitializeAllBaselines();
    
    /* Start UART */
    UART_Start();
    /* Send "initial" character over UART */
    UART_UartPutCRLF('I');

    /* Perform initial proximity read to set max and min */
    CapSense_CSD_UpdateEnabledBaselines();    
	/* Start scanning all enabled sensors */
	CapSense_CSD_ScanEnabledWidgets();
    /* Wait for scanning to complete */
	while(CapSense_CSD_IsBusy() != 0);
    
    /* Set initial limits */
    proximityMax = PROX_RANGE_INIT;

    /* Endless loop of proximity updates */
    for(;;)
    {
        /* Read capsense proximity sensor */
        /* Update all baselines */
        CapSense_CSD_UpdateEnabledBaselines();
	    /* Start scanning all enabled sensors */
	    CapSense_CSD_ScanEnabledWidgets();
        /* Wait for scanning to complete */
	    while(CapSense_CSD_IsBusy() != 0);
        
		proximityCounts = CapSense_CSD_SensorSignal[0] - NOISE_THRESH;
        volumeCounts = CapSense_CSD_SensorSignal[1] - NOISE_THRESH ;
		
        /* Floor the counts so no negative values are displayed */
        if(proximityCounts<0)
        {
            proximityCounts=0;
        }
		if(volumeCounts<0)
        {
            volumeCounts=0;
        }

        /* Set new limits if appropriate */
        if(proximityCounts>proximityMax)
        {
            proximityMax = proximityCounts;
        }
		
		/* Set new limits if appropriate */
        if(volumeCounts > volumeMax)
        {
            volumeMax = volumeCounts;
        }
        
        /* Calculate scaled color values and write it */
        hue = ((uint32) proximityCounts)*UINT16_MAX/proximityMax;	// hue indicates pitch
        sat = 65535;												// always want full color saturation
		val = ((uint32) volumeCounts)*UINT16_MAX/volumeMax;			// value (brightness) indicates volume
        
        LED_RGB_SetColorCircleHSV(hue, sat, val);
        
        /* Print the capsense proximity to the UART for reading in Bridge Control Panel */
        /* Read with BCP command "RX8 [h=43] @1prox @0prox" */
        UART_UartPutChar('C');	/* 0x43 is ascii C */
        UART_UartPutChar(proximityCounts>>8);
        UART_UartPutChar(proximityCounts&0xff); 
        /* Delay to keep UART traffic down */
        CyDelay(5);
    	
		/* some FIR (does it really matter?) */		
		tone = (0.2*(float)prox_pprev + 0.6*(float)prox_prev + 0.2*(float)proximityCounts);
		
		/* Only if the volume proximity sensor is above some threshold, then turn on the music! */
		if(volumeCounts < VOL_CUTOFF_THRESHOLD)
		{
			PWM_Tone_WriteCompare(0);
			PWM_Tone_Mix_WriteCompare(0);
		}
		else
		{
			PWM_Tone_WriteCompare(volumeCounts>>4);		/* Scale down the volume for peace of mind */
			PWM_Tone_Mix_WriteCompare(volumeCounts>>4);	/* Scale down the volume for peace of mind */
		}
		
		if(discrete)
		{
			tone = 4*log(1+tone);	/* Multiplier 4 is empirically determined - feel free to play around with it */
			tone = DISCRETE_LOWEST_NOTE + tone%(DISCRETE_NOTE_RANGE); /* don't really want more than DISCRETE_NOTE_RANGE distinguishable notes, starting from midi[DISCRETE_LOWEST_NOTE] */

			PWM_Tone_WritePeriod((float)PITCH_CLOCK_FREQ/midi[tone]);
			PWM_Tone_Mix_WritePeriod((float)PITCH_CLOCK_FREQ/midi[tone + NOTES_TO_OCTAVE]); /* +12 is next octave (an octave contains 12 MIDI notes) */
																				  			/* also try NOTES_TO_JARRING and NOTES_TO_THIRD */
		}
		else
		{
			PWM_Tone_WritePeriod((float)PITCH_CLOCK_FREQ/tone);
			PWM_Tone_Mix_WritePeriod(((float)PITCH_CLOCK_FREQ/tone)/(float)OCTAVE_FREQ_MULTIPLIER); /* mulitplying by 2 gives next octave (an octave is a doubling of frequency */
		}
		
		/* silence if pitch proximity sensor is not activated above threshold */
		if(proximityCounts < PITCH_CUTOFF_THRESHOLD)						   
		{
			PWM_Tone_WriteCompare(0);
			PWM_Tone_Mix_WriteCompare(0);
		}
		
		
		prox_prev = proximityCounts;
		prox_pprev = prox_prev;
	}
}

/* [] END OF FILE */
