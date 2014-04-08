/*******************************************************************************
* File Name: P0_7_R1.c  
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
#include "P0_7_R1.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        P0_7_R1_PC =   (P0_7_R1_PC & \
                                (uint32)(~(uint32)(P0_7_R1_DRIVE_MODE_IND_MASK << (P0_7_R1_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (P0_7_R1_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: P0_7_R1_Write
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
void P0_7_R1_Write(uint8 value) 
{
    uint8 drVal = (uint8)(P0_7_R1_DR & (uint8)(~P0_7_R1_MASK));
    drVal = (drVal | ((uint8)(value << P0_7_R1_SHIFT) & P0_7_R1_MASK));
    P0_7_R1_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: P0_7_R1_SetDriveMode
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
void P0_7_R1_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(P0_7_R1__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: P0_7_R1_Read
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
*  Macro P0_7_R1_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 P0_7_R1_Read(void) 
{
    return (uint8)((P0_7_R1_PS & P0_7_R1_MASK) >> P0_7_R1_SHIFT);
}


/*******************************************************************************
* Function Name: P0_7_R1_ReadDataReg
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
uint8 P0_7_R1_ReadDataReg(void) 
{
    return (uint8)((P0_7_R1_DR & P0_7_R1_MASK) >> P0_7_R1_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(P0_7_R1_INTSTAT) 

    /*******************************************************************************
    * Function Name: P0_7_R1_ClearInterrupt
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
    uint8 P0_7_R1_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(P0_7_R1_INTSTAT & P0_7_R1_MASK);
		P0_7_R1_INTSTAT = maskedStatus;
        return maskedStatus >> P0_7_R1_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
