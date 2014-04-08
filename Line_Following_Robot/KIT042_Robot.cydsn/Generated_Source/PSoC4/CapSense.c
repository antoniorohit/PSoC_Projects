/*******************************************************************************
* File Name: CapSense.c
* Version 1.0
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

#include "CapSense.h"

#if(CapSense_IS_SHIELD_ENABLE)
    #define CapSense_SHIELD_PORT_NUMBER CapSense_Shield__PORT
    #define CapSense_SHIELD_PIN_NUMBER  CapSense_Shield__SHIFT
#endif /* (CapSense_IS_SHIELD_ENABLE) */

#if (CapSense_IS_COMPLEX_SCANSLOTS)
    void CapSense_EnableScanSlot(uint8 slot);
    void CapSense_DisableScanSlot(uint8 slot);
#else
    #define CapSense_EnableScanSlot(slot)   CapSense_EnableSensor(slot)
    #define CapSense_DisableScanSlot(slot)  CapSense_DisableSensor(slot)
#endif  /* End CapSense_IS_COMPLEX_SCANSLOTS */

/* Find next sensor for One Channel design */
uint8 CapSense_FindNextSensor(uint8 snsIndex);

/* Start and Compete the scan */
void CapSense_PreScan(uint8 sensor);
void CapSense_PostScan(uint8 sensor);


/* SmartSense functions */
#if (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING)
    uint8 CapSense_lowLevelTuningDone = 0u;
    extern void CapSense_AutoTune(void);
#endif /* End (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) */

#if(CapSense_PRS_OPTIONS != CapSense__PRS_NONE)
	uint8 CapSense_PrescalersTuningDone = 0u;
#endif /* (CapSense_PRS_OPTIONS == CapSense__PRS_NONE) */

uint8 CapSense_initVar = 0u;
            
/* Global software variables */
volatile uint8 CapSense_csv = 0u;            /* CapSense CSD status, control variable */
volatile uint8 CapSense_sensorIndex = 0u;    /* Index of scannig sensor */

/* Global array of Raw Counts */
uint16 CapSense_SensorRaw[CapSense_TOTAL_SENSOR_COUNT] = {0u};

/* Global array of PRS resolutions */
uint32 CapSense_PRSResolutionTbl[CapSense_TOTAL_SCANSLOT_COUNT] = {0u};

