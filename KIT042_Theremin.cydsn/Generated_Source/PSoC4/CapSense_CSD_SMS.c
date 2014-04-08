/*******************************************************************************
* File Name: CapSense_CSD_SMS.c
* Version 1.0
*
* Description:
*  This file provides the source code of wrapper between CapSense CSD component 
*  and Auto Tuning library.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "CapSense_CSD_SMS.h"
#include "CapSense_CSD_CSHL.h"

#include "cytypes.h"

#if (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING)

/* Declaration the sensetivity seed */
#if(CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK)
	#if(CYDEV_VDDA_MV == 5000u)
		#define CapSense_CSD_SENSETIVITY_SEED (4801u)
	#else
		#define CapSense_CSD_SENSETIVITY_SEED (2653u)
	#endif/* (CYDEV_VDDA_MV == 5000u) */
#else
	#define CapSense_CSD_SENSETIVITY_SEED (1156u)
#endif /* (CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK) */

#if(CapSense_CSD_PRS_OPTIONS != CapSense_CSD__PRS_NONE)
	extern uint8 CapSense_CSD_PrescalersTuningDone;
#endif /* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_NONE) */

#define CapSense_CSD_CAL_RAW_COUNT           (1024u)
#define CapSense_CSD_CAL_RAW_COUNT_SPLIT     (1740u)

#if(CYDEV_BCLK__HFCLK__MHZ > 12u)
	#define CapSense_CSD_IDAC2_MAX      (127u)
#elif(CYDEV_BCLK__HFCLK__MHZ > 6u)
	#define CapSense_CSD_IDAC2_MAX      (63u)
#else
	#define CapSense_CSD_IDAC2_MAX      (31u)
#endif /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */

static CapSense_CSD_ConfigType CapSense_CSD_Config;

extern const uint8 CapSense_CSD[];

extern uint16 CapSense_CSD_SensorRaw[];

extern uint32 CapSense_CSD_widgetResolution[];
extern uint8 CapSense_CSD_widgetNumber[];
extern uint8 CapSense_CSD_rawDataIndex[];
extern uint8 CapSense_CSD_numberOfSensors[];
extern uint32 CapSense_CSD_PRSResolutionTbl[];

extern uint8 CapSense_CSD_idac1Settings[];
extern uint8 CapSense_CSD_idac2Settings[];

extern uint8 CapSense_CSD_Clk1DividerVal[];
extern uint8 CapSense_CSD_Clk2DividerVal[];

extern uint16 CapSense_CSD_fingerThreshold[];
extern uint16 CapSense_CSD_noiseThreshold[];
extern uint16 CapSense_CSD_hysteresis[];

uint8 baNoiseEnvelope[CapSense_CSD_TOTAL_SCANSLOT_COUNT]; 
uint8 baRunningDifference[CapSense_CSD_TOTAL_SCANSLOT_COUNT];
uint8 baSignRegister[CapSense_CSD_TOTAL_SCANSLOT_COUNT];
uint16 waSampleMin[CapSense_CSD_TOTAL_SCANSLOT_COUNT];
uint16 waSampleMax[CapSense_CSD_TOTAL_SCANSLOT_COUNT];
uint16 waPreviousSample[CapSense_CSD_TOTAL_SCANSLOT_COUNT];
uint8 baK[CapSense_CSD_TOTAL_SCANSLOT_COUNT];              
uint8 baNoiseResetCounter[CapSense_CSD_TOTAL_SCANSLOT_COUNT];
uint8 waSnsResult[CapSense_CSD_TOTAL_SCANSLOT_COUNT];



