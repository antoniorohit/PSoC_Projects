/*******************************************************************************
* File Name: CapSense_CSD.c
* Version 1.11
*
* Description:
*  This file provides the source code of scanning APIs for the CapSense CSD 
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CapSense_CSD.h"

#if(CapSense_CSD_IS_SHIELD_ENABLE)
    #define CapSense_CSD_SHIELD_PORT_NUMBER CapSense_CSD_Shield__PORT
    #define CapSense_CSD_SHIELD_PIN_NUMBER  CapSense_CSD_Shield__SHIFT
#endif /* (CapSense_CSD_IS_SHIELD_ENABLE) */

#if (CapSense_CSD_IS_COMPLEX_SCANSLOTS)
    extern __INLINE void CapSense_CSD_EnableScanSlot(uint8 slot);
    extern __INLINE void CapSense_CSD_DisableScanSlot(uint8 slot);
#else
    #define CapSense_CSD_EnableScanSlot(slot)   CapSense_CSD_EnableSensor(slot)
    #define CapSense_CSD_DisableScanSlot(slot)  CapSense_CSD_DisableSensor(slot)
#endif  /* End CapSense_CSD_IS_COMPLEX_SCANSLOTS */

/* Find next sensor for One Channel design */
uint8 CapSense_CSD_FindNextSensor(uint8 snsIndex);

/* Start and Compete the scan */
void CapSense_CSD_PreScan(uint8 sensor);
void CapSense_CSD_PostScan(uint8 sensor);

extern __INLINE void CapSense_CSD_CmodPrecharge(void);
extern __INLINE void CapSense_CSD_SetScanSlotSettings(uint8 slot);
extern __INLINE void CapSense_CSD_EnableSensor(uint8 sensor);
extern __INLINE void CapSense_CSD_DisableSensor(uint8 sensor);


/* SmartSense functions */
#if (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING)
    uint8 CapSense_CSD_lowLevelTuningDone = 0u;
    extern void CapSense_CSD_AutoTune(void);
#endif /* End (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) */

#if(CapSense_CSD_PRS_OPTIONS != CapSense_CSD__PRS_NONE)
	uint8 CapSense_CSD_prescalersTuningDone = 0u;
#endif /* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_NONE) */

uint8 CapSense_CSD_initVar = 0u;
            
/* Global software variables */
volatile uint8 CapSense_CSD_csv = 0u;            /* CapSense CSD status, control variable */
volatile uint8 CapSense_CSD_sensorIndex = 0u;    /* Index of scannig sensor */

/* Global array of Raw Counts */
uint16 CapSense_CSD_sensorRaw[CapSense_CSD_TOTAL_SENSOR_COUNT] = {0u};

/* Global array of PRS resolutions */
uint32 CapSense_CSD_prsResolutionTbl[CapSense_CSD_TOTAL_SCANSLOT_COUNT] = {0u};

/* Backup variables for trim registers*/

#if (CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK)
	uint8 CapSense_CSD_csdTrim2;   
#else
    uint8 CapSense_CSD_csdTrim1;	
#endif /* (CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK) */


