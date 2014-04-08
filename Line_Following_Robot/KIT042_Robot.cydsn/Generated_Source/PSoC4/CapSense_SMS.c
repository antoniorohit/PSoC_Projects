/*******************************************************************************
* File Name: CapSense_SMS.c
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
#include "CapSense_SMS.h"
#include "CapSense_CSHL.h"

#include "cytypes.h"

#if (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING)

/* Declaration the sensetivity seed */
#if(CapSense_IDAC1_POLARITY == CapSense__IDAC_SINK)
	#if(CYDEV_VDDA_MV == 5000u)
		#define CapSense_SENSETIVITY_SEED (4801u)
	#else
		#define CapSense_SENSETIVITY_SEED (2653u)
	#endif/* (CYDEV_VDDA_MV == 5000u) */
#else
	#define CapSense_SENSETIVITY_SEED (1156u)
#endif /* (CapSense_IDAC1_POLARITY == CapSense__IDAC_SINK) */

#if(CapSense_PRS_OPTIONS != CapSense__PRS_NONE)
	extern uint8 CapSense_PrescalersTuningDone;
#endif /* (CapSense_PRS_OPTIONS == CapSense__PRS_NONE) */

#define CapSense_CAL_RAW_COUNT           (1024u)
#define CapSense_CAL_RAW_COUNT_SPLIT     (1740u)

#if(CYDEV_BCLK__HFCLK__MHZ > 12u)
	#define CapSense_IDAC2_MAX      (127u)
#elif(CYDEV_BCLK__HFCLK__MHZ > 6u)
	#define CapSense_IDAC2_MAX      (63u)
#else
	#define CapSense_IDAC2_MAX      (31u)
#endif /* (CYDEV_BCLK__HFCLK__MHZ > 12u) */

static CapSense_ConfigType CapSense_Config;

extern const uint8 CapSense[];

extern uint16 CapSense_SensorRaw[];

extern uint32 CapSense_widgetResolution[];
extern uint8 CapSense_widgetNumber[];
extern uint8 CapSense_rawDataIndex[];
extern uint8 CapSense_numberOfSensors[];
extern uint32 CapSense_PRSResolutionTbl[];

extern uint8 CapSense_idac1Settings[];
extern uint8 CapSense_idac2Settings[];

extern uint8 CapSense_Clk1DividerVal[];
extern uint8 CapSense_Clk2DividerVal[];

extern uint16 CapSense_fingerThreshold[];
extern uint16 CapSense_noiseThreshold[];
extern uint16 CapSense_hysteresis[];

uint8 baNoiseEnvelope[CapSense_TOTAL_SCANSLOT_COUNT]; 
uint8 baRunningDifference[CapSense_TOTAL_SCANSLOT_COUNT];
uint8 baSignRegister[CapSense_TOTAL_SCANSLOT_COUNT];
uint16 waSampleMin[CapSense_TOTAL_SCANSLOT_COUNT];
uint16 waSampleMax[CapSense_TOTAL_SCANSLOT_COUNT];
uint16 waPreviousSample[CapSense_TOTAL_SCANSLOT_COUNT];
uint8 baK[CapSense_TOTAL_SCANSLOT_COUNT];              
uint8 baNoiseResetCounter[CapSense_TOTAL_SCANSLOT_COUNT];
uint8 waSnsResult[CapSense_TOTAL_SCANSLOT_COUNT];



