/*******************************************************************************
* File Name: CapSense_CSD.h
* Version 1.11
*
* Description:
*  This file provides constants and parameter values for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semicondu)ctor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end u)ser license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_CapSense_CSD_H)
#define CY_CAPSENSE_CSD_CapSense_CSD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cydevice_trm.h"
#include "core_cm0_psoc4.h"
#include "CyLib.h"

#include "CapSense_CSD_SenseClk.h"
#include "CapSense_CSD_SampleClk.h"


/* Interrupt handler */
CY_ISR_PROTO(CapSense_CSD_ISR);


/***************************************
*   Condition compilation parameters
***************************************/

#define CapSense_CSD_CONNECT_INACTIVE_SNS       (0u)
#define CapSense_CSD_IS_COMPLEX_SCANSLOTS       (0u)

#define CapSense_CSD_IDAC_CNT                   (1u)
#define CapSense_CSD_IDAC1_POLARITY             (0u)
#define CapSense_CSD_IDAC1_RANGE_VALUE          (1u)
#define CapSense_CSD_IDAC2_RANGE_VALUE          (1u)

#define CapSense_CSD_MULTIPLE_FREQUENCY_SET     (0u)

#define CapSense_CSD_PRS_OPTIONS                (0u)

#define CapSense_CSD_WATER_PROOF                (0u)

#define CapSense_CSD_TUNING_METHOD              (0u)
#define CapSense_CSD_TUNER_API_GENERATE         (0u)


#define CapSense_CSD_CMOD_PREGARGE_OPTION       (1u)
#define CapSense_CSD_CSH_TANK_PREGARGE_OPTION   (0u)
#define CapSense_CSD_IS_SHIELD_ENABLE           (0u)
#define CapSense_CSD_CSH_TANK_ENABLE            (0u)

#define CapSense_CSD_SHIELD_DELAY               (0u)

/**************************************
*    Enumerated Types and Parameters
**************************************/

/* Current source definitions */
#define CapSense_CSD__IDAC_SOURCE 0
#define CapSense_CSD__IDAC_SINK 1

#define CapSense_CSD__IDAC_4X 0
#define CapSense_CSD__IDAC_8X 1

#define CapSense_CSD__PRS_NONE 0
#define CapSense_CSD__PRS_8BITS 1
#define CapSense_CSD__PRS_12BITS 2
#define CapSense_CSD__PRS_AUTO 3

/* Connection of inactive sensors definitions */
#define CapSense_CSD__GROUND 0
#define CapSense_CSD__HIZ_ANALOG 1
#define CapSense_CSD__SHIELD 2


/* Precharge options definitions */
#define CapSense_CSD__CAPPRIOBUF 0
#define CapSense_CSD__CAPPRVREF 1

/* Method of tunning */
#define CapSense_CSD__TUNING_NONE 0
#define CapSense_CSD__TUNING_MANUAL 1
#define CapSense_CSD__TUNING_AUTO 2


#define CapSense_CSD_TUNING_NONE 0
#define CapSense_CSD_MANUAL_TUNING 1
#define CapSense_CSD_AUTO_TUNING 2

/* Defitition of the time interval that enough for charging 100nF capacitor */
#define CapSense_CSD_MAX_CHARGE_TIME_US				(100u)
#define CapSense_CSD_AVG_CYCLES_PER_LOOP			(5u)
#define CapSense_CSD_PRECHARGE_WATCHDOG_CYCLES_NUM	(((CYDEV_BCLK__SYSCLK__MHZ) * (CapSense_CSD_MAX_CHARGE_TIME_US)) /\
														 (CapSense_CSD_AVG_CYCLES_PER_LOOP)) 

/* Scan type definitions */
#define CapSense_CSD_SELF_CAPACITANCE           (0u)
#define CapSense_CSD_MUTUAL_CAPACITANCE         (1u)

#define CapSense_CSD_CSD_SENSE_PORT_MODE        (4u)
#define CapSense_CSD_CSD_SHIELD_PORT_MODE       (5u)
#define CapSense_CSD_CSD_PIN_MODE_MASK          (0x00000007u)
#define CapSense_CSD_CSD_HSIOM_MASK             (0x0000000Fu)
#define CapSense_CSD_CSD_PIN_DRIVE_MASK         (0x00000001u)

#define CapSense_CSD_CSD_CMOD_CONNECTION_MASK   (0x00000F00)
#define CapSense_CSD_CSD_CTANK_CONNECTION_MASK  (0x0000F000)

#define CapSense_CSD_CSD_CMOD_TO_AMUXBUS_A      (0x00000600)
#define CapSense_CSD_CSD_CMOD_TO_AMUXBUS_B      (0x00000700)

