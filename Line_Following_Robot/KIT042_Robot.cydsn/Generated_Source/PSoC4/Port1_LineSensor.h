/*******************************************************************************
* File Name: Port1_LineSensor.h  
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

#if !defined(CY_PINS_Port1_LineSensor_H) /* Pins Port1_LineSensor_H */
#define CY_PINS_Port1_LineSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Port1_LineSensor_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Port1_LineSensor_Write(uint8 value) ;
void    Port1_LineSensor_SetDriveMode(uint8 mode) ;
uint8   Port1_LineSensor_ReadDataReg(void) ;
uint8   Port1_LineSensor_Read(void) ;
uint8   Port1_LineSensor_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Port1_LineSensor_DRIVE_MODE_BITS        (3)
#define Port1_LineSensor_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Port1_LineSensor_DRIVE_MODE_BITS))
#define Port1_LineSensor_DRIVE_MODE_SHIFT       (0x00u)
#define Port1_LineSensor_DRIVE_MODE_MASK        (0x07u << Port1_LineSensor_DRIVE_MODE_SHIFT)

#define Port1_LineSensor_DM_ALG_HIZ         (0x00u << Port1_LineSensor_DRIVE_MODE_SHIFT)
#define Port1_LineSensor_DM_DIG_HIZ         (0x01u << Port1_LineSensor_DRIVE_MODE_SHIFT)
#define Port1_LineSensor_DM_RES_UP          (0x02u << Port1_LineSensor_DRIVE_MODE_SHIFT)
#define Port1_LineSensor_DM_RES_DWN         (0x03u << Port1_LineSensor_DRIVE_MODE_SHIFT)
#define Port1_LineSensor_DM_OD_LO           (0x04u << Port1_LineSensor_DRIVE_MODE_SHIFT)
#define Port1_LineSensor_DM_OD_HI           (0x05u << Port1_LineSensor_DRIVE_MODE_SHIFT)
#define Port1_LineSensor_DM_STRONG          (0x06u << Port1_LineSensor_DRIVE_MODE_SHIFT)
#define Port1_LineSensor_DM_RES_UPDWN       (0x07u << Port1_LineSensor_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define Port1_LineSensor_MASK               Port1_LineSensor__MASK
#define Port1_LineSensor_SHIFT              Port1_LineSensor__SHIFT
#define Port1_LineSensor_WIDTH              8u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Port1_LineSensor_PS                     (* (reg32 *) Port1_LineSensor__PS)
/* Port Configuration */
#define Port1_LineSensor_PC                     (* (reg32 *) Port1_LineSensor__PC)
/* Data Register */
#define Port1_LineSensor_DR                     (* (reg32 *) Port1_LineSensor__DR)
/* Input Buffer Disable Override */
#define Port1_LineSensor_INP_DIS                (* (reg32 *) Port1_LineSensor__PC2)


#if defined(Port1_LineSensor__INTSTAT)  /* Interrupt Registers */

    #define Port1_LineSensor_INTSTAT                (* (reg32 *) Port1_LineSensor__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins Port1_LineSensor_H */


/* [] END OF FILE */