uint8 CapSense_SensorEnableMask[(((CapSense_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)] = {
0x0u, };

reg32 * CapSense_pcTable[] = {
    (reg32 *)CapSense_Sns__ProximitySensor_0__PROX__PC, 
};

const uint8 CapSense_portTable[] = {
    CapSense_Sns__ProximitySensor_0__PROX__PORT, 
};

const uint32 CapSense_maskTable[] = {
    CapSense_Sns__ProximitySensor_0__PROX__MASK, 
};

const uint8 CapSense_pinShiftTbl[] = {
    CapSense_Sns__ProximitySensor_0__PROX__SHIFT, 
};

const uint8 CYCODE CapSense_idac1Settings[] = {
    120u,
};

const uint8 CYCODE CapSense_idac2Settings[] = {
    80u,
};

const uint32 CYCODE CapSense_widgetResolution[] = {
    CapSense_RESOLUTION_16_BITS,
};

uint8 CapSense_Clk1DividerVal = 2u;
uint8 CapSense_Clk2DividerVal = 2u;

const uint8 CYCODE CapSense_widgetNumber[] = {
    0u, /* ProximitySensor__PROX */
    
};


reg32* const CYCODE CapSense_PrtSelTbl[] = {
    ((reg32 *) CYREG_HSIOM_PORT_SEL0),
    ((reg32 *) CYREG_HSIOM_PORT_SEL1),
    ((reg32 *) CYREG_HSIOM_PORT_SEL2),
    ((reg32 *) CYREG_HSIOM_PORT_SEL3)
};

reg32* const CYCODE CapSense_PrtCfgTbl[] = {
    ((reg32 *) CYREG_PRT0_PC),
    ((reg32 *) CYREG_PRT1_PC),
    ((reg32 *) CYREG_PRT2_PC),
    ((reg32 *) CYREG_PRT3_PC)
};

reg32* const CYCODE CapSense_PrtDRTbl[] = {
    ((reg32 *) CYREG_PRT0_DR),
    ((reg32 *) CYREG_PRT1_DR),
    ((reg32 *) CYREG_PRT2_DR),
    ((reg32 *) CYREG_PRT3_DR)
};





/*******************************************************************************
* Function Name: CapSense_Init
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
void CapSense_Init(void)
{

#if ( ( CapSense_MULTIPLE_FREQUENCY_SET ) || (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) )

    uint8 snsNumber;

    for(snsNumber = 0u; snsNumber < CapSense_TOTAL_SENSOR_COUNT; snsNumber++)  
    {  
        CapSense_CSD_Clk1_SetDividerValue(CapSense_Clk1DividerVal[snsNumber]);
        CapSense_CSD_Clk2_SetDividerValue(CapSense_Clk2DividerVal[snsNumber]);
    }
#else
    CapSense_CSD_Clk1_SetDividerValue(CapSense_Clk1DividerVal);
    CapSense_CSD_Clk2_SetDividerValue(CapSense_Clk2DividerVal);
#endif /* (CapSense_MULTIPLE_FREQUENCY_SET) || \
      (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) */
      
    /* Clear all sensors */
    CapSense_ClearSensors();
    
#if(CapSense_IS_SHIELD_ENABLE)
    *CapSense_PrtCfgTbl[CapSense_SHIELD_PORT_NUMBER] &= ~(CapSense_CSD_PIN_MODE_MASK << (CapSense_SHIELD_PIN_NUMBER * 3u));
    *CapSense_PrtSelTbl[CapSense_SHIELD_PORT_NUMBER] &= ~(CapSense_CSD_HSIOM_MASK << (CapSense_SHIELD_PIN_NUMBER << 2u));
    *CapSense_PrtSelTbl[CapSense_SHIELD_PORT_NUMBER] |= (CapSense_CSD_SHIELD_PORT_MODE << (CapSense_SHIELD_PIN_NUMBER << 2u));
	
	#if((CapSense_CSH_TANK_PREGARGE_OPTION == CapSense__CAPPRIOBUF) || (CapSense_CSH_TANK_ENABLE))
		CapSense_PORT_SEL4_REG &= ~(CapSense_CSD_CTANK_CONNECTION_MASK);
		CapSense_PORT_SEL4_REG |= CapSense_CSD_CTANK_TO_AMUXBUS_B;
	#endif /* */
	
	#if(CapSense_CSH_TANK_PREGARGE_OPTION == CapSense__CAPPRIOBUF)
		CapSense_PORT4_PC_REG &= ~(CapSense_CSD_CTANK_PC_MASK);
		CapSense_PORT4_PC_REG |= CapSense_CTANK_PC_STRONG_MODE;
		
		CapSense_PORT4_DR_REG &= ~(CapSense_CTANK_DR_MASK);
		CapSense_PORT4_DR_REG |= CapSense_CTANK_DR_CONFIG;
	#endif/* (CapSense_CSH_TANK_PREGARGE_OPTION == CapSense__CAPPRIOBUF) */

#endif /* (CapSense_IS_SHIELD_ENABLE) */
    
    CapSense_CSD_CFG_REG = CapSense_DEFAULT_CSD_CONFIG;
    CapSense_CSD_IDAC_REG = CapSense_DEFAULT_CSD_IDAC_CONFIG;   
    CapSense_SetShieldDelay(CapSense_SHIELD_DELAY ); 

    CapSense_PORT_SEL4_REG &= ~(CapSense_CSD_CMOD_CONNECTION_MASK);
    CapSense_PORT_SEL4_REG |= CapSense_CSD_CMOD_TO_AMUXBUS_A;
    
    /* Setup ISR */
    CyIntDisable(CapSense_ISR_NUMBER);
    CyIntSetVector(CapSense_ISR_NUMBER, CapSense_ISR);
    CyIntSetPriority(CapSense_ISR_NUMBER, CapSense_ISR_PRIORITY);
}


/*******************************************************************************
* Function Name: CapSense_Enable
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
void CapSense_Enable(void)
{
    /* Enable the Clocks */
    CapSense_CSD_Clk1_Start();
    CapSense_CSD_Clk2_Start();
    
	CapSense_CSD_CFG_REG |= CapSense_CSD_CFG_ENABLE;
	
    CapSense_CSD_CFG_REG |= CapSense_CSD_CFG_SENSE_COMP_EN;
    CyDelayUs(100u);
    CapSense_CSD_CFG_REG |= CapSense_CSD_CFG_SENSE_EN;

    /* Enable interrupt */
    CyIntEnable(CapSense_ISR_NUMBER);
}


