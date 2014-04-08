/*******************************************************************************
* File Name: Clock_QuadDec.h
* Version 2.0
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

#if !defined(CY_CLOCK_Clock_QuadDec_H)
#define CY_CLOCK_Clock_QuadDec_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void Clock_QuadDec_Start(void);
void Clock_QuadDec_Stop(void);

void Clock_QuadDec_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clock_QuadDec_GetDividerRegister(void);
uint8  Clock_QuadDec_GetFractionalDividerRegister(void);

#define Clock_QuadDec_Enable()                         Clock_QuadDec_Start()
#define Clock_QuadDec_Disable()                        Clock_QuadDec_Stop()
#define Clock_QuadDec_SetDividerRegister(clkDivider, reset)  \
                        Clock_QuadDec_SetFractionalDividerRegister((clkDivider), 0)
#define Clock_QuadDec_SetDivider(clkDivider)           Clock_QuadDec_SetDividerRegister((clkDivider), 1)
#define Clock_QuadDec_SetDividerValue(clkDivider)      Clock_QuadDec_SetDividerRegister((clkDivider) - 1, 1)


/***************************************
*             Registers
***************************************/

#define Clock_QuadDec_DIV_REG    (*(reg32 *)Clock_QuadDec__REGISTER)
#define Clock_QuadDec_ENABLE_REG Clock_QuadDec_DIV_REG

#endif /* !defined(CY_CLOCK_Clock_QuadDec_H) */

/* [] END OF FILE */