/*******************************************************************************
* Function Name: CapSense_AutoTune
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
void CapSense_AutoTune(void)
{
	uint8 curSensor;
    uint8 widget;
    
    CapSense_Config.totalScanslotsNum = CapSense_TOTAL_SCANSLOT_COUNT;
	CapSense_Config.totalWidgetsNum = CapSense_END_OF_WIDGETS_INDEX;
    CapSense_Config.idac1LevelsTbl = CapSense_idac1Settings;
    CapSense_Config.idac2LevelsTbl = CapSense_idac2Settings;
    CapSense_Config.sensetivityTbl = SMS_LIB_SensorSensitivity;
    CapSense_Config.chargeDivTbl = CapSense_Clk1DividerVal;
    CapSense_Config.modDivTbl = CapSense_Clk2DividerVal;
    CapSense_Config.widgetNubmersTbl = CapSense_widgetNumber;
    CapSense_Config.resolutionsTbl = CapSense_widgetResolution;
	CapSense_Config.rawDataIndex = CapSense_rawDataIndex;
	CapSense_Config.numberOfSensors = CapSense_numberOfSensors; 
    CapSense_Config.ptrGetRaw = CapSense_GetSensorRaw;
	CapSense_Config.IMOFreq_MHz = CYDEV_BCLK__SYSCLK__MHZ;
	CapSense_Config.sensetivitySeed = CapSense_SENSETIVITY_SEED;
	
	#if(CapSense_PRS_OPTIONS == CapSense__PRS_NONE)	
		CapSense_Config.prsEn = 0u;
	#else
		CapSense_Config.prsEn = 1u;
	#endif /* (CapSense_PRS_OPTIONS == CapSense__PRS_NONE) */
	
	CapSense_SetAnalogSwitchesSrc_Prescaler();
    
    for(curSensor = 0u; curSensor < CapSense_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        
        widget = CapSense_widgetNumber[curSensor];
        CapSense_widgetResolution[widget] = CapSense_RESOLUTION_11_BITS;
    }
    
    CapSense_DisableBaselineIDAC();
	
    CalibrateSensors(&CapSense_Config, CapSense_CAL_RAW_COUNT);
	
    TunePrescalers(&CapSense_Config);
	
	#if(CapSense_PRS_OPTIONS != CapSense__PRS_NONE)
		CapSense_PrescalersTuningDone = 1u;
	#endif /* (CapSense_PRS_OPTIONS == CapSense__PRS_NONE) */
	
	CapSense_NormalizeWidgets(CapSense_END_OF_WIDGETS_INDEX, CapSense_Clk1DividerVal);
	
    #if(CapSense_PRS_OPTIONS == CapSense__PRS_AUTO)
        CapSense_Calc_PRS_Resolution();
    #endif/* (CapSense_PRS_OPTIONS == CapSense__PRS_AUTO) */
    
	CapSense_EnableBaselineIDAC(&CapSense_Config);
    
    for(curSensor = 0u; curSensor < CapSense_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        widget = CapSense_widgetNumber[curSensor];
        
		#if(CapSense_FRACT_DIVIDERS_ENABLED == 1u)
			CapSense_widgetResolution[widget] = 0x09D80000;
		#else
			CapSense_widgetResolution[widget] = CapSense_RESOLUTION_11_BITS;
		#endif /* (CapSense_FRACT_DIVIDERS_ENABLED == 1u) */
    }
    
    CalibrateSensors(&CapSense_Config, CapSense_CAL_RAW_COUNT_SPLIT);
    
    TuneSensitivity(&CapSense_Config);
    
    for(curSensor = 0u; curSensor < CapSense_TOTAL_SCANSLOT_COUNT; curSensor++)
    {
        CapSense_CalculateThresholds(curSensor);
    }
}


