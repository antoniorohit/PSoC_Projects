/*******************************************************************************
* File Name: PN_N_PWM_L.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PN_N_PWM_L_H) /* Pins PN_N_PWM_L_H */
#define CY_PINS_PN_N_PWM_L_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PN_N_PWM_L_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PN_N_PWM_L_Write(uint8 value) ;
void    PN_N_PWM_L_SetDriveMode(uint8 mode) ;
uint8   PN_N_PWM_L_ReadDataReg(void) ;
uint8   PN_N_PWM_L_Read(void) ;
uint8   PN_N_PWM_L_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PN_N_PWM_L_DRIVE_MODE_BITS        (3)
#define PN_N_PWM_L_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PN_N_PWM_L_DRIVE_MODE_BITS))
#define PN_N_PWM_L_DRIVE_MODE_SHIFT       (0x00u)
#define PN_N_PWM_L_DRIVE_MODE_MASK        (0x07u << PN_N_PWM_L_DRIVE_MODE_SHIFT)

#define PN_N_PWM_L_DM_ALG_HIZ         (0x00u << PN_N_PWM_L_DRIVE_MODE_SHIFT)
#define PN_N_PWM_L_DM_DIG_HIZ         (0x01u << PN_N_PWM_L_DRIVE_MODE_SHIFT)
#define PN_N_PWM_L_DM_RES_UP          (0x02u << PN_N_PWM_L_DRIVE_MODE_SHIFT)
#define PN_N_PWM_L_DM_RES_DWN         (0x03u << PN_N_PWM_L_DRIVE_MODE_SHIFT)
#define PN_N_PWM_L_DM_OD_LO           (0x04u << PN_N_PWM_L_DRIVE_MODE_SHIFT)
#define PN_N_PWM_L_DM_OD_HI           (0x05u << PN_N_PWM_L_DRIVE_MODE_SHIFT)
#define PN_N_PWM_L_DM_STRONG          (0x06u << PN_N_PWM_L_DRIVE_MODE_SHIFT)
#define PN_N_PWM_L_DM_RES_UPDWN       (0x07u << PN_N_PWM_L_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define PN_N_PWM_L_MASK               PN_N_PWM_L__MASK
#define PN_N_PWM_L_SHIFT              PN_N_PWM_L__SHIFT
#define PN_N_PWM_L_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PN_N_PWM_L_PS                     (* (reg32 *) PN_N_PWM_L__PS)
/* Port Configuration */
#define PN_N_PWM_L_PC                     (* (reg32 *) PN_N_PWM_L__PC)
/* Data Register */
#define PN_N_PWM_L_DR                     (* (reg32 *) PN_N_PWM_L__DR)
/* Input Buffer Disable Override */
#define PN_N_PWM_L_INP_DIS                (* (reg32 *) PN_N_PWM_L__PC2)


#if defined(PN_N_PWM_L__INTSTAT)  /* Interrupt Registers */

    #define PN_N_PWM_L_INTSTAT                (* (reg32 *) PN_N_PWM_L__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins PN_N_PWM_L_H */


/* [] END OF FILE */