/*******************************************************************************
* Function Name: CapSense_Start
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
*  CapSense_initVar - used to check initial configuration, modified on 
*  first function call.
*  CapSense_lowLevelTuningDone - used to notify the Tuner GUI that 
*  tuning of scanning parameters are done.
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_Start(void)
{
    if (CapSense_initVar == 0u)
    {
        CapSense_Init();
        CapSense_initVar = 1u;
    }
    CapSense_Enable();
    
    /* AutoTunning start */
    #if (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING)
        /* AutoTune by sensor basis */
        CapSense_AutoTune();
        CapSense_lowLevelTuningDone = 1u;
	#else
        #if(CapSense_PRS_OPTIONS == CapSense__PRS_AUTO)
            CapSense_Calc_PRS_Resolution();
        #endif /* (CapSense_PRS_OPTIONS == CapSense__PRS_AUTO) */     
    #endif /* (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) */	
	
	CapSense_CSD_CFG_REG |= CapSense_CSD_SENSE_AMUXA;
}


/*******************************************************************************
* Function Name: CapSense_Stop
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
void CapSense_Stop(void)
{
    /* Disable interrupt */
    CyIntDisable(CapSense_ISR_NUMBER);

    /* Clear all sensors */
    CapSense_ClearSensors();

    /* Disable the Clocks */
    CapSense_CSD_Clk1_Stop();
    CapSense_CSD_Clk2_Stop();
}


/*******************************************************************************
* Function Name: CapSense_FindNextSensor
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
*  CapSense_SensorEnableMask[ ] - used to store bit masks of enabled 
*  sensors.
*  CapSense_SensorEnableMask[0] contains the masked bits for sensors 0
*  through 7 (sensor 0 is bit 0, sensor 1 is bit 1).
*  CapSense_SensorEnableMask[1] contains the masked bits for sensors 
*  8 through 15 (if needed), and so on.
*    0 - sensor doesn't scan by CapSense_ScanEnabledWidgets().
*    1 - sensor scans by CapSense_ScanEnabledWidgets().
*
* Note: 
*  This function has effect on current scanning scanning and should not
*  be used outisde of component.
*
*******************************************************************************/
uint8 CapSense_FindNextSensor(uint8 snsIndex)
{
    uint8 pos;
    uint8 enMask;
    
    /* Check if sensor enabled */
    do
    {
        /* Proceed with the next sensor */
        snsIndex++;
        if(snsIndex == CapSense_TOTAL_SENSOR_COUNT)
        {
            break;
        }
        pos = (snsIndex >> 3u);
        enMask = 0x01u << (snsIndex & 0x07u);
    }    
    while((CapSense_SensorEnableMask[pos] & enMask) == 0u);
    
    return snsIndex;
}