uint8 CapSense_CSD_sensorEnableMask[(((CapSense_CSD_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)] = {
0x0u, };

reg32 * CapSense_CSD_pcTable[] = {
    (reg32 *)CapSense_CSD_Sns__ProximitySensor0_0__PROX__PC, 
    (reg32 *)CapSense_CSD_Sns__ProximitySensor1_0__PROX__PC, 
};

const uint8 CapSense_CSD_portTable[] = {
    CapSense_CSD_Sns__ProximitySensor0_0__PROX__PORT, 
    CapSense_CSD_Sns__ProximitySensor1_0__PROX__PORT, 
};

const uint32 CapSense_CSD_maskTable[] = {
    CapSense_CSD_Sns__ProximitySensor0_0__PROX__MASK, 
    CapSense_CSD_Sns__ProximitySensor1_0__PROX__MASK, 
};

const uint8 CapSense_CSD_pinShiftTbl[] = {
    CapSense_CSD_Sns__ProximitySensor0_0__PROX__SHIFT, 
    CapSense_CSD_Sns__ProximitySensor1_0__PROX__SHIFT, 
};

const uint8 CYCODE CapSense_CSD_idac1Settings[] = {
    120u,120u,
};

const uint8 CYCODE CapSense_CSD_idac2Settings[] = {
    80u,80u,
};

const uint32 CYCODE CapSense_CSD_widgetResolution[] = {
    CapSense_CSD_RESOLUTION_16_BITS,
    CapSense_CSD_RESOLUTION_16_BITS,
};

uint8 CapSense_CSD_Clk1DividerVal = 1u;
uint8 CapSense_CSD_Clk2DividerVal = 12u;

const uint8 CYCODE CapSense_CSD_widgetNumber[] = {
    0u, /* ProximitySensor0__PROX */
    1u, /* ProximitySensor1__PROX */
    
};


reg32* const CapSense_CSD_prtSelTbl[] = {
    ((reg32 *) CYREG_HSIOM_PORT_SEL0),
    ((reg32 *) CYREG_HSIOM_PORT_SEL1),
    ((reg32 *) CYREG_HSIOM_PORT_SEL2),
    ((reg32 *) CYREG_HSIOM_PORT_SEL3),
    ((reg32 *) CYREG_HSIOM_PORT_SEL4)
};

reg32* const CapSense_CSD_prtCfgTbl[] = {
    ((reg32 *) CYREG_PRT0_PC),
    ((reg32 *) CYREG_PRT1_PC),
    ((reg32 *) CYREG_PRT2_PC),
    ((reg32 *) CYREG_PRT3_PC),
    ((reg32 *) CYREG_PRT4_PC)
};

reg32* const CapSense_CSD_prtDRTbl[] = {
    ((reg32 *) CYREG_PRT0_DR),
    ((reg32 *) CYREG_PRT1_DR),
    ((reg32 *) CYREG_PRT2_DR),
    ((reg32 *) CYREG_PRT3_DR),
    ((reg32 *) CYREG_PRT4_DR)
};





/*******************************************************************************
* Function Name: CapSense_CSD_Init
********************************************************************************
*
* Summary:
*  Inits default CapSense configuration provided with customizer that defines 
*  mode of component operations and resets all sensors to an inactive state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_Init(void)
{
	uint32 newRegValue;
#if ( ( CapSense_CSD_MULTIPLE_FREQUENCY_SET ) || (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) )

    uint8 snsNumber;

    for(snsNumber = 0u; snsNumber < CapSense_CSD_TOTAL_SENSOR_COUNT; snsNumber++)  
    {  
        CapSense_CSD_SenseClk_SetDividerValue(CapSense_CSD_senseClkDividerVal[snsNumber]);
        CapSense_CSD_SampleClk_SetDividerValue(CapSense_CSD_sampleClkDividerVal[snsNumber]);
    }
#else
    CapSense_CSD_SenseClk_SetDividerValue(CapSense_CSD_senseClkDividerVal);
    CapSense_CSD_SampleClk_SetDividerValue(CapSense_CSD_sampleClkDividerVal);
#endif /* (CapSense_CSD_MULTIPLE_FREQUENCY_SET) || \
      (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) */
      
    /* Clear all sensors */
    CapSense_CSD_ClearSensors();
    
#if(CapSense_CSD_IS_SHIELD_ENABLE)
    *CapSense_CSD_prtCfgTbl[CapSense_CSD_SHIELD_PORT_NUMBER] &= ~(CapSense_CSD_CSD_PIN_MODE_MASK << (CapSense_CSD_SHIELD_PIN_NUMBER * 3u));
    *CapSense_CSD_prtSelTbl[CapSense_CSD_SHIELD_PORT_NUMBER] &= ~(CapSense_CSD_CSD_HSIOM_MASK << (CapSense_CSD_SHIELD_PIN_NUMBER << 2u));
    *CapSense_CSD_prtSelTbl[CapSense_CSD_SHIELD_PORT_NUMBER] |= (CapSense_CSD_CSD_SHIELD_PORT_MODE << (CapSense_CSD_SHIELD_PIN_NUMBER << 2u));
	
	#if((CapSense_CSD_CSH_TANK_PREGARGE_OPTION == CapSense_CSD__CAPPRIOBUF) || (CapSense_CSD_CSH_TANK_ENABLE))
		CapSense_CSD_PORT_SEL4_REG &= ~(CapSense_CSD_CSD_CTANK_CONNECTION_MASK);
		CapSense_CSD_PORT_SEL4_REG |= CapSense_CSD_CSD_CTANK_TO_AMUXBUS_B;
	#endif /* */
	
	#if(CapSense_CSD_CSH_TANK_PREGARGE_OPTION == CapSense_CSD__CAPPRIOBUF)
		CapSense_CSD_PORT4_PC_REG &= ~(CapSense_CSD_CSD_CTANK_PC_MASK);
		CapSense_CSD_PORT4_PC_REG |= CapSense_CSD_CTANK_PC_STRONG_MODE;
		
		CapSense_CSD_PORT4_DR_REG &= ~(CapSense_CSD_CTANK_DR_MASK);
		CapSense_CSD_PORT4_DR_REG |= CapSense_CSD_CTANK_DR_CONFIG;
	#endif/* (CapSense_CSD_CSH_TANK_PREGARGE_OPTION == CapSense_CSD__CAPPRIOBUF) */

#endif /* (CapSense_CSD_IS_SHIELD_ENABLE) */

    /* Set trim registers for CSD Mode */ 
    #if (CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK)
		/* iDAC1 Sinking Mode */ 
		CapSense_CSD_csdTrim2 = CapSense_CSD_CSD_TRIM2_REG;
		newRegValue = CapSense_CSD_csdTrim2;
		newRegValue &= CapSense_CSD_CSD_IDAC1_TRIM_MASK;
		newRegValue |= (uint32)(CapSense_CSD_SFLASH_CSD_TRIM2_REG & CapSense_CSD_CSFLASH_TRIM_IDAC1_MASK); 
		
		#if (CapSense_CSD_IDAC_CNT == 2u)
		     /* iDAC2 Sinking Mode */ 
			newRegValue &= CapSense_CSD_CSD_IDAC2_TRIM_MASK;
			newRegValue |= (uint32)(CapSense_CSD_SFLASH_CSD_TRIM2_REG & CapSense_CSD_CSFLASH_TRIM_IDAC2_MASK); 
		#endif
		CapSense_CSD_CSD_TRIM2_REG = newRegValue;
    #else   
		/* iDAC1 Sourcing Mode */ 
		CapSense_CSD_csdTrim1 = CapSense_CSD_CSD_TRIM1_REG;
		newRegValue = CapSense_CSD_csdTrim1;
		newRegValue &= CapSense_CSD_CSD_IDAC1_TRIM_MASK;
		newRegValue |= (uint32)(CapSense_CSD_SFLASH_CSD_TRIM1_REG & CapSense_CSD_CSFLASH_TRIM_IDAC1_MASK);
		#if (CapSense_CSD_IDAC_CNT == 2u)
		     /* iDAC2 Sourcing Mode */ 
			newRegValue &= CapSense_CSD_CSD_IDAC2_TRIM_MASK;
			newRegValue |= (uint32)(CapSense_CSD_SFLASH_CSD_TRIM1_REG & CapSense_CSD_CSFLASH_TRIM_IDAC2_MASK);
		#endif		
		CapSense_CSD_CSD_TRIM1_REG = newRegValue;
    #endif /* (CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK) */

    CapSense_CSD_CSD_CFG_REG = CapSense_CSD_DEFAULT_CSD_CONFIG;
    CapSense_CSD_CSD_IDAC_REG = CapSense_CSD_DEFAULT_CSD_IDAC_CONFIG;   
    CapSense_CSD_SetShieldDelay(CapSense_CSD_SHIELD_DELAY ); 

    CapSense_CSD_PORT_SEL4_REG &= ~(CapSense_CSD_CSD_CMOD_CONNECTION_MASK);
    CapSense_CSD_PORT_SEL4_REG |= CapSense_CSD_CSD_CMOD_TO_AMUXBUS_A;
    
    /* Setup ISR */
    CyIntDisable(CapSense_CSD_ISR_NUMBER);
    CyIntSetVector(CapSense_CSD_ISR_NUMBER, CapSense_CSD_ISR);
    CyIntSetPriority(CapSense_CSD_ISR_NUMBER, CapSense_CSD_ISR_PRIORITY);
}


/*******************************************************************************
* Function Name: CapSense_CSD_Enable
********************************************************************************
*
* Summary:
*  Enables active mode power template bits for number of component used within 
*  CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_Enable(void)
{
    /* Enable the Clocks */
    CapSense_CSD_SenseClk_Start();
    CapSense_CSD_SampleClk_Start();
    
	CapSense_CSD_CSD_CFG_REG |= CapSense_CSD_CSD_CFG_ENABLE;
	
    CapSense_CSD_CSD_CFG_REG |= CapSense_CSD_CSD_CFG_SENSE_COMP_EN;
    CapSense_CSD_CSD_CFG_REG |= CapSense_CSD_CSD_CFG_SENSE_EN;

    /* Enable interrupt */
    CyIntEnable(CapSense_CSD_ISR_NUMBER);
	
	CapSense_CSD_CmodPrecharge();
}