#define CapSense_CSD_CSD_CTANK_TO_AMUXBUS_A     (0x00006000)
#define CapSense_CSD_CSD_CTANK_TO_AMUXBUS_B     (0x00007000)

#define  CapSense_CSD_CSD_CMOD_PC_MASK          (0x000001C0u)
#define  CapSense_CSD_CSD_CTANK_PC_MASK         (0x00000E00u)

#define  CapSense_CSD_CMOD_PC_STRONG_MODE       (0x00000180u)
#define  CapSense_CSD_CMOD_PC_HIGH_Z_MODE       (0x00000000u)

#define  CapSense_CSD_CTANK_PC_STRONG_MODE      (0x00000C00u)
#define  CapSense_CSD_CTANK_PC_HIGH_Z_MODE      (0x00000000u)

#define  CapSense_CSD_CMOD_DR_VSSIO 			(0x04u)
#define  CapSense_CSD_CMOD_DR_VDDIO				(0x00u)
#define  CapSense_CSD_CMOD_DR_MASK				(0x04u)

#define  CapSense_CSD_CTANK_DR_VSSIO 			(0x08u)
#define  CapSense_CSD_CTANK_DR_VDDIO			(0x00u)
#define  CapSense_CSD_CTANK_DR_MASK 			(0x08u)

/* Structure to save registers before go to sleep */
typedef struct _CapSense_CSD_BACKUP_STRUCT
{
    uint8 enableState;
} CapSense_CSD_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void CapSense_CSD_Init(void);
void CapSense_CSD_Enable(void);
void CapSense_CSD_Start(void);
void CapSense_CSD_Stop(void);
void CapSense_CSD_SaveConfig(void);
void CapSense_CSD_Sleep(void);
void CapSense_CSD_RestoreConfig(void);
void CapSense_CSD_Wakeup(void);
uint8 CapSense_CSD_IsBusy(void);
void CapSense_CSD_ScanSensor(uint8 sensor);
void CapSense_CSD_ScanEnabledWidgets(void);
__INLINE void CapSense_CSD_SetScanSlotSettings(uint8 slot);
uint16 CapSense_CSD_ReadSensorRaw(uint8 sensor);
void CapSense_CSD_ClearSensors(void);
__INLINE void CapSense_CSD_EnableSensor(uint8 sensor);
__INLINE void CapSense_CSD_DisableSensor(uint8 sensor);

void CapSense_CSD_SetShieldDelay(uint32 delay);

uint32 CapSense_CSD_GetResolutionIndex(uint32 widgetResolution);
void CapSense_CSD_Calc_PRS_Resolution(void);

/* Interrupt handler */
CY_ISR_PROTO(CapSense_CSD_ISR);


/***************************************
*           API Constants
***************************************/

#define CapSense_CSD_TOTAL_SENSOR_COUNT            (2u)
#define CapSense_CSD_TOTAL_SCANSLOT_COUNT            (2u)

/* Define Sensors */
#define CapSense_CSD_SENSOR_PROXIMITYSENSOR0_0__PROX    (0u)
#define CapSense_CSD_SENSOR_PROXIMITYSENSOR1_0__PROX    (1u)
/* AMux Cmod, Comparator and Idac Channels definitions */
#define CapSense_CSD_AMuxCH_CMOD_CHANNEL          (0u)
#define CapSense_CSD_AMuxCH_CMP_VP_CHANNEL        (1u)
#define CapSense_CSD_AMuxCH_IDAC_CHANNEL          (2u)




/* PWM Resolution */
#define CapSense_CSD_WINDOW_APPEND          (0xFFFE0000u)
#define CapSense_CSD_RESOLUTION_8_BITS      (0x00FF0000u)
#define CapSense_CSD_RESOLUTION_9_BITS      (0x01FF0000u)
#define CapSense_CSD_RESOLUTION_10_BITS     (0x03FF0000u)
#define CapSense_CSD_RESOLUTION_11_BITS     (0x07FF0000u)
#define CapSense_CSD_RESOLUTION_12_BITS     (0x0FFF0000u)
#define CapSense_CSD_RESOLUTION_13_BITS     (0x1FFF0000u)
#define CapSense_CSD_RESOLUTION_14_BITS     (0x3FFF0000u)
#define CapSense_CSD_RESOLUTION_15_BITS     (0x7FFF0000u)
#define CapSense_CSD_RESOLUTION_16_BITS     (0xFFFF0000u)

#define CapSense_CSD_MSB_RESOLUTION_OFFSET  (24u)

/* Software Status Register Bit Masks */
#define CapSense_CSD_SW_STS_BUSY                (0x01u)
/* Software Status Register Bit Masks */
#define CapSense_CSD_SW_CTRL_SINGLE_SCAN        (0x80u)
/* Flag of complex scan slot */
#define CapSense_CSD_COMPLEX_SS_FLAG            (0x80u)


