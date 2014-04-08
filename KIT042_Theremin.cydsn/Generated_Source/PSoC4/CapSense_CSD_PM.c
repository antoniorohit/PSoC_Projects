/*******************************************************************************
* File Name: CapSense_CSD_PM.c
* Version 1.11
*
* Description:
*  This file provides Sleep APIs for CapSense CSD Component.
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

CapSense_CSD_BACKUP_STRUCT CapSense_CSD_backup =
{   
    0x00u, /* enableState; */
};


/*******************************************************************************
* Function Name: CapSense_CSD_SaveConfig
********************************************************************************
*
* Summary:
*  Saves customer configuration of CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_backup - used to save component state before enter sleep 
*  mode and none-retention registers.
*
*******************************************************************************/
void CapSense_CSD_SaveConfig(void)
{
	if(CapSense_CSD_CSD_CFG_REG & CapSense_CSD_CSD_CFG_ENABLE)
	{
		CapSense_CSD_backup.enableState = 1u;
	}
}


/*******************************************************************************
* Function Name: CapSense_CSD_Sleep
********************************************************************************
*
* Summary:
*  Disables Active mode power.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_backup - used to save component state before enter sleep 
*  mode.
*
*******************************************************************************/
void CapSense_CSD_Sleep(void)
{
	CapSense_CSD_SaveConfig();
		
	/* Disable interrupt */
	CyIntDisable(CapSense_CSD_ISR_NUMBER);
	
	CapSense_CSD_CSD_CFG_REG &= ~(CapSense_CSD_CSD_CFG_SENSE_EN);
	CapSense_CSD_CSD_CFG_REG &= ~(CapSense_CSD_CSD_CFG_SENSE_COMP_EN);
	CapSense_CSD_CSD_CFG_REG &= ~(CapSense_CSD_CSD_CFG_ENABLE);
	
	/* Disable the Clocks */
    CapSense_CSD_SenseClk_Stop();
    CapSense_CSD_SampleClk_Stop();
	
	/* Clear all sensors */
    CapSense_CSD_ClearSensors();
}


/*******************************************************************************
* Function Name: CapSense_CSD_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores CapSense configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Must be called only after CapSense_CSD_SaveConfig() routine. Otherwise 
*  the component configuration will be overwritten with its initial setting.  
*
* Global Variables:
*  CapSense_CSD_backup - used to save component state before enter sleep 
*  mode and none-retention registers.
*
*******************************************************************************/
void CapSense_CSD_RestoreConfig(void)
{

}
 
 
/*******************************************************************************
* Function Name: CapSense_CSD_Wakeup
********************************************************************************
*
* Summary:
*  Restores CapSense configuration and non-retention register values. 
*  Restores enabled state of component by setting Active mode power template 
*  bits for number of component used within CapSense.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  CapSense_CSD_backup - used to save component state before enter sleep 
*  mode and none-retention registers.
*
*******************************************************************************/
void CapSense_CSD_Wakeup(void)
{
	/* Enable the Clocks */
    CapSense_CSD_SenseClk_Start();
    CapSense_CSD_SampleClk_Start();
    
	/* Restore CapSense Enable state */
    if (CapSense_CSD_backup.enableState != 0u)
    {
        CapSense_CSD_Enable();
    }
}


/* [] END OF FILE */