/*******************************************************************************
* Function Name: CapSense_CSD_Start
********************************************************************************
*
* Summary:
*  Initializes registers and starts the CSD method of CapSense component. Reset 
*  all sensors to an inactive state. Enables interrupts for sensors scanning.
*  When Auto Tuning (SmartSense) mode is selected the tuning procedure is 
*  applied for all sensors.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_initVar - used to check initial configuration, modified on 
*  first function call.
*  CapSense_CSD_lowLevelTuningDone - used to notify the Tuner GUI that 
*  tuning of scanning parameters are done.
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_CSD_Start(void)
{
    if (CapSense_CSD_initVar == 0u)
    {
        CapSense_CSD_Init();
        CapSense_CSD_initVar = 1u;
    }
    CapSense_CSD_Enable();
    
    /* AutoTunning start */
    #if (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING)
        /* AutoTune by sensor basis */
        CapSense_CSD_AutoTune();
        CapSense_CSD_lowLevelTuningDone = 1u;
	#else
        #if(CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_AUTO)
            CapSense_CSD_Calc_PRS_Resolution();
        #endif /* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_AUTO) */     
    #endif /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) */	
	
	CapSense_CSD_CSD_CFG_REG |= CapSense_CSD_CSD_SENSE_AMUXA;
}


/*******************************************************************************
* Function Name: CapSense_CSD_Stop
********************************************************************************
*
* Summary:
*  Stops the sensors scanner, disables internal interrupts, and resets all 
*  sensors to an inactive state. Disables Active mode power template bits for 
*  number of component used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This function should be called after scans will be completed.
*
*******************************************************************************/
void CapSense_CSD_Stop(void)
{
    /* Disable interrupt */
    CyIntDisable(CapSense_CSD_ISR_NUMBER);

    /* Clear all sensors */
    CapSense_CSD_ClearSensors();

    /* Disable the Clocks */
    CapSense_CSD_SenseClk_Stop();
    CapSense_CSD_SampleClk_Stop();
	
    /* Restore trim registers */ 
    #if (CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK)
		/* iDAC Sinking Mode */ 
		CapSense_CSD_CSD_TRIM2_REG = CapSense_CSD_csdTrim2; 
    #else   
		/* iDAC Sourcing Mode */ 
		CapSense_CSD_CSD_TRIM1_REG = CapSense_CSD_csdTrim1;
    #endif /* (CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK) */
}