/***************************************
*             Registers
***************************************/

#define CapSense_CSD_CSD_ID_REG             (*(reg32 *)  CapSense_CSD_CSD_FFB__CSD_ID)
#define CapSense_CSD_CSD_ID_PTR             ( (reg32 *)  CapSense_CSD_CSD_FFB__CSD_ID)

#define CapSense_CSD_CSD_CFG_REG            (*(reg32 *)  CapSense_CSD_CSD_FFB__CSD_CONFIG)
#define CapSense_CSD_CSD_CFG_PTR            ( (reg32 *)  CapSense_CSD_CSD_FFB__CSD_CONFIG)

#define CapSense_CSD_CSD_IDAC_REG           (*(reg32 *)  CYREG_CSD_IDAC)
#define CapSense_CSD_CSD_IDAC_PTR           ( (reg32 *)  CYREG_CSD_IDAC)

#define CapSense_CSD_CSD_CNT_REG            (*(reg32 *) CYREG_CSD_COUNTER)
#define CapSense_CSD_CSD_CNT_PTR            ( (reg32 *) CYREG_CSD_COUNTER)

#define CapSense_CSD_CSD_STAT_REG           (*(reg32 *) CapSense_CSD_CSD_FFB__CSD_STATUS)
#define CapSense_CSD_CSD_STAT_PTR           ( (reg32 *) CapSense_CSD_CSD_FFB__CSD_STATUS)

#define CapSense_CSD_CSD_INTR_REG           (*(reg32 *) CapSense_CSD_CSD_FFB__CSD_INTR)
#define CapSense_CSD_CSD_INTR_PTR           ( (reg32 *) CapSense_CSD_CSD_FFB__CSD_INTR)

#define CapSense_CSD_CSD_INTR_SET_REG       (*(reg32 *) CapSense_CSD_CSD_FFB__CSD_INTR_SET)
#define CapSense_CSD_CSD_INTR_SET_PTR       ( (reg32 *) CapSense_CSD_CSD_FFB__CSD_INTR_SET)

#define CapSense_CSD_CSD_TRIM1_REG          (*(reg32 *) CYREG_CSD_TRIM1)
#define CapSense_CSD_CSD_TRIM1_PTR          ( (reg32 *) CYREG_CSD_TRIM1)

#define CapSense_CSD_CSD_TRIM2_REG          (*(reg32 *) CYREG_CSD_TRIM2)
#define CapSense_CSD_CSD_TRIM2_PTR          ( (reg32 *) CYREG_CSD_TRIM2)

#define CapSense_CSD_SFLASH_CSD_TRIM1_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
#define CapSense_CSD_SFLASH_CSD_TRIM1_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

#define CapSense_CSD_SFLASH_CSD_TRIM2_REG   (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
#define CapSense_CSD_SFLASH_CSD_TRIM2_PTR   ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)

/* Port function select */
#define CapSense_CSD_PORT_SEL0_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL0 )
#define CapSense_CSD_PORT_SEL0_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL0 )

#define CapSense_CSD_PORT_SEL1_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL1 )
#define CapSense_CSD_PORT_SEL1_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL1 )

#define CapSense_CSD_PORT_SEL2_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL2 )
#define CapSense_CSD_PORT_SEL2_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL2 )

#define CapSense_CSD_PORT_SEL3_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL3 )
#define CapSense_CSD_PORT_SEL3_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL3 )

#define CapSense_CSD_PORT_SEL4_REG          (*(reg32 *) CYREG_HSIOM_PORT_SEL4 )
#define CapSense_CSD_PORT_SEL4_PTR          ( (reg32 *) CYREG_HSIOM_PORT_SEL4 )

/* Port DR and PC registers */
#define CapSense_CSD_PORT0_DR_REG           (*(reg32 *) CYREG_PRT0_DR )
#define CapSense_CSD_PORT0_DR_PTR           ( (reg32 *) CYREG_PRT0_DR )

#define CapSense_CSD_PORT1_DR_REG           (*(reg32 *) CYREG_PRT1_DR )
#define CapSense_CSD_PORT1_DR_PTR           ( (reg32 *) CYREG_PRT1_DR )

#define CapSense_CSD_PORT2_DR_REG           (*(reg32 *) CYREG_PRT2_DR )
#define CapSense_CSD_PORT2_DR_PTR           ( (reg32 *) CYREG_PRT2_DR )

#define CapSense_CSD_PORT3_DR_REG           (*(reg32 *) CYREG_PRT3_DR )
#define CapSense_CSD_PORT3_DR_PTR           ( (reg32 *) CYREG_PRT3_DR )