/*******************************************************************************
* Function Name: CapSense_SetScanSlotSettings
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
*  CapSense_idacSettings[] - used to store idac value for every sensor.
*  CapSense_widgetResolution[] - used to store scan resolution of every 
*  widget.
*
*******************************************************************************/
void CapSense_SetScanSlotSettings(uint8 slot)
{
    uint32 newRegisterValue;

	
	/* Set Idac Value */
    newRegisterValue = CapSense_CSD_IDAC_REG;
    
	newRegisterValue &= ~(CapSense_CSD_IDAC1_DATA_MASK);
    newRegisterValue |= CapSense_idac1Settings[slot];
    
    #if (CapSense_IDAC_CNT == 2u)
        newRegisterValue &= ~(CapSense_CSD_IDAC2_DATA_MASK);
        newRegisterValue |= (CapSense_idac2Settings[slot] 
                                           << CapSense_CSD_IDAC2_DATA_OFFSET);                               
    #endif /* (CapSense_IDAC_CNT == 2u) */
	
	CapSense_CSD_IDAC_REG = newRegisterValue;

    #if ( (CapSense_MULTIPLE_FREQUENCY_SET) || \
          (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) )
		CapSense_CSD_Clk1_SetDividerValue(CapSense_Clk1DividerVal[slot]);
		CapSense_CSD_Clk2_SetDividerValue(CapSense_Clk2DividerVal[slot]);
    #else
		CapSense_CSD_Clk1_SetDividerValue(CapSense_Clk1DividerVal);
		CapSense_CSD_Clk2_SetDividerValue(CapSense_Clk2DividerVal);
    #endif /* ( (CapSense_MULTIPLE_FREQUENCY_SET) || \
                (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) )
           */
		   
	#if(CapSense_PRS_OPTIONS != CapSense__PRS_NONE)
	
		#if(CapSense_TUNING_METHOD == CapSense_AUTO_TUNING)
			if(CapSense_PrescalersTuningDone != 0u)
			{
		#endif /* (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) */
				
				newRegisterValue = CapSense_CSD_CFG_REG;
				newRegisterValue |= CapSense_CSD_PRS_SELECT_PRS;
				
				#if(CapSense_PRS_OPTIONS == CapSense__PRS_AUTO)

					newRegisterValue &= ~(CapSense_CSD_PRS_12_BIT);
					newRegisterValue |= CapSense_PRSResolutionTbl[slot];	
				#endif /* (CapSense_PRS_OPTIONS == CapSense__PRS_AUTO) */
				
				CapSense_CSD_CFG_REG = newRegisterValue;
				
		#if(CapSense_TUNING_METHOD == CapSense_AUTO_TUNING)	
			}
		#endif /* (CapSense_PRS_OPTIONS != CapSense__PRS_NONE) */

	#endif /* (CapSense_PRS_OPTIONS == CapSense__PRS_NONE) */
	
}


/*******************************************************************************
* Function Name: CapSense_ScanSensor
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
*  CapSense_csv - used to provide status and mode of scanning process. 
*  Sets busy status(scan in progress) and mode of scan as single scan.
*  For two channel design the additional bits are set to define if scan a 
*  pair of sensors or single one.
*  CapSense_sensorIndex - used to store sensor scanning sensor number.
*  Sets to provided sensor argument.
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_ScanSensor(uint8 sensor)
{
    /* Clears status/control variable and set sensorIndex */
    CapSense_csv = 0u;
    CapSense_sensorIndex = sensor;
    
    /* Start of sensor scan */
    CapSense_csv = (CapSense_SW_STS_BUSY | CapSense_SW_CTRL_SINGLE_SCAN);
    CapSense_PreScan(sensor);
}


/*******************************************************************************
* Function Name: CapSense_ScanEnableWidgets
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
*  CapSense_csv - used to provide status and mode of scanning process. 
*  Sets busy status(scan in progress) and clears single scan mode.
*  For two channel design the additional bits are set to define if scan a 
*  pair of sensors or single one. 
*  CapSense_sensorIndex - used to store sensor scanning sensor number.
*  Sets to 0xFF and provided to function CapSense_FindNextSensor or
*  CapSense_FindNextPair, these functions starts with sensor index
*  increment and overflow of uint8 gives desired index 0.
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_ScanEnabledWidgets(void)
{
    /* Clears status/control variable and set sensorIndex */
    CapSense_csv = 0u;
    CapSense_sensorIndex = 0xFFu;
    
    /* Find next sensor */
    CapSense_sensorIndex = CapSense_FindNextSensor(CapSense_sensorIndex);

    /* Check end of scan condition */
    if(CapSense_sensorIndex < CapSense_TOTAL_SENSOR_COUNT)
    {
        CapSense_csv |= CapSense_SW_STS_BUSY;
        CapSense_PreScan(CapSense_sensorIndex);
    }
}


/*******************************************************************************
* Function Name: CapSense_IsBusy
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
*  CapSense_csv - used to provide status and mode of scanning process. 
*  Checks the busy status.
*
*******************************************************************************/
uint8 CapSense_IsBusy(void)
{
    return ((CapSense_csv & CapSense_SW_STS_BUSY) == 
             CapSense_SW_STS_BUSY) ? 1u : 0u;
}