/*******************************************************************************
* Function Name: CapSense_CSD_FindNextSensor
********************************************************************************
*
* Summary:
*  Finds next sensor to scan. 
*
* Parameters:
*  snsIndex:  Current index of sensor.
*
* Return:
*  Returns the next sensor index to scan.
*
* Global Variables:
*  CapSense_CSD_sensorEnableMask[ ] - used to store bit masks of enabled 
*  sensors.
*  CapSense_CSD_sensorEnableMask[0] contains the masked bits for sensors 0
*  through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  CapSense_CSD_sensorEnableMask[1] contains the masked bits for sensors 
*  8 through 15 (if needed), and so on.
*    0 - sensor doesn't scan by CapSense_CSD_ScanEnabledWidgets().
*    1 - sensor scans by CapSense_CSD_ScanEnabledWidgets().
*
* Note: 
*  This function has effect on current scanning scanning and should not
*  be used outisde of component.
*
*******************************************************************************/
uint8 CapSense_CSD_FindNextSensor(uint8 snsIndex)
{
    uint8 pos;
    uint8 enMask;
    
    /* Check if sensor enabled */
    do
    {
        /* Proceed with the next sensor */
        snsIndex++;
        if(snsIndex == CapSense_CSD_TOTAL_SENSOR_COUNT)
        {
            break;
        }
        pos = (snsIndex >> 3u);
        enMask = 0x01u << (snsIndex & 0x07u);
    }    
    while((CapSense_CSD_sensorEnableMask[pos] & enMask) == 0u);
    
    return snsIndex;
}


/*******************************************************************************
* Function Name: CapSense_CSD_SetScanSlotSettings
********************************************************************************
*
* Summary:
*  Sets the scan settings of the selected scan slot (sensor or pair of sensors). 
*  The scan settings incorporate IDAC value (for IDAC configurations) for every 
*  sensor and resolution. The resolution is the same for all sensors within 
*  widget.
*
* Parameters:
*  slot:  Scan slot number (sensor or pair of sensors).
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_idacSettings[] - used to store idac value for every sensor.
*  CapSense_CSD_widgetResolution[] - used to store scan resolution of every 
*  widget.
*
*******************************************************************************/
__INLINE void CapSense_CSD_SetScanSlotSettings(uint8 slot)
{
    uint32 newRegisterValue;

	
	/* Set Idac Value */
    newRegisterValue = CapSense_CSD_CSD_IDAC_REG;
    
	newRegisterValue &= ~(CapSense_CSD_CSD_IDAC1_DATA_MASK);
    newRegisterValue |= CapSense_CSD_idac1Settings[slot];
    
    #if (CapSense_CSD_IDAC_CNT == 2u)
        newRegisterValue &= ~(CapSense_CSD_CSD_IDAC2_DATA_MASK);
        newRegisterValue |= (CapSense_CSD_idac2Settings[slot] 
                                           << CapSense_CSD_CSD_IDAC2_DATA_OFFSET);                               
    #endif /* (CapSense_CSD_IDAC_CNT == 2u) */
	
	CapSense_CSD_CSD_IDAC_REG = newRegisterValue;

    #if ( (CapSense_CSD_MULTIPLE_FREQUENCY_SET) || \
          (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) )
		CapSense_CSD_SenseClk_SetDividerValue(CapSense_CSD_senseClkDividerVal[slot]);
		CapSense_CSD_SampleClk_SetDividerValue(CapSense_CSD_sampleClkDividerVal[slot]);
    #else
		CapSense_CSD_SenseClk_SetDividerValue(CapSense_CSD_senseClkDividerVal);
		CapSense_CSD_SampleClk_SetDividerValue(CapSense_CSD_sampleClkDividerVal);
    #endif /* ( (CapSense_CSD_MULTIPLE_FREQUENCY_SET) || \
                (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) )
           */
		   
	#if(CapSense_CSD_PRS_OPTIONS != CapSense_CSD__PRS_NONE)
	
		#if(CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING)
			if(CapSense_CSD_prescalersTuningDone != 0u)
			{
		#endif /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) */
				
				newRegisterValue = CapSense_CSD_CSD_CFG_REG;
				newRegisterValue |= CapSense_CSD_CSD_PRS_SELECT_PRS;
				
				#if(CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_AUTO)

					newRegisterValue &= ~(CapSense_CSD_CSD_PRS_12_BIT);
					newRegisterValue |= CapSense_CSD_prsResolutionTbl[slot];	
				#endif /* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_AUTO) */
				
				CapSense_CSD_CSD_CFG_REG = newRegisterValue;
				
		#if(CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING)	
			}
		#endif /* (CapSense_CSD_PRS_OPTIONS != CapSense_CSD__PRS_NONE) */

	#endif /* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_NONE) */
	
}


/*******************************************************************************
* Function Name: CapSense_CSD_ScanSensor
********************************************************************************
*
* Summary:
*  Sets scan settings and starts scanning a sensor or pair of combined sensors
*  on each channel. If two channels are configured, two sensors may be scanned 
*  at the same time. After scanning is complete the isr copies the measured 
*  sensor raw data to the global array. Use of the isr ensures this function 
*  is non-blocking. Each sensor has a unique number within the sensor array. 
*  This number is assigned by the CapSense customizer in sequence.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_csv - used to provide status and mode of scanning process. 
*  Sets busy status(scan in progress) and mode of scan as single scan.
*  For two channel design the additional bits are set to define if scan a 
*  pair of sensors or single one.
*  CapSense_CSD_sensorIndex - used to store sensor scanning sensor number.
*  Sets to provided sensor argument.
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_CSD_ScanSensor(uint8 sensor)
{
    /* Clears status/control variable and set sensorIndex */
    CapSense_CSD_csv = 0u;
    CapSense_CSD_sensorIndex = sensor;
    
    /* Start of sensor scan */
    CapSense_CSD_csv = (CapSense_CSD_SW_STS_BUSY | CapSense_CSD_SW_CTRL_SINGLE_SCAN);
    CapSense_CSD_PreScan(sensor);
}


