/*******************************************************************************
* File Name: CapSense_CSD_SampleClk.h
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

#if !defined(CY_CLOCK_CapSense_CSD_SampleClk_H)
#define CY_CLOCK_CapSense_CSD_SampleClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void CapSense_CSD_SampleClk_Start(void);
void CapSense_CSD_SampleClk_Stop(void);

void CapSense_CSD_SampleClk_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 CapSense_CSD_SampleClk_GetDividerRegister(void);
uint8  CapSense_CSD_SampleClk_GetFractionalDividerRegister(void);

#define CapSense_CSD_SampleClk_Enable()                         CapSense_CSD_SampleClk_Start()
#define CapSense_CSD_SampleClk_Disable()                        CapSense_CSD_SampleClk_Stop()
#define CapSense_CSD_SampleClk_SetDividerRegister(clkDivider, reset)  \
                        CapSense_CSD_SampleClk_SetFractionalDividerRegister((clkDivider), 0u)
#define CapSense_CSD_SampleClk_SetDivider(clkDivider)           CapSense_CSD_SampleClk_SetDividerRegister((clkDivider), 1u)
#define CapSense_CSD_SampleClk_SetDividerValue(clkDivider)      CapSense_CSD_SampleClk_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/

#define CapSense_CSD_SampleClk_DIV_REG    (*(reg32 *)CapSense_CSD_SampleClk__REGISTER)
#define CapSense_CSD_SampleClk_ENABLE_REG CapSense_CSD_SampleClk_DIV_REG

#endif /* !defined(CY_CLOCK_CapSense_CSD_SampleClk_H) */

/* [] END OF FILE */
