/*******************************************************************************
* File Name: Clock_PWM_LED.h
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

#if !defined(CY_CLOCK_Clock_PWM_LED_H)
#define CY_CLOCK_Clock_PWM_LED_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void Clock_PWM_LED_Start(void);
void Clock_PWM_LED_Stop(void);

void Clock_PWM_LED_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clock_PWM_LED_GetDividerRegister(void);
uint8  Clock_PWM_LED_GetFractionalDividerRegister(void);

#define Clock_PWM_LED_Enable()                         Clock_PWM_LED_Start()
#define Clock_PWM_LED_Disable()                        Clock_PWM_LED_Stop()
#define Clock_PWM_LED_SetDividerRegister(clkDivider, reset)  \
                        Clock_PWM_LED_SetFractionalDividerRegister((clkDivider), 0)
#define Clock_PWM_LED_SetDivider(clkDivider)           Clock_PWM_LED_SetDividerRegister((clkDivider), 1)
#define Clock_PWM_LED_SetDividerValue(clkDivider)      Clock_PWM_LED_SetDividerRegister((clkDivider) - 1, 1)


/***************************************
*             Registers
***************************************/

#define Clock_PWM_LED_DIV_REG    (*(reg32 *)Clock_PWM_LED__REGISTER)
#define Clock_PWM_LED_ENABLE_REG Clock_PWM_LED_DIV_REG

#endif /* !defined(CY_CLOCK_Clock_PWM_LED_H) */

/* [] END OF FILE */