/*******************************************************************************
* Function Name: CapSense_ReadSensorRaw
********************************************************************************
*
* Summary:
*  Returns scan sensor raw data from the CapSense_SensorRaw[] array. 
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
*  CapSense_SensorRaw[] - used to store sensors raw data.
*
*******************************************************************************/
uint16 CapSense_ReadSensorRaw(uint8 sensor)
{
    return CapSense_SensorRaw[sensor];
}


/*******************************************************************************
* Function Name: CapSense_ClearSensors
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
void CapSense_ClearSensors(void)
{
    uint8 i;
   
    for (i = 0u; i < CapSense_TOTAL_SENSOR_COUNT; i++)
    {
        CapSense_DisableScanSlot(i);
    }
}


#if (CapSense_IS_COMPLEX_SCANSLOTS)
    /*******************************************************************************
    * Function Name: CapSense_EnableScanSlot
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
    *  CapSense_portTable[]  - used to store the port number that pin 
    *  belongs to for every sensor.
    *  CapSense_maskTable[]  - used to store the pin within the port for 
    *  every sensor.
    *  CapSense_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in port and mask table for 
    *  complex sensors.
    *  The bit 7 (msb) is used to define the sensor type: single or complex.
    *
    *******************************************************************************/
    void CapSense_EnableScanSlot(uint8 slot)
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 CYCODE *index;
        /* Read the sensor type: single or complex */
        uint8 snsType = CapSense_portTable[slot];

        /* Check if sensor is complex */
        if ((snsType & CapSense_COMPLEX_SS_FLAG) == 0u)
        {
            /* Enable sensor (signle) */
            CapSense_EnableSensor(slot);
        }
        else
        {
            /* Enable complex sensor */
            snsType &= ~CapSense_COMPLEX_SS_FLAG;
            index = &CapSense_indexTable[snsType];
            snsNumber = CapSense_maskTable[slot];
                        
            for (j=0; j < snsNumber; j++)
            {
                CapSense_EnableSensor(index[j]);
            }
        } 
    }
    
    
    /*******************************************************************************
    * Function Name: CapSense_DisableScanSlot
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
    *  CapSense_portTable[]  - used to store the port number that pin 
    *  belongs to for every sensor.
    *  CapSense_maskTable[]  - used to store the pin within the port for 
    *  every sensor.
    *  CapSense_indexTable[] - used to store indexes of complex sensors.
    *  The offset and position in this array are stored in port and mask table for 
    *  complex sensors.
    *  The 7bit(msb) is used to define the sensor type: single or complex.
    *
    *******************************************************************************/
    void CapSense_DisableScanSlot(uint8 slot)
    {
        uint8 j;
        uint8 snsNumber;
        const uint8 CYCODE *index;
        /* Read the sensor type: single or complex */
        uint8 snsType = CapSense_portTable[slot];
        
        /* Check if sensor is complex */
        if ((snsType & CapSense_COMPLEX_SS_FLAG) == 0u)
        {
            /* Disable sensor (signle) */
            CapSense_DisableSensor(slot);
        }
        else
        {
            /* Disable complex sensor */
            snsType &= ~CapSense_COMPLEX_SS_FLAG;
            index = &CapSense_indexTable[snsType];
            snsNumber = CapSense_maskTable[slot];
                        
            for (j=0; j < snsNumber; j++)
            {
                CapSense_DisableSensor(index[j]);
            }
        } 
    }
#endif  /* CapSense_IS_COMPLEX_SCANSLOTS */


/*******************************************************************************
* Function Name: CapSense_EnableSensor
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
*  CapSense_portTable[] - used to store the port number that pin 
*  belongs to for every sensor.
*  CapSense_maskTable[] - used to store the pin within the port for 
*  every sensor.
*  CapSense_csTable[]   - used to store the pointers to CAPS_SEL 
*  registers for every port.
*  CapSense_pcTable[]   - used to store the pointers to PC pin 
*  register for every sensor.
*  CapSense_amuxIndex[] - used to store corrected AMUX index when 
*  complex sensors are defeined.
*
*******************************************************************************/
void CapSense_EnableSensor(uint8 sensor)
{
	uint32 newRegisterValue;
	
    uint32 port = (uint32) CapSense_portTable[sensor];
    uint8  pinModeShift = CapSense_pinShiftTbl[sensor]  * 3u;
    uint8  pinHSIOMShift = CapSense_pinShiftTbl[sensor] * 4u;

	newRegisterValue = *CapSense_PrtSelTbl[port];
	newRegisterValue &= ~(CapSense_CSD_HSIOM_MASK << pinHSIOMShift);
	newRegisterValue |= (CapSense_CSD_SENSE_PORT_MODE << pinHSIOMShift);
   
    *CapSense_PrtCfgTbl[port] &= ~(CapSense_CSD_PIN_MODE_MASK << pinModeShift);
    *CapSense_PrtSelTbl[port] = newRegisterValue;
}


