/*******************************************************************************
* File Name: CapSense_CSD_SenseClk.h
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

#if !defined(CY_CLOCK_CapSense_CSD_SenseClk_H)
#define CY_CLOCK_CapSense_CSD_SenseClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void CapSense_CSD_SenseClk_Start(void);
void CapSense_CSD_SenseClk_Stop(void);

void CapSense_CSD_SenseClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 CapSense_CSD_SenseClk_GetDividerRegister(void);
uint8  CapSense_CSD_SenseClk_GetFractionalDividerRegister(void);

#define CapSense_CSD_SenseClk_Enable()                         CapSense_CSD_SenseClk_Start()
#define CapSense_CSD_SenseClk_Disable()                        CapSense_CSD_SenseClk_Stop()
#define CapSense_CSD_SenseClk_SetDividerRegister(clkDivider, reset)  \
                        CapSense_CSD_SenseClk_SetFractionalDividerRegister((clkDivider), 0u)
#define CapSense_CSD_SenseClk_SetDivider(clkDivider)           CapSense_CSD_SenseClk_SetDividerRegister((clkDivider), 1u)
#define CapSense_CSD_SenseClk_SetDividerValue(clkDivider)      CapSense_CSD_SenseClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/

#define CapSense_CSD_SenseClk_DIV_REG    (*(reg32 *)CapSense_CSD_SenseClk__REGISTER)
#define CapSense_CSD_SenseClk_ENABLE_REG CapSense_CSD_SenseClk_DIV_REG

#endif /* !defined(CY_CLOCK_CapSense_CSD_SenseClk_H) */

/* [] END OF FILE */