#define CapSense_CSD_PORT4_DR_REG           (*(reg32 *) CYREG_PRT4_DR )
#define CapSense_CSD_PORT4_DR_PTR           ( (reg32 *) CYREG_PRT4_DR )


/* Port DR and PC registers */
#define CapSense_CSD_PORT0_PC_REG           (*(reg32 *) CYREG_PRT0_PC )
#define CapSense_CSD_PORT0_PC_PTR           ( (reg32 *) CYREG_PRT0_PC )

#define CapSense_CSD_PORT1_PC_REG           (*(reg32 *) CYREG_PRT1_PC )
#define CapSense_CSD_PORT1_PC_PTR           ( (reg32 *) CYREG_PRT1_PC )

#define CapSense_CSD_PORT2_PC_REG           (*(reg32 *) CYREG_PRT2_PC )
#define CapSense_CSD_PORT2_PC_PTR           ( (reg32 *) CYREG_PRT2_PC )

#define CapSense_CSD_PORT3_PC_REG           (*(reg32 *) CYREG_PRT3_PC )
#define CapSense_CSD_PORT3_PC_PTR           ( (reg32 *) CYREG_PRT3_PC )

#define CapSense_CSD_PORT4_PC_REG           (*(reg32 *) CYREG_PRT4_PC )
#define CapSense_CSD_PORT4_PC_PTR           ( (reg32 *) CYREG_PRT4_PC )


/* ISR Number and Priority to work with CyLib functions */
#define CapSense_CSD_ISR_NUMBER        (CapSense_CSD_ISR__INTC_NUMBER)
#define CapSense_CSD_ISR_PRIORITY      (CapSense_CSD_ISR__INTC_PRIOR_NUM)


/***************************************
*       Register Constants
***************************************/

/* ID register fields position */
#define CapSense_CSD_CSD_ID_ID__POS              (0x00u)
#define CapSense_CSD_CSD_ID_REV__POS             (0x10u)

#define CapSense_CSD_CSD_ID_ID                   (0xFFLu << CapSense_CSD_CSD_ID_ID__POS)
#define CapSense_CSD_CSD_ID_REV                  (0xFFLu << CapSense_CSD_CSD_ID_REV__POS)


/* CONFIG register fields position */
#define CapSense_CSD_CSD_CFG_DSI_SAMPLE_EN__POS  (0x00u)
#define CapSense_CSD_CSD_CFG_SAMPLE_SYNC__POS    (0x01u)
#define CapSense_CSD_CSD_CFG_PRS_CLEAR__POS      (0x05u)
#define CapSense_CSD_CSD_CFG_PRS_SELECT__POS     (0x06u)
#define CapSense_CSD_CSD_CFG_PRS_12_8__POS       (0x07u)
#define CapSense_CSD_CSD_CFG_DSI_SENSE_EN__POS   (0x08u)
#define CapSense_CSD_CSD_CFG_SHIELD_DELAY__POS   (0x09u)
#define CapSense_CSD_CSD_CFG_SENSE_COMP_BW__POS  (0x0Bu)
#define CapSense_CSD_CSD_CFG_SENSE_EN__POS       (0x0Cu)
#define CapSense_CSD_CSD_CFG_REFBUF_EN__POS      (0x0Du)
#define CapSense_CSD_CSD_CFG_COMP_MODE__POS      (0x0Eu)
#define CapSense_CSD_CSD_CFG_COMP_PIN__POS       (0x0Fu)
#define CapSense_CSD_CSD_CFG_POLARITY__POS       (0x10u)
#define CapSense_CSD_CSD_CFG_POLARITY2__POS      (0x11u)
#define CapSense_CSD_CSD_CFG_MUTUAL_CAP__POS     (0x12u)
#define CapSense_CSD_CSD_CFG_SENSE_COMP_EN__POS  (0x13u)
#define CapSense_CSD_CSD_CFG_REFBUF_BOOST__POS   (0x14u)
#define CapSense_CSD_CSD_CFG_REFBUF_OUTSEL__POS  (0x15u)
#define CapSense_CSD_CSD_CFG_SENSE_INSEL__POS    (0x16u)
#define CapSense_CSD_CSD_CFG_DDFTSEL__POS        (0x1Au)
#define CapSense_CSD_CSD_CFG_ADFTEN__POS         (0x1Du)
#define CapSense_CSD_CSD_CFG_DDFTCOMP__POS       (0x1Eu)
#define CapSense_CSD_CSD_CFG_ENABLE__POS         (0x1Fu)

