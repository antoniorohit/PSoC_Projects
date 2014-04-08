/*******************************************************************************
* File Name: SW2_PlayMode.h  
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

#if !defined(CY_PINS_SW2_PlayMode_H) /* Pins SW2_PlayMode_H */
#define CY_PINS_SW2_PlayMode_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SW2_PlayMode_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SW2_PlayMode_Write(uint8 value) ;
void    SW2_PlayMode_SetDriveMode(uint8 mode) ;
uint8   SW2_PlayMode_ReadDataReg(void) ;
uint8   SW2_PlayMode_Read(void) ;
uint8   SW2_PlayMode_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SW2_PlayMode_DRIVE_MODE_BITS        (3)
#define SW2_PlayMode_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SW2_PlayMode_DRIVE_MODE_BITS))
#define SW2_PlayMode_DRIVE_MODE_SHIFT       (0x00u)
#define SW2_PlayMode_DRIVE_MODE_MASK        (0x07u << SW2_PlayMode_DRIVE_MODE_SHIFT)

#define SW2_PlayMode_DM_ALG_HIZ         (0x00u << SW2_PlayMode_DRIVE_MODE_SHIFT)
#define SW2_PlayMode_DM_DIG_HIZ         (0x01u << SW2_PlayMode_DRIVE_MODE_SHIFT)
#define SW2_PlayMode_DM_RES_UP          (0x02u << SW2_PlayMode_DRIVE_MODE_SHIFT)
#define SW2_PlayMode_DM_RES_DWN         (0x03u << SW2_PlayMode_DRIVE_MODE_SHIFT)
#define SW2_PlayMode_DM_OD_LO           (0x04u << SW2_PlayMode_DRIVE_MODE_SHIFT)
#define SW2_PlayMode_DM_OD_HI           (0x05u << SW2_PlayMode_DRIVE_MODE_SHIFT)
#define SW2_PlayMode_DM_STRONG          (0x06u << SW2_PlayMode_DRIVE_MODE_SHIFT)
#define SW2_PlayMode_DM_RES_UPDWN       (0x07u << SW2_PlayMode_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define SW2_PlayMode_MASK               SW2_PlayMode__MASK
#define SW2_PlayMode_SHIFT              SW2_PlayMode__SHIFT
#define SW2_PlayMode_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SW2_PlayMode_PS                     (* (reg32 *) SW2_PlayMode__PS)
/* Port Configuration */
#define SW2_PlayMode_PC                     (* (reg32 *) SW2_PlayMode__PC)
/* Data Register */
#define SW2_PlayMode_DR                     (* (reg32 *) SW2_PlayMode__DR)
/* Input Buffer Disable Override */
#define SW2_PlayMode_INP_DIS                (* (reg32 *) SW2_PlayMode__PC2)


#if defined(SW2_PlayMode__INTSTAT)  /* Interrupt Registers */

    #define SW2_PlayMode_INTSTAT                (* (reg32 *) SW2_PlayMode__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins SW2_PlayMode_H */


/* [] END OF FILE */