/*******************************************************************************
* Function Name: CapSense_CSD_ScanEnableWidgets
********************************************************************************
*
* Summary:
*  Scans all of the enabled widgets. Starts scanning a sensor or pair of sensors 
*  within enabled widget. The isr proceeding scanning next sensor or pair till 
*  all enabled widgets will be scanned. Use of the isr ensures this function is 
*  non-blocking. All widgets are enabled by default except proximity widgets. 
*  Proximity widgets must be manually enabled as their long scan time is 
*  incompatible with fast response desired of other widget types.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_csv - used to provide status and mode of scanning process. 
*  Sets busy status(scan in progress) and clears single scan mode.
*  For two channel design the additional bits are set to define if scan a 
*  pair of sensors or single one. 
*  CapSense_CSD_sensorIndex - used to store sensor scanning sensor number.
*  Sets to 0xFF and provided to function CapSense_CSD_FindNextSensor or
*  CapSense_CSD_FindNextPair, these functions starts with sensor index
*  increment and overflow of uint8 gives desired index 0.
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_CSD_ScanEnabledWidgets(void)
{
    /* Clears status/control variable and set sensorIndex */
    CapSense_CSD_csv = 0u;
    CapSense_CSD_sensorIndex = 0xFFu;
    
    /* Find next sensor */
    CapSense_CSD_sensorIndex = CapSense_CSD_FindNextSensor(CapSense_CSD_sensorIndex);

    /* Check end of scan condition */
    if(CapSense_CSD_sensorIndex < CapSense_CSD_TOTAL_SENSOR_COUNT)
    {
        CapSense_CSD_csv |= CapSense_CSD_SW_STS_BUSY;
        CapSense_CSD_PreScan(CapSense_CSD_sensorIndex);
    }
}


/*******************************************************************************
* Function Name: CapSense_CSD_IsBusy
********************************************************************************
*
* Summary:
*  Returns the state of CapSense component. The 1 means that scanning in 
*  progress and 0 means that scanning is complete.
*
* Parameters:
*  None
*
* Return:
*  Returns the state of scanning. 1 - scanning in progress, 0 - scanning 
*  completed.
*
* Global Variables:
*  CapSense_CSD_csv - used to provide status and mode of scanning process. 
*  Checks the busy status.
*
*******************************************************************************/
uint8 CapSense_CSD_IsBusy(void)
{
    return ((CapSense_CSD_csv & CapSense_CSD_SW_STS_BUSY) == 
             CapSense_CSD_SW_STS_BUSY) ? 1u : 0u;
}


/*******************************************************************************
* Function Name: CapSense_CSD_ReadSensorRaw
********************************************************************************
*
* Summary:
*  Returns scan sensor raw data from the CapSense_CSD_sensorRaw[] array. 
*  Each scan sensor has a unique number within the sensor array. This number 
*  is assigned by the CapSense customizer in sequence.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  Returns current raw data value for defined sensor number.
*
* Global Variables:
*  CapSense_CSD_sensorRaw[] - used to store sensors raw data.
*
*******************************************************************************/
uint16 CapSense_CSD_ReadSensorRaw(uint8 sensor)
{
    return CapSense_CSD_sensorRaw[sensor];
}


