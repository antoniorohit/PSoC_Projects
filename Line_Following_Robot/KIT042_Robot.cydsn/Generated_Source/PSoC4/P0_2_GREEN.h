/*******************************************************************************
* File Name: P0_2_GREEN.h  
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

#if !defined(CY_PINS_P0_2_GREEN_H) /* Pins P0_2_GREEN_H */
#define CY_PINS_P0_2_GREEN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "P0_2_GREEN_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    P0_2_GREEN_Write(uint8 value) ;
void    P0_2_GREEN_SetDriveMode(uint8 mode) ;
uint8   P0_2_GREEN_ReadDataReg(void) ;
uint8   P0_2_GREEN_Read(void) ;
uint8   P0_2_GREEN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define P0_2_GREEN_DRIVE_MODE_BITS        (3)
#define P0_2_GREEN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - P0_2_GREEN_DRIVE_MODE_BITS))
#define P0_2_GREEN_DRIVE_MODE_SHIFT       (0x00u)
#define P0_2_GREEN_DRIVE_MODE_MASK        (0x07u << P0_2_GREEN_DRIVE_MODE_SHIFT)

#define P0_2_GREEN_DM_ALG_HIZ         (0x00u << P0_2_GREEN_DRIVE_MODE_SHIFT)
#define P0_2_GREEN_DM_DIG_HIZ         (0x01u << P0_2_GREEN_DRIVE_MODE_SHIFT)
#define P0_2_GREEN_DM_RES_UP          (0x02u << P0_2_GREEN_DRIVE_MODE_SHIFT)
#define P0_2_GREEN_DM_RES_DWN         (0x03u << P0_2_GREEN_DRIVE_MODE_SHIFT)
#define P0_2_GREEN_DM_OD_LO           (0x04u << P0_2_GREEN_DRIVE_MODE_SHIFT)
#define P0_2_GREEN_DM_OD_HI           (0x05u << P0_2_GREEN_DRIVE_MODE_SHIFT)
#define P0_2_GREEN_DM_STRONG          (0x06u << P0_2_GREEN_DRIVE_MODE_SHIFT)
#define P0_2_GREEN_DM_RES_UPDWN       (0x07u << P0_2_GREEN_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define P0_2_GREEN_MASK               P0_2_GREEN__MASK
#define P0_2_GREEN_SHIFT              P0_2_GREEN__SHIFT
#define P0_2_GREEN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P0_2_GREEN_PS                     (* (reg32 *) P0_2_GREEN__PS)
/* Port Configuration */
#define P0_2_GREEN_PC                     (* (reg32 *) P0_2_GREEN__PC)
/* Data Register */
#define P0_2_GREEN_DR                     (* (reg32 *) P0_2_GREEN__DR)
/* Input Buffer Disable Override */
#define P0_2_GREEN_INP_DIS                (* (reg32 *) P0_2_GREEN__PC2)


#if defined(P0_2_GREEN__INTSTAT)  /* Interrupt Registers */

    #define P0_2_GREEN_INTSTAT                (* (reg32 *) P0_2_GREEN__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins P0_2_GREEN_H */


/* [] END OF FILE */