#define CapSense_CSD_CSD_CFG_DSI_SAMPLE_EN       (0x01Lu << CapSense_CSD_CSD_CFG_DSI_SAMPLE_EN__POS)
#define CapSense_CSD_CSD_CFG_SAMPLE_SYNC         (0x01Lu << CapSense_CSD_CSD_CFG_SAMPLE_SYNC__POS)
#define CapSense_CSD_CSD_CFG_PRS_CLEAR           (0x01Lu << CapSense_CSD_CSD_CFG_PRS_CLEAR__POS)
#define CapSense_CSD_CSD_CFG_PRS_SELECT          (0x01Lu << CapSense_CSD_CSD_CFG_PRS_SELECT__POS)
#define CapSense_CSD_CSD_CFG_PRS_12_8            (0x01Lu << CapSense_CSD_CSD_CFG_PRS_12_8__POS)
#define CapSense_CSD_CSD_CFG_DSI_SENSE_EN        (0x01Lu << CapSense_CSD_CSD_CFG_DSI_SENSE_EN__POS)
#define CapSense_CSD_CSD_CFG_SHIELD_DELAY        (0x03Lu << CapSense_CSD_CSD_CFG_SHIELD_DELAY__POS)
#define CapSense_CSD_CSD_CFG_SENSE_COMP_BW       (0x01Lu << CapSense_CSD_CSD_CFG_SENSE_COMP_BW__POS)
#define CapSense_CSD_CSD_CFG_SENSE_EN            (0x01Lu << CapSense_CSD_CSD_CFG_SENSE_EN__POS)
#define CapSense_CSD_CSD_CFG_REFBUF_EN           (0x01Lu << CapSense_CSD_CSD_CFG_REFBUF_EN__POS)
#define CapSense_CSD_CSD_CFG_COMP_MODE           (0x01Lu << CapSense_CSD_CSD_CFG_COMP_MODE__POS)
#define CapSense_CSD_CSD_CFG_COMP_PIN            (0x01Lu << CapSense_CSD_CSD_CFG_COMP_PIN__POS)
#define CapSense_CSD_CSD_CFG_POLARITY            (0x01Lu << CapSense_CSD_CSD_CFG_POLARITY__POS)
#define CapSense_CSD_CSD_CFG_POLARITY2           (0x01Lu << CapSense_CSD_CSD_CFG_POLARITY2__POS)
#define CapSense_CSD_CSD_CFG_MUTUAL_CAP          (0x01Lu << CapSense_CSD_CSD_CFG_MUTUAL_CAP__POS)
#define CapSense_CSD_CSD_CFG_SENSE_COMP_EN       (0x01Lu << CapSense_CSD_CSD_CFG_SENSE_COMP_EN__POS)
#define CapSense_CSD_CSD_CFG_REFBUF_BOOST        (0x01Lu << CapSense_CSD_CSD_CFG_REFBUF_BOOST__POS)
#define CapSense_CSD_CSD_CFG_REFBUF_OUTSEL       (0x01Lu << CapSense_CSD_CSD_CFG_REFBUF_OUTSEL__POS)
#define CapSense_CSD_CSD_CFG_SENSE_INSEL         (0x01Lu << CapSense_CSD_CSD_CFG_SENSE_INSEL__POS)
#define CapSense_CSD_CSD_CFG_DDFTSEL             (0x07Lu << CapSense_CSD_CSD_CFG_DDFTSEL__POS)
#define CapSense_CSD_CSD_CFG_ADFTEN              (0x01Lu << CapSense_CSD_CSD_CFG_ADFTEN__POS)
#define CapSense_CSD_CSD_CFG_DDFTCOMP            (0x01Lu << CapSense_CSD_CSD_CFG_DDFTCOMP__POS)
#define CapSense_CSD_CSD_CFG_ENABLE              (0x01Lu << CapSense_CSD_CSD_CFG_ENABLE__POS)

/* STATUS register fields position */
#define CapSense_CSD_CSD_STAT_CSD_CHARGE__POS    (0x00Lu)
#define CapSense_CSD_CSD_STAT_CSD_SENSE__POS     (0x01Lu)
#define CapSense_CSD_CSD_STAT_COMP_OUT__POS      (0x02Lu)
#define CapSense_CSD_CSD_STAT_SAMPLE__POS        (0x03Lu)

#define CapSense_CSD_CSD_STAT_CSD_CHARGE         (0x01Lu << CapSense_CSD_CSD_STAT_CSD_CHARGE__POS)
#define CapSense_CSD_CSD_STAT_CSD_SENSE          (0x01Lu << CapSense_CSD_CSD_STAT_CSD_SENSE__POS)
#define CapSense_CSD_CSD_STAT_COMP_OUT           (0x01Lu << CapSense_CSD_CSD_STAT_COMP_OUT__POS)
#define CapSense_CSD_CSD_STAT_SAMPLE             (0x01Lu << CapSense_CSD_CSD_STAT_SAMPLE__POS)

/* Init Idac current */
#define CapSense_CSD_TURN_OFF_IDAC               (0x00u)
#define CapSense_CSD_PRECHARGE_IDAC1_VAL		 (0xFAu)