/*******************************************************************************
* Function Name: CapSense_CSD_ClearSensors
********************************************************************************
*
* Summary:
*  Resets all sensors to the non-sampling state by sequentially disconnecting
*  all sensors from Analog MUX Bus and putting them to inactive state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_ClearSensors(void)
{
    uint8 i;
   
    for (i = 0u; i < CapSense_CSD_TOTAL_SENSOR_COUNT; i++)
    {
        CapSense_CSD_DisableScanSlot(i);
    }
}


#if (CapSense_CSD_IS_COMPLEX_SCANSLOTS)
    /*******************************************************************************
    * Function Name: CapSense_CSD_EnableScanSlot
    ********************************************************************************
    *
    * Summary:
    *  Configures the selected slot to measure during the next measurement 
    *  cycle. The corresponding pin/pins are set to Analog High-Z mode and 
    *  connected to the Analog Mux Bus. This also enables the comparator function.
    *
    * Parameters:
    *  slot:  Slot number.
    *
    * Return:
    *  None
    *
    * Global Constants:
    *  CapSense_CSD_portTable[]  - used to store the port number that pin 
    *  belongs to for every sensor.
    *  CapSense_CSD_maskTable[]  - used to store the pin within the port for 
    *  every sensor.
    *  CapSense_CSD_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in port and mask table for 
    *  complex sensors.
    *  The bit 7 (msb) is used to define the sensor type: single or complex.
    *
    *******************************************************************************/
    __INLINE void CapSense_CSD_EnableScanSlot(uint8 slot)
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 CYCODE *index;
        /* Read the sensor type: single or complex */
        uint8 snsType = CapSense_CSD_portTable[slot];

        /* Check if sensor is complex */
        if ((snsType & CapSense_CSD_COMPLEX_SS_FLAG) == 0u)
        {
            /* Enable sensor (signle) */
            CapSense_CSD_EnableSensor(slot);
        }
        else
        {
            /* Enable complex sensor */
            snsType &= ~CapSense_CSD_COMPLEX_SS_FLAG;
            index = &CapSense_CSD_indexTable[snsType];
            snsNumber = CapSense_CSD_maskTable[slot];
                        
            for (j=0; j < snsNumber; j++)
            {
                CapSense_CSD_EnableSensor(index[j]);
            }
        } 
    }
    
    
    /*******************************************************************************
    * Function Name: CapSense_CSD_DisableScanSlot
    ********************************************************************************
    *
    * Summary:
    *  Disables the selected slot. The corresponding pin/pis is/are disconnected 
    *  from the Analog Mux Bus and connected to GND, High_Z or Shield electrode.
    *
    * Parameters:
    *  slot:  Slot number.
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  CapSense_CSD_portTable[]  - used to store the port number that pin 
    *  belongs to for every sensor.
    *  CapSense_CSD_maskTable[]  - used to store the pin within the port for 
    *  every sensor.
    *  CapSense_CSD_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in port and mask table for 
    *  complex sensors.
    *  The 7bit(msb) is used to define the sensor type: single or complex.
    *
    *******************************************************************************/
    __INLINE void CapSense_CSD_DisableScanSlot(uint8 slot)
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 CYCODE *index;
        /* Read the sensor type: single or complex */
        uint8 snsType = CapSense_CSD_portTable[slot];
        
        /* Check if sensor is complex */
        if ((snsType & CapSense_CSD_COMPLEX_SS_FLAG) == 0u)
        {
            /* Disable sensor (signle) */
            CapSense_CSD_DisableSensor(slot);
        }
        else
        {
            /* Disable complex sensor */
            snsType &= ~CapSense_CSD_COMPLEX_SS_FLAG;
            index = &CapSense_CSD_indexTable[snsType];
            snsNumber = CapSense_CSD_maskTable[slot];
                        
            for (j=0; j < snsNumber; j++)
            {
                CapSense_CSD_DisableSensor(index[j]);
            }
        } 
    }
#endif  /* CapSense_CSD_IS_COMPLEX_SCANSLOTS */


/*******************************************************************************
* Function Name: CapSense_CSD_EnableSensor
********************************************************************************
*
* Summary:
*  Configures the selected sensor to measure during the next measurement cycle.
*  The corresponding pins are set to Analog High-Z mode and connected to the
*  Analog Mux Bus. This also enables the comparator function.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_portTable[] - used to store the port number that pin 
*  belongs to for every sensor.
*  CapSense_CSD_pinShiftTbl[] - used to store position of pin that 
*  configured as sensor in port. 
*  CapSense_CSD_prtSelTbl[] - Contains pointers to the HSIOM 
*  registers for every port. 
*  CapSense_CSD_PrtCfgTb[] - Contains pointers to the port config 
*  registers for every port.
*
*******************************************************************************/
__INLINE void CapSense_CSD_EnableSensor(uint8 sensor)
{
	uint32 newRegisterValue;
	
    uint32 port = (uint32) CapSense_CSD_portTable[sensor];
    uint8  pinModeShift = CapSense_CSD_pinShiftTbl[sensor]  * 3u;
    uint8  pinHSIOMShift = CapSense_CSD_pinShiftTbl[sensor] * 4u;

	newRegisterValue = *CapSense_CSD_prtSelTbl[port];
	newRegisterValue &= ~(CapSense_CSD_CSD_HSIOM_MASK << pinHSIOMShift);
	newRegisterValue |= (CapSense_CSD_CSD_SENSE_PORT_MODE << pinHSIOMShift);
   
    *CapSense_CSD_prtCfgTbl[port] &= ~(CapSense_CSD_CSD_PIN_MODE_MASK << pinModeShift);
    *CapSense_CSD_prtSelTbl[port] = newRegisterValue;
}


/*******************************************************************************
* Function Name: CapSense_CSD_DisableSensor
********************************************************************************
*
* Summary:
*  Disables the selected sensor. The corresponding pin is disconnected from the
*  Analog Mux Bus and connected to GND, High_Z or Shield electrode.
*
* Parameters:
*  sensor:  Sensor number
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_portTable[] - used to store the port number that pin 
*  belongs to for every sensor.
*  CapSense_CSD_pinShiftTbl[] - used to store position of pin that 
*  configured as sensor in port. 
*  CapSense_CSD_prtSelTbl[] - Contains pointers to the HSIOM 
*  registers for every port. 
*  CapSense_CSD_PrtCfgTb[] - Contains pointers to the port config 
*  registers for every port.
*
*******************************************************************************/
__INLINE void CapSense_CSD_DisableSensor(uint8 sensor)
{
    uint32 port = (uint32) CapSense_CSD_portTable[sensor];
    uint8  pinHSIOMShift = CapSense_CSD_pinShiftTbl[sensor] * 4u;
#if (CapSense_CSD_CONNECT_INACTIVE_SNS != CapSense_CSD__SHIELD)
	uint32 newRegisterValue;
    uint8  pinModeShift = CapSense_CSD_pinShiftTbl[sensor]  * 3u;
#endif

    *CapSense_CSD_prtSelTbl[port] &= ~(CapSense_CSD_CSD_HSIOM_MASK << pinHSIOMShift);
        
#if (CapSense_CSD_CONNECT_INACTIVE_SNS == CapSense_CSD__SHIELD)
    *CapSense_CSD_prtSelTbl[port] |= (CapSense_CSD_CSD_SHIELD_PORT_MODE << pinHSIOMShift);
#else

	newRegisterValue = *CapSense_CSD_prtCfgTbl[port];
	newRegisterValue &= ~(CapSense_CSD_CSD_PIN_MODE_MASK << pinModeShift);
	newRegisterValue |=  (CapSense_CSD_CSD_INACTIVE_CONNECT << pinModeShift);
    *CapSense_CSD_prtCfgTbl[port] =  newRegisterValue;
    
	*CapSense_CSD_prtDRTbl[port]  &=  ~(1u << CapSense_CSD_pinShiftTbl[sensor]);  
    
#endif /* CapSense_CSD_CONNECT_INACTIVE_SNS == CapSense_CSD__SHIELD */
}


