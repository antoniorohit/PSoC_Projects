/*******************************************************************************
* File Name: PWM_Tone_PM.c
* Version 3.0
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "PWM_Tone.h"

static PWM_Tone_backupStruct PWM_Tone_backup;


/*******************************************************************************
* Function Name: PWM_Tone_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_Tone_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PWM_Tone_SaveConfig(void) 
{
    
    #if(!PWM_Tone_UsingFixedFunction)
        #if(!PWM_Tone_PWMModeIsCenterAligned)
            PWM_Tone_backup.PWMPeriod = PWM_Tone_ReadPeriod();
        #endif /* (!PWM_Tone_PWMModeIsCenterAligned) */
        PWM_Tone_backup.PWMUdb = PWM_Tone_ReadCounter();
        #if (PWM_Tone_UseStatus)
            PWM_Tone_backup.InterruptMaskValue = PWM_Tone_STATUS_MASK;
        #endif /* (PWM_Tone_UseStatus) */
        
        #if(PWM_Tone_DeadBandMode == PWM_Tone__B_PWM__DBM_256_CLOCKS || \
            PWM_Tone_DeadBandMode == PWM_Tone__B_PWM__DBM_2_4_CLOCKS)
            PWM_Tone_backup.PWMdeadBandValue = PWM_Tone_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */
        
        #if(PWM_Tone_KillModeMinTime)
             PWM_Tone_backup.PWMKillCounterPeriod = PWM_Tone_ReadKillTime();
        #endif /* (PWM_Tone_KillModeMinTime) */
        
        #if(PWM_Tone_UseControl)
            PWM_Tone_backup.PWMControlRegister = PWM_Tone_ReadControlRegister();
        #endif /* (PWM_Tone_UseControl) */
    #endif  /* (!PWM_Tone_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Tone_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_Tone_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Tone_RestoreConfig(void) 
{
        #if(!PWM_Tone_UsingFixedFunction)
            #if(!PWM_Tone_PWMModeIsCenterAligned)
                PWM_Tone_WritePeriod(PWM_Tone_backup.PWMPeriod);
            #endif /* (!PWM_Tone_PWMModeIsCenterAligned) */
            PWM_Tone_WriteCounter(PWM_Tone_backup.PWMUdb);
            #if (PWM_Tone_UseStatus)
                PWM_Tone_STATUS_MASK = PWM_Tone_backup.InterruptMaskValue;
            #endif /* (PWM_Tone_UseStatus) */
            
            #if(PWM_Tone_DeadBandMode == PWM_Tone__B_PWM__DBM_256_CLOCKS || \
                PWM_Tone_DeadBandMode == PWM_Tone__B_PWM__DBM_2_4_CLOCKS)
                PWM_Tone_WriteDeadTime(PWM_Tone_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            #if(PWM_Tone_KillModeMinTime)
                PWM_Tone_WriteKillTime(PWM_Tone_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Tone_KillModeMinTime) */
            
            #if(PWM_Tone_UseControl)
                PWM_Tone_WriteControlRegister(PWM_Tone_backup.PWMControlRegister); 
            #endif /* (PWM_Tone_UseControl) */
        #endif  /* (!PWM_Tone_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Tone_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_Tone_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Tone_Sleep(void) 
{
    #if(PWM_Tone_UseControl)
        if(PWM_Tone_CTRL_ENABLE == (PWM_Tone_CONTROL & PWM_Tone_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Tone_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Tone_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Tone_UseControl) */

    /* Stop component */
    PWM_Tone_Stop();
    
    /* Save registers configuration */
    PWM_Tone_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Tone_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_Tone_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Tone_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Tone_RestoreConfig();
    
    if(PWM_Tone_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Tone_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