/* CSD config constants */
#define CapSense_CSD_CSD_IDAC1_MODE_MASK          (0x00000300u)
#define CapSense_CSD_CSD_IDAC1_MODE_OFF           (0x00000000u)
#define CapSense_CSD_CSD_IDAC1_MODE_FIXED         (0x00000100u)
#define CapSense_CSD_CSD_IDAC1_MODE_VARIABLE      (0x00000200u)
#define CapSense_CSD_CSD_IDAC1_MODE_DSI           (0x00000300u)
#define CapSense_CSD_CSD_IDAC1_RANGE_8X           (0x00000400u)
#define CapSense_CSD_CSD_IDAC1_DATA_MASK          (0x000000FFu)

#define CapSense_CSD_CSD_IDAC2_MODE_MASK          (0x03000000u)
#define CapSense_CSD_CSD_IDAC2_MODE_OFF           (0x00000000u)
#define CapSense_CSD_CSD_IDAC2_MODE_ON            (0x00000000u)
#define CapSense_CSD_CSD_IDAC2_MODE_FIXED         (0x01000000u)
#define CapSense_CSD_CSD_IDAC2_MODE_VARIABLE      (0x02000000u)
#define CapSense_CSD_CSD_IDAC2_MODE_DSI           (0x03000000u)
#define CapSense_CSD_CSD_IDAC2_RANGE_8X           (0x04000000u)
#define CapSense_CSD_CSD_IDAC2_DATA_MASK          (0x007F0000u)
#define CapSense_CSD_CSD_IDAC2_DATA_OFFSET        (16u)

#define CapSense_CSD_CSD_IDAC1_TRIM_MASK          (0xFFFFFFF0u)
#define CapSense_CSD_CSD_IDAC2_TRIM_MASK          (0xFFFFFF0Fu)

#define CapSense_CSD_CSFLASH_TRIM_IDAC1_MASK      (0x0F)
#define CapSense_CSD_CSFLASH_TRIM_IDAC2_MASK      (0xF0)

#define CapSense_CSD_CSD_IDAC_PRECHARGE_CONFIG	  (CapSense_CSD_CSD_IDAC1_MODE_FIXED |\
													   CapSense_CSD_PRECHARGE_IDAC1_VAL)	

#define CapSense_CSD_CSD_PRS_SELECT_DIV2          (0x00000000u)  
#define CapSense_CSD_CSD_PRS_SELECT_PRS           (CapSense_CSD_CSD_CFG_PRS_SELECT)  

#define CapSense_CSD_CSD_PRS_8_BIT                (0x00000000u)
#define CapSense_CSD_CSD_PRS_12_BIT               (CapSense_CSD_CSD_CFG_PRS_12_8)

#define CapSense_CSD_CSD_SENSE_COMP_BW_LOW        (0x00000000u)
#define CapSense_CSD_CSD_SENSE_COMP_BW_HIGH       (CapSense_CSD_CSD_CFG_SENSE_COMP_BW)

#define  CapSense_CSD_CSD_REFBUF_ENABLE           (CapSense_CSD_CSD_CFG_REFBUF_EN)
#define  CapSense_CSD_CSD_REFBUF_DISABLE          (0x00000000u)

#define  CapSense_CSD_CSD_REFBUF_TO_AMUXA         (0x00000000u)
#define  CapSense_CSD_CSD_REFBUF_TO_AMUXB         (CapSense_CSD_CSD_CFG_REFBUF_OUTSEL)

#define CapSense_CSD_CSD_COMP_MODE_CARGE_BUF      (0x00000000u)
#define CapSense_CSD_CSD_COMP_MODE_CHARGE_IO      (CapSense_CSD_CSD_CFG_COMP_MODE)

#define CapSense_CSD_CSD_COMP_PIN_CHANNEL1        (0x00000000u)  
#define CapSense_CSD_CSD_COMP_PIN_CHANNEL2        (CapSense_CSD_CSD_CFG_COMP_PIN)  

#define CapSense_CSD_CSD_POLARITY_VSSIO           (0x00000000u)
#define CapSense_CSD_CSD_POLARITY_VDDIO           (CapSense_CSD_CSD_CFG_POLARITY)

#define CapSense_CSD_CSD_POLARITY2_VSSIO          (0x00000000u)
#define CapSense_CSD_CSD_POLARITY2_VDDIO          (CapSense_CSD_CSD_CFG_POLARITY2)

#define CapSense_CSD_CSD_SENSE_CHANNEL1           (0x00000000u)
#define CapSense_CSD_CSD_SENSE_AMUXA              (CapSense_CSD_CSD_CFG_SENSE_INSEL)