/*******************************************************************************
* Function Name: CapSense_CalculateThresholds
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
void CapSense_CalculateThresholds(uint8 sensor)
{
	uint32 fingerThleshold;
	uint8 widget;
	
	widget = CapSense_widgetNumber[sensor];
	
    CalculateThresholds(sensor, CapSense_SensorRaw, widget, 
                        CapSense_fingerThreshold, CapSense_noiseThreshold);
	
	fingerThleshold = CapSense_fingerThreshold[widget];
	
	if(fingerThleshold < 220u)
	{
		CapSense_hysteresis[widget] = fingerThleshold >> 3u;
	}
	else if(fingerThleshold <  237u)
	{
		CapSense_hysteresis[widget] = fingerThleshold >> 4u;
	}
	else if(fingerThleshold <  245u)
	{
		CapSense_hysteresis[widget] = fingerThleshold >> 5u;
	}
	else if(fingerThleshold <  250)
	{
		CapSense_hysteresis[widget] = fingerThleshold >> 6u;
	}
	else
	{
		CapSense_hysteresis[widget] = 0u;
	}                 
}

/*******************************************************************************
* Function Name: CapSense_DisableBaselineIDAC
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
void CapSense_DisableBaselineIDAC(void)
{
	CapSense_CSD_IDAC_REG &= ~(CapSense_CSD_IDAC1_MODE_MASK);
    CapSense_CSD_IDAC_REG &= ~(CapSense_CSD_IDAC2_MODE_MASK);
    
	CapSense_CSD_IDAC_REG |= CapSense_CSD_IDAC1_MODE_VARIABLE;
    CapSense_CSD_IDAC_REG |= CapSense_CSD_IDAC2_MODE_OFF;
}

/*******************************************************************************
* Function Name: CapSense_SetAnalogSwitchesSrc_PRS
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
void  CapSense_EnableBaselineIDAC(CapSense_ConfigType *config)
{
    uint8 curSensor;
    
    for(curSensor = 0u; curSensor < config->totalScanslotsNum; curSensor++)
    {
        config->idac2LevelsTbl[curSensor] = CapSense_IDAC2_MAX;
    }
    
	CapSense_CSD_IDAC_REG &= ~(CapSense_CSD_IDAC1_MODE_MASK);
    CapSense_CSD_IDAC_REG &= ~(CapSense_CSD_IDAC2_MODE_MASK);
    
	CapSense_CSD_IDAC_REG |= CapSense_CSD_IDAC1_MODE_FIXED;
    CapSense_CSD_IDAC_REG |= CapSense_CSD_IDAC2_MODE_VARIABLE;
}

/*******************************************************************************
* Function Name: CapSense_GetSensorRaw
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
uint16  CapSense_GetSensorRaw(uint8 sensor, uint8 avgSamples)
{
	uint8 curSample;
	uint32 avgVal = 0u;
	
	for(curSample = 0u; curSample < avgSamples; curSample++)
	{
    
		CapSense_ScanSensor(sensor);
	    while(CapSense_IsBusy());
		avgVal += CapSense_ReadSensorRaw(sensor);
	}
    
    return(avgVal / avgSamples);
}

/*******************************************************************************
* Function Name: CapSense_NormalizeWidgets
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
void CapSense_NormalizeWidgets(uint32 widgetsNum, uint8 *dataPtr)
{
	uint32 currentWidget;
	uint32 currentSensor = 0u;
	uint32 lastSensor = 0u;
	uint32 sensorsPerWidget;
	uint32 maxPerWidget;
	
	
	for(currentWidget = 0u; currentWidget < widgetsNum; currentWidget++)
	{
		maxPerWidget = 0u;
		
		sensorsPerWidget = CapSense_numberOfSensors[currentWidget];
		currentSensor = CapSense_rawDataIndex[currentWidget];
		lastSensor = currentSensor + sensorsPerWidget;
		
		while(currentSensor < lastSensor)
		{
			if(maxPerWidget < dataPtr[currentSensor])
			{
				maxPerWidget = dataPtr[currentSensor];
			}
			currentSensor++;
		}
		
		currentSensor = CapSense_rawDataIndex[currentWidget];
		
		while(currentSensor < lastSensor)
		{
			dataPtr[currentSensor] = maxPerWidget;
			currentSensor++;
		}
	}
}


/*******************************************************************************
* Function Name: CapSense_SetAnalogSwitchesSrc_Prescaler
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
void CapSense_SetAnalogSwitchesSrc_Prescaler(void)
{
	CapSense_CSD_CFG_REG &= ~(CapSense_CSD_CFG_PRS_SELECT);
}

#endif /* (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) */

/* [] END OF FILE */