/*******************************************************************************
* Function Name: CapSense_CSD_AutoTune
********************************************************************************
*
* Summary:
*  Provides tunning procedure for all sensors.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_AutoTune(void)
{
	uint8 curSensor;
    uint8 widget;
    
    CapSense_CSD_Config.totalScanslotsNum = CapSense_CSD_TOTAL_SCANSLOT_COUNT;
	CapSense_CSD_Config.totalWidgetsNum = CapSense_CSD_END_OF_WIDGETS_INDEX;
    CapSense_CSD_Config.idac1LevelsTbl = CapSense_CSD_idac1Settings;
    CapSense_CSD_Config.idac2LevelsTbl = CapSense_CSD_idac2Settings;
    CapSense_CSD_Config.sensetivityTbl = SMS_LIB_SensorSensitivity;
    CapSense_CSD_Config.chargeDivTbl = CapSense_CSD_Clk1DividerVal;
    CapSense_CSD_Config.modDivTbl = CapSense_CSD_Clk2DividerVal;
    CapSense_CSD_Config.widgetNubmersTbl = CapSense_CSD_widgetNumber;
    CapSense_CSD_Config.resolutionsTbl = CapSense_CSD_widgetResolution;
	CapSense_CSD_Config.rawDataIndex = CapSense_CSD_rawDataIndex;
	CapSense_CSD_Config.numberOfSensors = CapSense_CSD_numberOfSensors; 
    CapSense_CSD_Config.ptrGetRaw = CapSense_CSD_GetSensorRaw;
	CapSense_CSD_Config.IMOFreq_MHz = CYDEV_BCLK__SYSCLK__MHZ;
	CapSense_CSD_Config.sensetivitySeed = CapSense_CSD_SENSETIVITY_SEED;
	
	#if(CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_NONE)	
		CapSense_CSD_Config.prsEn = 0u;
	#else
		CapSense_CSD_Config.prsEn = 1u;
	#endif /* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_NONE) */
	
	CapSense_CSD_SetAnalogSwitchesSrc_Prescaler();
    
    for(curSensor = 0u; curSensor < CapSense_CSD_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        
        widget = CapSense_CSD_widgetNumber[curSensor];
        CapSense_CSD_widgetResolution[widget] = CapSense_CSD_RESOLUTION_11_BITS;
    }
    
    CapSense_CSD_DisableBaselineIDAC();
	
    CalibrateSensors(&CapSense_CSD_Config, CapSense_CSD_CAL_RAW_COUNT);
	
    TunePrescalers(&CapSense_CSD_Config);
	
	#if(CapSense_CSD_PRS_OPTIONS != CapSense_CSD__PRS_NONE)
		CapSense_CSD_PrescalersTuningDone = 1u;
	#endif /* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_NONE) */
	
	CapSense_CSD_NormalizeWidgets(CapSense_CSD_END_OF_WIDGETS_INDEX, CapSense_CSD_Clk1DividerVal);
	
    #if(CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_AUTO)
        CapSense_CSD_Calc_PRS_Resolution();
    #endif/* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_AUTO) */
    
	CapSense_CSD_EnableBaselineIDAC(&CapSense_CSD_Config);
    
    for(curSensor = 0u; curSensor < CapSense_CSD_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        widget = CapSense_CSD_widgetNumber[curSensor];
        
		#if(CapSense_CSD_FRACT_DIVIDERS_ENABLED == 1u)
			CapSense_CSD_widgetResolution[widget] = 0x09D80000;
		#else
			CapSense_CSD_widgetResolution[widget] = CapSense_CSD_RESOLUTION_11_BITS;
		#endif /* (CapSense_CSD_FRACT_DIVIDERS_ENABLED == 1u) */
    }
    
    CalibrateSensors(&CapSense_CSD_Config, CapSense_CSD_CAL_RAW_COUNT_SPLIT);
    
    TuneSensitivity(&CapSense_CSD_Config);
    
    for(curSensor = 0u; curSensor < CapSense_CSD_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        CapSense_CSD_CalculateThresholds(curSensor);
    }
}