#define CapSense_CSD_CSD_REFBUF_OFF               (0x00000000u)
#define CapSense_CSD_CSD_REFBUF_DRV_1             (0x00800000u)
#define CapSense_CSD_CSD_REFBUF_DRV_2             (0x01000000u)
#define CapSense_CSD_CSD_REFBUF_DRV_3             (0x01800000u)

/* COUNTER register fields position */
#define CapSense_CSD_CSD_CNT_COUNTER__POS        (0x00u)
#define CapSense_CSD_CSD_CNT_PERIOD__POS         (0x10u)

#define CapSense_CSD_CSD_CNT_COUNTER             (0xFFLu << CapSense_CSD_CSD_CNT_COUNTER__POS )
#define CapSense_CSD_CSD_CNT_PERIOD              (0xFFLu << CapSense_CSD_CSD_CNT_PERIOD__POS)


/* Set PRS */
#if (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_8BITS)
    #define CapSense_CSD_DEFAULT_MODULATION_MODE    CapSense_CSD_CSD_CFG_PRS_SELECT

#elif (CapSense_CSD_PRS_OPTIONS == CapSense_CSD__PRS_12BITS)
    #define CapSense_CSD_DEFAULT_MODULATION_MODE	CapSense_CSD_CSD_CFG_PRS_12_8 |\
														CapSense_CSD_CSD_CFG_PRS_SELECT
#else
	#define CapSense_CSD_DEFAULT_MODULATION_MODE	(0u)
#endif /* (CapSense_CSD_PRS_OPTIONS == CapSense_CSD_PRS_8BITS) */

/* Set IDAC ranges */
#if (CapSense_CSD_IDAC1_RANGE_VALUE == CapSense_CSD__IDAC_8X)
    #define CapSense_CSD_DEFAULT_IDAC1_RANGE    CapSense_CSD_CSD_IDAC1_RANGE_8X
    #define CapSense_CSD_DEFAULT_IDAC2_RANGE    CapSense_CSD_CSD_IDAC2_RANGE_8X
#else
    #define CapSense_CSD_DEFAULT_IDAC1_RANGE    (0u)
    #define CapSense_CSD_DEFAULT_IDAC2_RANGE    (0u)
#endif /* (CapSense_CSD_IDAC1_RANGE_VALUE == CapSense_CSD_IDAC_RANGE_8X) */

/* Set IDAC polarity */
#if(CapSense_CSD_IDAC1_POLARITY == CapSense_CSD__IDAC_SINK)

    #define CapSense_CSD_DEFAULT_IDAC_POLARITY	CapSense_CSD_CSD_POLARITY_VDDIO
	#define CapSense_CSD_CMOD_DR_CONFIG			 CapSense_CSD_CMOD_DR_VDDIO	
	#define CapSense_CSD_CTANK_DR_CONFIG	     CapSense_CSD_CTANK_DR_VDDIO
#else

    #define CapSense_CSD_DEFAULT_IDAC_POLARITY	 (0u)
	#define CapSense_CSD_CMOD_DR_CONFIG			 CapSense_CSD_CMOD_DR_VSSIO	
	#define CapSense_CSD_CTANK_DR_CONFIG	     CapSense_CSD_CTANK_DR_VSSIO 
#endif /* (CapSense_CSD_IDAC_OPTIONS == CapSense_CSD_IDAC_SINK) */

/* Inactive sensors connection configuration */
#if (CapSense_CSD_CONNECT_INACTIVE_SNS == CapSense_CSD__GROUND)
    #define CapSense_CSD_CSD_INACTIVE_CONNECT       (6u)
#else
    #define CapSense_CSD_CSD_INACTIVE_CONNECT       (0u)
#endif /* CapSense_CSD_CONNECT_INACTIVE_SNS == CapSense_CSD__GROUND */


/* Defining the default CSD configuration according to settingd in customizer. */
#define CapSense_CSD_DEFAULT_CSD_CONFIG             (CapSense_CSD_DEFAULT_MODULATION_MODE |\
                                                         CapSense_CSD_CSD_CFG_SENSE_COMP_BW |\
                                                         CapSense_CSD_CSD_REFBUF_ENABLE |\
                                                         CapSense_CSD_DEFAULT_IDAC_POLARITY |\
                                                         CapSense_CSD_CSD_CFG_REFBUF_OUTSEL |\
                                                         CapSense_CSD_CSD_REFBUF_DRV_3)


/* Defining the default IDACs configuration according to settings in customizer. */
#if (CapSense_CSD_IDAC_CNT == 1u)
#define CapSense_CSD_DEFAULT_CSD_IDAC_CONFIG        (CapSense_CSD_CSD_IDAC1_MODE_VARIABLE |\
                                                         CapSense_CSD_DEFAULT_IDAC1_RANGE)
