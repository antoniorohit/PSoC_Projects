/*******************************************************************************
* File Name: Pitch_Clock.h
* Version 2.10
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Pitch_Clock_H)
#define CY_CLOCK_Pitch_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void Pitch_Clock_Start(void);
void Pitch_Clock_Stop(void);

void Pitch_Clock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Pitch_Clock_GetDividerRegister(void);
uint8  Pitch_Clock_GetFractionalDividerRegister(void);

#define Pitch_Clock_Enable()                         Pitch_Clock_Start()
#define Pitch_Clock_Disable()                        Pitch_Clock_Stop()
#define Pitch_Clock_SetDividerRegister(clkDivider, reset)  \
                        Pitch_Clock_SetFractionalDividerRegister((clkDivider), 0u)
#define Pitch_Clock_SetDivider(clkDivider)           Pitch_Clock_SetDividerRegister((clkDivider), 1u)
#define Pitch_Clock_SetDividerValue(clkDivider)      Pitch_Clock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/

#define Pitch_Clock_DIV_REG    (*(reg32 *)Pitch_Clock__REGISTER)
#define Pitch_Clock_ENABLE_REG Pitch_Clock_DIV_REG

#endif /* !defined(CY_CLOCK_Pitch_Clock_H) */

/* [] END OF FILE */