/*******************************************************************************
* Function Name: CapSense_CSD_CalculateThresholds
********************************************************************************
*
* Summary:
*  Computes the noise and finger thresholds based on the high frequency noise
*  found in Noise_Calc and the amplitude of the signal from a recent finger
*  press.
*
* Parameters:
*  sensor: Sensor number.
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_CSD_CalculateThresholds(uint8 sensor)
{
	uint32 fingerThleshold;
	uint8 widget;
	
	widget = CapSense_CSD_widgetNumber[sensor];
	
    CalculateThresholds(sensor, CapSense_CSD_SensorRaw, widget, 
                        CapSense_CSD_fingerThreshold, CapSense_CSD_noiseThreshold);
	
	fingerThleshold = CapSense_CSD_fingerThreshold[widget];
	
	if(fingerThleshold < 220u)
	{
		CapSense_CSD_hysteresis[widget] = fingerThleshold >> 3u;
	}
	else if(fingerThleshold <  237u)
	{
		CapSense_CSD_hysteresis[widget] = fingerThleshold >> 4u;
	}
	else if(fingerThleshold <  245u)
	{
		CapSense_CSD_hysteresis[widget] = fingerThleshold >> 5u;
	}
	else if(fingerThleshold <  250)
	{
		CapSense_CSD_hysteresis[widget] = fingerThleshold >> 6u;
	}
	else
	{
		CapSense_CSD_hysteresis[widget] = 0u;
	}                 
}

/*******************************************************************************
* Function Name: CapSense_CSD_DisableBaselineIDAC
********************************************************************************
*
* Summary:
*  Intended to disabling the baselining IDAC. 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_DisableBaselineIDAC(void)
{
	CapSense_CSD_CSD_IDAC_REG &= ~(CapSense_CSD_CSD_IDAC1_MODE_MASK);
    CapSense_CSD_CSD_IDAC_REG &= ~(CapSense_CSD_CSD_IDAC2_MODE_MASK);
    
	CapSense_CSD_CSD_IDAC_REG |= CapSense_CSD_CSD_IDAC1_MODE_VARIABLE;
    CapSense_CSD_CSD_IDAC_REG |= CapSense_CSD_CSD_IDAC2_MODE_OFF;
}

/*******************************************************************************
* Function Name: CapSense_CSD_SetAnalogSwitchesSrc_PRS
********************************************************************************
*
* Summary:
*  Intended to enabling the baselining IDAC. 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void  CapSense_CSD_EnableBaselineIDAC(CapSense_CSD_ConfigType *config)
{
    uint8 curSensor;
    
    for(curSensor = 0u; curSensor < config->totalScanslotsNum; curSensor++)
    {
        config->idac2LevelsTbl[curSensor] = CapSense_CSD_IDAC2_MAX;
    }
    
	CapSense_CSD_CSD_IDAC_REG &= ~(CapSense_CSD_CSD_IDAC1_MODE_MASK);
    CapSense_CSD_CSD_IDAC_REG &= ~(CapSense_CSD_CSD_IDAC2_MODE_MASK);
    
	CapSense_CSD_CSD_IDAC_REG |= CapSense_CSD_CSD_IDAC1_MODE_FIXED;
    CapSense_CSD_CSD_IDAC_REG |= CapSense_CSD_CSD_IDAC2_MODE_VARIABLE;
}

/*******************************************************************************
* Function Name: CapSense_CSD_GetSensorRaw
********************************************************************************
*
* Summary:
*  Intended to updatind and riding uprated raw data from sensor.
*
* Parameters:
*  sensor - Sensor number.
*
* Return:
*  Returns current raw data value for defined sensor number.
*
*******************************************************************************/
uint16  CapSense_CSD_GetSensorRaw(uint8 sensor, uint8 avgSamples)
{
	uint8 curSample;
	uint32 avgVal = 0u;
	
	for(curSample = 0u; curSample < avgSamples; curSample++)
	{
    
		CapSense_CSD_ScanSensor(sensor);
	    while(CapSense_CSD_IsBusy());
		avgVal += CapSense_CSD_ReadSensorRaw(sensor);
	}
    
    return(avgVal / avgSamples);
}

/*******************************************************************************
* Function Name: CapSense_CSD_NormalizeWidgets
********************************************************************************
*
* Summary:
*  Intended to align all parameters of widget to maximum paramrter.
*
* Parameters:
*  widgetsNum - Number of widgets.
*  datsPrt - pointer ro array with widget parameters.	
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_NormalizeWidgets(uint32 widgetsNum, uint8 *dataPtr)
{
	uint32 currentWidget;
	uint32 currentSensor = 0u;
	uint32 lastSensor = 0u;
	uint32 sensorsPerWidget;
	uint32 maxPerWidget;
	
	
	for(currentWidget = 0u; currentWidget < widgetsNum; currentWidget++)
	{
		maxPerWidget = 0u;
		
		sensorsPerWidget = CapSense_CSD_numberOfSensors[currentWidget];
		currentSensor = CapSense_CSD_rawDataIndex[currentWidget];
		lastSensor = currentSensor + sensorsPerWidget;
		
		while(currentSensor < lastSensor)
		{
			if(maxPerWidget < dataPtr[currentSensor])
			{
				maxPerWidget = dataPtr[currentSensor];
			}
			currentSensor++;
		}
		
		currentSensor = CapSense_CSD_rawDataIndex[currentWidget];
		
		while(currentSensor < lastSensor)
		{
			dataPtr[currentSensor] = maxPerWidget;
			currentSensor++;
		}
	}
}


/*******************************************************************************
* Function Name: CapSense_CSD_SetAnalogSwitchesSrc_Prescaler
********************************************************************************
*
* Summary:
*  Intedned to switching charge clock source to prescaler. 
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_SetAnalogSwitchesSrc_Prescaler(void)
{
	CapSense_CSD_CSD_CFG_REG &= ~(CapSense_CSD_CSD_CFG_PRS_SELECT);
}

#endif /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) */

/* [] END OF FILE */
