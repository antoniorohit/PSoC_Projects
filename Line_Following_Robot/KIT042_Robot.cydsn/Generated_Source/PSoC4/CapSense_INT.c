/*******************************************************************************
* File Name: CapSense_INT.c
* Version 1.0
*
* Description:
*  This file provides the source code of Interrupt Service Routine (ISR)
*  for CapSense CSD component.
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

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START CapSense_IsrCH_ISR_intc` */

/* `#END` */

/* Extern functions declarations, Start and Compete the scan */
extern void CapSense_PreScan(uint8 sensor);
extern void CapSense_PostScan(uint8 sensor);

extern uint8 CapSense_FindNextSensor(uint8 snsIndex);
 
/* Global variables and arrays */
extern volatile uint8 CapSense_csv;
extern volatile uint8 CapSense_sensorIndex;


/*******************************************************************************
* Function Name: CapSense_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed when measure window is closed. The measure window 
*  depends on scan resolution parameter of sensor. 
*  The ISR has two modes: 
*   1. Scans single sensor and stores measure result.
*   2. Stores result of current measure and starts next scan till all 
*      enabled sensors will be scanned.
*  This interrupt handler only used in one channel designs.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_csv - used to provide status and mode of scanning process.
*   Mode - single scan or scan of all enabled sensors.
*   Status - scan in progress or ready for new scan.
*  CapSense_sensorIndex - used to store sensor scanning sensor number.
*
* Reentrant:
*  No
*
*******************************************************************************/
CY_ISR(CapSense_ISR)
{
    uint8 interruptState;
    
    interruptState = CyEnterCriticalSection();
    
    CapSense_CSD_INTR_REG = 1u;
    /*  Place your Interrupt code here. */
    /* `#START CapSense_ONE_CHANNEL_IsrCH0_ISR` */

    /* `#END` */

    /* Save results and disable sensor */
    CapSense_PostScan(CapSense_sensorIndex);
            
    if ((CapSense_csv & CapSense_SW_CTRL_SINGLE_SCAN) != 0u)
    {
        CapSense_csv &= ~CapSense_SW_STS_BUSY;
    }
    else
    {
        /* Proceed the scanning */
        CapSense_sensorIndex = CapSense_FindNextSensor(CapSense_sensorIndex);
        
        /* Check end of scan */
        if(CapSense_sensorIndex < CapSense_TOTAL_SENSOR_COUNT)
        {
            CapSense_PreScan(CapSense_sensorIndex);
        }
        else
        {
            CapSense_csv &= ~CapSense_SW_STS_BUSY;
        } 
    }
    CyExitCriticalSection(interruptState);
}

/* [] END OF FILE */