/*******************************************************************************
* Function Name: CapSense_DisableSensor
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
*  CapSense_portTable[] - used to store the port number that pin 
*  belongs to for every sensor.
*  CapSense_maskTable[] - used to store the pin within the port for 
*  every sensor.
*  CapSense_csTable[]   - used to store the pointers to CAPS_SEL 
*  registers for every port.
*  CapSense_pcTable[]   - used to store the pointers to PC pin 
*  register for every sensor.
*  CapSense_amuxIndex[] - used to store corrected AMUX index when 
*  complex sensors are defeined.
*
*******************************************************************************/
void CapSense_DisableSensor(uint8 sensor)
{
    uint32 port = (uint32) CapSense_portTable[sensor];
    uint8  pinHSIOMShift = CapSense_pinShiftTbl[sensor] * 4u;
#if (CapSense_CONNECT_INACTIVE_SNS != CapSense__SHIELD)
	uint32 newRegisterValue;
    uint8  pinModeShift = CapSense_pinShiftTbl[sensor]  * 3u;
#endif    


    *CapSense_PrtSelTbl[port] &= ~(CapSense_CSD_HSIOM_MASK << pinHSIOMShift);
        
#if (CapSense_CONNECT_INACTIVE_SNS == CapSense__SHIELD)
    *CapSense_PrtSelTbl[port] |= (CapSense_CSD_SHIELD_PORT_MODE << pinHSIOMShift);
#else

	newRegisterValue = *CapSense_PrtCfgTbl[port];
	newRegisterValue &= ~(CapSense_CSD_PIN_MODE_MASK << pinModeShift);
	newRegisterValue |=  (CapSense_CSD_INACTIVE_CONNECT << pinModeShift);
    *CapSense_PrtCfgTbl[port] =  newRegisterValue;
    
	*CapSense_PrtDRTbl[port]  &=  ~(1u << CapSense_pinShiftTbl[sensor]);  
    
#endif /* CapSense_CONNECT_INACTIVE_SNS == CapSense__SHIELD */
}


/*******************************************************************************
* Function Name: CapSense_PreScan
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
void CapSense_PreScan(uint8 sensor)
{
    uint8 widget;
    uint8 interruptState;
	uint32 newRegisterValue;
    
    interruptState = CyEnterCriticalSection();

    /* Define widget sensor belongs to */
    widget = CapSense_widgetNumber[sensor];

    /* Set Sensor Settings */
    CapSense_SetScanSlotSettings(sensor);

    /* Enable Sensor */
    CapSense_EnableScanSlot(sensor);
	
#if(CapSense_CMOD_PREGARGE_OPTION == CapSense__CAPPRIOBUF)
	CapSense_PORT4_PC_REG &= ~(CapSense_CSD_CMOD_PC_MASK);
	CapSense_PORT4_PC_REG |= CapSense_CMOD_PC_STRONG_MODE;
	
	CapSense_PORT4_DR_REG &= ~(CapSense_CMOD_DR_MASK);
	CapSense_PORT4_DR_REG |= CapSense_CMOD_DR_CONFIG;
#endif /* (CapSense_CMOD_PREGARGE_OPTION == CapSense__CAPPRIOBUF) */

	newRegisterValue = CapSense_CSD_CFG_REG;
	newRegisterValue &= ~(CapSense_PRECHARGE_CONFIG_MASK);
	newRegisterValue |= CapSense_CMOD_PRECHARGE_CONFIG;
	CapSense_CSD_CFG_REG = newRegisterValue;
	
	CyDelayUs(MAX_CHARGE_TIME_US);
	