/*******************************************************************************
* Function Name: CapSense_CSD_PreScan
********************************************************************************
*
* Summary:
*  Set required settings, enable sensor, remove Vref from AMUX and start the 
*  scanning process of the sensor.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*
*******************************************************************************/
void CapSense_CSD_PreScan(uint8 sensor)
{
    uint8 widget;
    uint8 interruptState;
	uint32 regValue;
    
    interruptState = CyEnterCriticalSection();

    /* Define widget sensor belongs to */
    widget = CapSense_CSD_widgetNumber[sensor];

    /* Set Sensor Settings */
    CapSense_CSD_SetScanSlotSettings(sensor);

    /* Enable Sensor */
    CapSense_CSD_EnableScanSlot(sensor);
	
#if(CapSense_CSD_CMOD_PREGARGE_OPTION == CapSense_CSD__CAPPRIOBUF)
	regValue = CapSense_CSD_PORT_SEL4_REG;
	regValue &= ~(CapSense_CSD_CSD_CMOD_CONNECTION_MASK);
	regValue |= CapSense_CSD_CSD_CMOD_TO_AMUXBUS_A;
	CapSense_CSD_PORT_SEL4_REG = regValue;
	
	regValue = CapSense_CSD_PORT4_PC_REG;
	regValue &= ~(CapSense_CSD_CSD_CMOD_PC_MASK);
	regValue |= CapSense_CSD_CMOD_PC_HIGH_Z_MODE;
	CapSense_CSD_PORT4_PC_REG = regValue;
#endif /* (CapSense_CSD_CMOD_PREGARGE_OPTION == CapSense_CSD__CAPPRIOBUF) */
	
	regValue = CapSense_CSD_CSD_CFG_REG;
	regValue &= ~(CapSense_CSD_PRECHARGE_CONFIG_MASK);
	regValue |= CapSense_CSD_CTANK_PRECHARGE_CONFIG;
	
	CapSense_CSD_CSD_CFG_REG = regValue;
	
#if(CapSense_CSD_PRS_OPTIONS  != CapSense_CSD__PRS_NONE)
	CapSense_CSD_CSD_CFG_REG |= CapSense_CSD_CSD_CFG_PRS_CLEAR;
#endif /* (CapSense_CSD_PRS_OPTIONS  != CapSense_CSD__PRS_NONE) */
    
    CapSense_CSD_CSD_CNT_REG = CapSense_CSD_widgetResolution[widget];
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: CapSense_CSD_PostScan
********************************************************************************
*
* Summary:
*  Store results of measurament in CapSense_CSD_SensorResult[] array,
*  sets scan sensor in none sampling state, turn off Idac(Current Source IDAC),
*  disconnect IDAC(Sink mode) or bleed resistor (Rb) and apply Vref on AMUX.
*  Only one channel designs.
*
* Parameters:
*  sensor:  Sensor number.
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_sensorRaw[] - used to store sensors raw data.
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_CSD_PostScan(uint8 sensor)
{	
	CapSense_CSD_CmodPrecharge();
	
    /* Read SlotResult from Raw Counter */
    CapSense_CSD_sensorRaw[sensor]  = CapSense_CSD_CSD_CNT_REG;
    /* Disable Sensor */
    CapSense_CSD_DisableScanSlot(sensor);
}



/*******************************************************************************
* Function Name: CapSense_CSD_SetShieldDelay
********************************************************************************
*
* Summary:
*  Sets plarity for IDAC2.
*
* Parameters:
*  delay:  shield delya value:
*                               0 - no delay
*                               1 - 1 tact delay
*                               2 - 2 tacts delay
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_SetShieldDelay(uint32 delay)
{
    CapSense_CSD_CSD_CFG_REG &= ~CapSense_CSD_CSD_CFG_SHIELD_DELAY;
    delay &= 0x03u;
    CapSense_CSD_CSD_CFG_REG |= (delay << CapSense_CSD_CSD_CFG_SHIELD_DELAY__POS);
}


/*******************************************************************************
* Function Name: CapSense_CSD_GetResolutionIndex
********************************************************************************
*
* Summary:
*  Recalculating the counter value tu the resolution.
*
* Parameters:
*	sensor: Sensor number.
*
* Return:
*  Returns scanning resolution for the selected sensor.
*
*******************************************************************************/
uint32 CapSense_CSD_GetResolutionIndex(uint32 sensor)
{
	uint32 widgetResolution;
	uint32 result = 0u;
	uint32 mask = 1u;
	
	uint8 widget;
	
	widget = CapSense_CSD_widgetNumber[sensor];
	widgetResolution = CapSense_CSD_widgetResolution[widget];
	
	widgetResolution >>= 16u;
	
	while(widgetResolution & mask)
	{
		result++;
		mask <<= 1u;
	}
	
	return(result);
}


/*******************************************************************************
* Function Name: CapSense_CSD_Calc_PRS_Resolution
********************************************************************************
*
* Summary:
*  Calculates the PRS resolution if the PRS-Auto mode is selected.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void CapSense_CSD_Calc_PRS_Resolution(void)
{
	uint32 curSensor;
	uint32 widgetResolution;
    
    uint8 senseClk;
    uint8 sampleClk;
	
    for(curSensor = 0u; curSensor < CapSense_CSD_TOTAL_SENSOR_COUNT; curSensor++)
	{
    
        #if ( (CapSense_CSD_MULTIPLE_FREQUENCY_SET) || \
              (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) )
            senseClk = CapSense_CSD_senseClkDividerVal[curSensor];
            sampleClk = CapSense_CSD_sampleClkDividerVal[curSensor];
        #else
            senseClk = CapSense_CSD_senseClkDividerVal;
            sampleClk = CapSense_CSD_sampleClkDividerVal;
        #endif /* ( (CapSense_CSD_MULTIPLE_FREQUENCY_SET) || \
                    (CapSense_CSD_TUNING_METHOD == CapSense_CSD_AUTO_TUNING) ) */
        
		if(senseClk > 1u)
		{
			senseClk >>= 1u;
		}
		
		widgetResolution = CapSense_CSD_GetResolutionIndex(curSensor);
		
		if((sampleClk + widgetResolution) > (12u + senseClk))
		{
			CapSense_CSD_prsResolutionTbl[curSensor] = CapSense_CSD_CSD_PRS_12_BIT;
		}
		else
		{
			CapSense_CSD_prsResolutionTbl[curSensor] = CapSense_CSD_CSD_PRS_8_BIT;
		}
	}
}