#else
#define CapSense_CSD_DEFAULT_CSD_IDAC_CONFIG        (CapSense_CSD_CSD_IDAC1_MODE_FIXED |\
                                                         CapSense_CSD_CSD_IDAC2_MODE_VARIABLE |\
                                                         CapSense_CSD_DEFAULT_IDAC1_RANGE |\
                                                         CapSense_CSD_DEFAULT_IDAC2_RANGE)
#endif /* (CapSense_CSD_IDAC_CNT == 1u) */


/* Defining mask that intended to clearing bits that related to precharging options. */
#define CapSense_CSD_PRECHARGE_CONFIG_MASK			(CapSense_CSD_CSD_CFG_COMP_MODE |\
														 CapSense_CSD_CSD_CFG_COMP_PIN  |\
														 CapSense_CSD_CSD_REFBUF_ENABLE |\
														 CapSense_CSD_CSD_CFG_REFBUF_OUTSEL)

/* Cmod precharge mode configuration */
#if(CapSense_CSD_CMOD_PREGARGE_OPTION == CapSense_CSD__CAPPRVREF)

	#define CapSense_CSD_CMOD_PRECHARGE_CONFIG 		(CapSense_CSD_CSD_REFBUF_ENABLE |\
														 CapSense_CSD_CSD_COMP_MODE_CARGE_BUF |\
														 CapSense_CSD_CSD_COMP_PIN_CHANNEL2 |\
														 CapSense_CSD_CSD_REFBUF_TO_AMUXA)
														 
#else

	#define CapSense_CSD_CMOD_PRECHARGE_CONFIG 		(CapSense_CSD_CSD_REFBUF_TO_AMUXB |\
														 CapSense_CSD_CSD_REFBUF_ENABLE |\
														 CapSense_CSD_CSD_COMP_MODE_CHARGE_IO |\
														 CapSense_CSD_CSD_COMP_PIN_CHANNEL1)
														 
#endif /* (CapSense_CSD_CMOD_PREGARGE_OPTION == CapSense_CSD__CAPPRVREF) */


/* Ctank precharge mode configuration */
#if(CapSense_CSD_CSH_TANK_PREGARGE_OPTION == CapSense_CSD__CAPPRVREF)
	
	#if(0u != CapSense_CSD_IS_SHIELD_ENABLE)
		#define  CapSense_CSD_CTANK_PRECHARGE_CONFIG	(CapSense_CSD_CSD_COMP_MODE_CARGE_BUF |\
															 CapSense_CSD_CSD_COMP_PIN_CHANNEL1 |\
															 CapSense_CSD_CSD_REFBUF_ENABLE |\
															 CapSense_CSD_CSD_REFBUF_TO_AMUXB)
	#else
		#define  CapSense_CSD_CTANK_PRECHARGE_CONFIG	(CapSense_CSD_CSD_COMP_MODE_CARGE_BUF |\
															 CapSense_CSD_CSD_COMP_PIN_CHANNEL1 |\
															 CapSense_CSD_CSD_REFBUF_TO_AMUXB)
	#endif /* (0u != CapSense_CSD_IS_SHIELD_ENABLE) */													 
#else

	#define  CapSense_CSD_CTANK_PRECHARGE_CONFIG	(CapSense_CSD_CSD_REFBUF_TO_AMUXB |\
														 CapSense_CSD_CSD_REFBUF_ENABLE |\
														 CapSense_CSD_CSD_COMP_MODE_CHARGE_IO |\
														 CapSense_CSD_CSD_COMP_PIN_CHANNEL2)
#endif /* (CapSense_CSD_CSH_TANK_PREGARGE_OPTION == CapSense_CSD__CAPPRIOBUF) */

						
#endif /* CY_CAPSENSE_CSD_CapSense_CSD_H */

/***************************************************
*    Obsolete Names (will be removed in future)
***************************************************/
#define  CapSense_CSD_PrescalersTuningDone         CapSense_CSD_prescalersTuningDone
#define  CapSense_CSD_SensorRaw	                   CapSense_CSD_sensorRaw
#define  CapSense_CSD_PRSResolutionTbl             CapSense_CSD_prsResolutionTbl
#define  CapSense_CSD_SensorEnableMask             CapSense_CSD_sensorEnableMask
#define  CapSense_CSD_Clk1DividerVal               CapSense_CSD_senseClkDividerVal
#define  CapSense_CSD_Clk2DividerVal               CapSense_CSD_sampleClkDividerVal
#define  CapSense_CSD_PrtSelTbl                    CapSense_CSD_prtSelTbl
#define  CapSense_CSD_PrtCfgTbl                    CapSense_CSD_prtCfgTbl
#define  CapSense_CSD_PrtDRTbl                     CapSense_CSD_prtDRTbl


 /* [] END OF FILE */