#if(CapSense_CMOD_PREGARGE_OPTION == CapSense__CAPPRIOBUF)
	CapSense_PORT4_PC_REG &= ~(CapSense_CSD_CMOD_PC_MASK);
	CapSense_PORT4_PC_REG |= CapSense_CMOD_PC_HIGH_Z_MODE;
#endif /* (CapSense_CMOD_PREGARGE_OPTION == CapSense__CAPPRIOBUF) */
	
	newRegisterValue = CapSense_CSD_CFG_REG;
	newRegisterValue &= ~(CapSense_PRECHARGE_CONFIG_MASK);
	newRegisterValue |= CapSense_CTANK_PRECHARGE_CONFIG;
	CapSense_CSD_CFG_REG = newRegisterValue;
	
#if(CapSense_PRS_OPTIONS  != CapSense__PRS_NONE)
	CapSense_CSD_CFG_REG |= CapSense_CSD_CFG_PRS_CLEAR;
#endif /* (CapSense_PRS_OPTIONS  != CapSense__PRS_NONE) */
	
	CapSense_CSD_Clk1_Stop();
    CapSense_CSD_Clk2_Stop();
	
	CapSense_CSD_Clk1_Start();
    CapSense_CSD_Clk2_Start();
	
	CyDelayUs(10u);
    
    CapSense_CSD_CNT_REG = CapSense_widgetResolution[widget];
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: CapSense_PostScan
********************************************************************************
*
* Summary:
*  Store results of measurament in CapSense_SensorResult[] array,
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
*  CapSense_SensorRaw[] - used to store sensors raw data.
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_PostScan(uint8 sensor)
{
   
    /* Read SlotResult from Raw Counter */
    CapSense_SensorRaw[sensor]  = CapSense_CSD_CNT_REG;
    /* Disable Sensor */
    CapSense_DisableScanSlot(sensor);
}



/*******************************************************************************
* Function Name: CapSense_SetShieldDelay
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
void CapSense_SetShieldDelay(uint32 delay)
{
    CapSense_CSD_CFG_REG &= ~CapSense_CSD_CFG_SHIELD_DELAY;
    delay &= 0x03u;
    CapSense_CSD_CFG_REG |= (delay << CapSense_CSD_CFG_SHIELD_DELAY__POS);
}


/*******************************************************************************
* Function Name: CapSense_GetResolutionIndex
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
uint32 CapSense_GetResolutionIndex(uint32 sensor)
{
	uint32 widgetResolution;
	uint32 result = 0u;
	uint32 mask = 1u;
	
	uint8 widget;
	
	widget = CapSense_widgetNumber[sensor];
	widgetResolution = CapSense_widgetResolution[widget];
	
	widgetResolution >>= 16u;
	
	while(widgetResolution & mask)
	{
		result++;
		mask <<= 1u;
	}
	
	return(result);
}


/*******************************************************************************
* Function Name: CapSense_Calc_PRS_Resolution
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
void CapSense_Calc_PRS_Resolution(void)
{
	uint32 curSensor;
	uint32 widgetResolution;
    
    uint8 senseClk;
    uint8 sampleClk;
	
    for(curSensor = 0u; curSensor < CapSense_TOTAL_SENSOR_COUNT; curSensor++)
	{
    
        #if ( (CapSense_MULTIPLE_FREQUENCY_SET) || \
              (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) )
            senseClk = CapSense_Clk1DividerVal[curSensor];
            sampleClk = CapSense_Clk2DividerVal[curSensor];
        #else
            senseClk = CapSense_Clk1DividerVal;
            sampleClk = CapSense_Clk2DividerVal;
        #endif /* ( (CapSense_MULTIPLE_FREQUENCY_SET) || \
                    (CapSense_TUNING_METHOD == CapSense_AUTO_TUNING) ) */
        
		if(senseClk > 1u)
		{
			senseClk >>= 1u;
		}
		
		widgetResolution = CapSense_GetResolutionIndex(curSensor);
		
		if((sampleClk + widgetResolution) > (12u + senseClk))
		{
			CapSense_PRSResolutionTbl[curSensor] = CapSense_CSD_PRS_12_BIT;
		}
		else
		{
			CapSense_PRSResolutionTbl[curSensor] = CapSense_CSD_PRS_8_BIT;
		}
	}
}

/* [] END OF FILE */
