/*******************************************************************************
* File Name: PN_N_PWM_L.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
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
#include "PN_N_PWM_L.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        PN_N_PWM_L_PC =   (PN_N_PWM_L_PC & \
                                (uint32)(~(uint32)(PN_N_PWM_L_DRIVE_MODE_IND_MASK << (PN_N_PWM_L_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (PN_N_PWM_L_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: PN_N_PWM_L_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void PN_N_PWM_L_Write(uint8 value) 
{
    uint8 drVal = (uint8)(PN_N_PWM_L_DR & (uint8)(~PN_N_PWM_L_MASK));
    drVal = (drVal | ((uint8)(value << PN_N_PWM_L_SHIFT) & PN_N_PWM_L_MASK));
    PN_N_PWM_L_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: PN_N_PWM_L_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void PN_N_PWM_L_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(PN_N_PWM_L__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: PN_N_PWM_L_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro PN_N_PWM_L_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 PN_N_PWM_L_Read(void) 
{
    return (uint8)((PN_N_PWM_L_PS & PN_N_PWM_L_MASK) >> PN_N_PWM_L_SHIFT);
}


/*******************************************************************************
* Function Name: PN_N_PWM_L_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 PN_N_PWM_L_ReadDataReg(void) 
{
    return (uint8)((PN_N_PWM_L_DR & PN_N_PWM_L_MASK) >> PN_N_PWM_L_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(PN_N_PWM_L_INTSTAT) 

    /*******************************************************************************
    * Function Name: PN_N_PWM_L_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 PN_N_PWM_L_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(PN_N_PWM_L_INTSTAT & PN_N_PWM_L_MASK);
		PN_N_PWM_L_INTSTAT = maskedStatus;
        return maskedStatus >> PN_N_PWM_L_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