/*******************************************************************************
* Function Name: CapSense_CSD_CmodPrecharge
********************************************************************************
*
* Summary:
*  This is internal API which precharges the Modulator Capacitor before scan.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
__INLINE void CapSense_CSD_CmodPrecharge(void)
{
	uint32 regValue;
	
	#if(CapSense_CSD_CMOD_PREGARGE_OPTION == CapSense_CSD__CAPPRVREF)	
		uint32 watchdogCounter;
	#endif /* (CapSense_CSD_CMOD_PREGARGE_OPTION == CapSense_CSD__CAPPRVREF) */
	
	#if(CapSense_CSD_CMOD_PREGARGE_OPTION == CapSense_CSD__CAPPRIOBUF)
		regValue = CapSense_CSD_PORT_SEL4_REG;
		regValue &= ~(CapSense_CSD_CSD_CMOD_CONNECTION_MASK);
		regValue |= CapSense_CSD_CSD_CMOD_TO_AMUXBUS_B;
		CapSense_CSD_PORT_SEL4_REG = regValue;
		
		regValue = CapSense_CSD_PORT4_PC_REG;
		regValue &= ~(CapSense_CSD_CSD_CMOD_PC_MASK);
		regValue |= CapSense_CSD_CMOD_PC_STRONG_MODE;
		CapSense_CSD_PORT4_PC_REG = regValue;
			
		CapSense_CSD_PORT4_DR_REG &= ~(CapSense_CSD_CMOD_DR_MASK);
		CapSense_CSD_PORT4_DR_REG |= CapSense_CSD_CMOD_DR_CONFIG;
	#endif /* (CapSense_CSD_CMOD_PREGARGE_OPTION == CapSense_CSD__CAPPRIOBUF) */

		regValue = CapSense_CSD_CSD_CFG_REG;
		regValue &= ~(CapSense_CSD_PRECHARGE_CONFIG_MASK);
		regValue |= CapSense_CSD_CMOD_PRECHARGE_CONFIG;
		CapSense_CSD_CSD_CFG_REG = regValue;

	#if(CapSense_CSD_CMOD_PREGARGE_OPTION == CapSense_CSD__CAPPRVREF)	
		regValue = CapSense_CSD_CSD_IDAC_REG;
		CapSense_CSD_CSD_IDAC_REG = CapSense_CSD_CSD_IDAC_PRECHARGE_CONFIG;
		
	#if(CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK)	
		CapSense_CSD_CSD_CFG_REG &= ~(CapSense_CSD_CSD_CFG_POLARITY);
	#endif /* (CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK) */	
		
		watchdogCounter = CapSense_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM;
		while((0u == (CapSense_CSD_CSD_STAT_REG & CapSense_CSD_CSD_STAT_SAMPLE)) && (0u != watchdogCounter))
	    {
	    	watchdogCounter--;
	    }
		
	#if(CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK)
		CapSense_CSD_CSD_CFG_REG |= (CapSense_CSD_CSD_CFG_POLARITY);
	#endif /* (CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK) */	
		
		CapSense_CSD_CSD_IDAC_REG = regValue;
		
	#endif /* (CapSense_CSD_CMOD_PREGARGE_OPTION == CapSense_CSD__CAPPRVREF) */	
}

/* [] END OF FILE */
