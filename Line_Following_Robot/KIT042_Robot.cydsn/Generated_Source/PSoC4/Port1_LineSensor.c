/*******************************************************************************
* File Name: Port1_LineSensor.c  
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
#include "Port1_LineSensor.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Port1_LineSensor_PC =   (Port1_LineSensor_PC & \
                                (uint32)(~(uint32)(Port1_LineSensor_DRIVE_MODE_IND_MASK << (Port1_LineSensor_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Port1_LineSensor_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Port1_LineSensor_Write
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
void Port1_LineSensor_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Port1_LineSensor_DR & (uint8)(~Port1_LineSensor_MASK));
    drVal = (drVal | ((uint8)(value << Port1_LineSensor_SHIFT) & Port1_LineSensor_MASK));
    Port1_LineSensor_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Port1_LineSensor_SetDriveMode
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
void Port1_LineSensor_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Port1_LineSensor__0__SHIFT, mode);
	SetP4PinDriveMode(Port1_LineSensor__1__SHIFT, mode);
	SetP4PinDriveMode(Port1_LineSensor__2__SHIFT, mode);
	SetP4PinDriveMode(Port1_LineSensor__3__SHIFT, mode);
	SetP4PinDriveMode(Port1_LineSensor__4__SHIFT, mode);
	SetP4PinDriveMode(Port1_LineSensor__5__SHIFT, mode);
	SetP4PinDriveMode(Port1_LineSensor__6__SHIFT, mode);
	SetP4PinDriveMode(Port1_LineSensor__7__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Port1_LineSensor_Read
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
*  Macro Port1_LineSensor_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Port1_LineSensor_Read(void) 
{
    return (uint8)((Port1_LineSensor_PS & Port1_LineSensor_MASK) >> Port1_LineSensor_SHIFT);
}


/*******************************************************************************
* Function Name: Port1_LineSensor_ReadDataReg
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
uint8 Port1_LineSensor_ReadDataReg(void) 
{
    return (uint8)((Port1_LineSensor_DR & Port1_LineSensor_MASK) >> Port1_LineSensor_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Port1_LineSensor_INTSTAT) 

    /*******************************************************************************
    * Function Name: Port1_LineSensor_ClearInterrupt
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
    uint8 Port1_LineSensor_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Port1_LineSensor_INTSTAT & Port1_LineSensor_MASK);
		Port1_LineSensor_INTSTAT = maskedStatus;
        return maskedStatus >> Port1_LineSensor_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
