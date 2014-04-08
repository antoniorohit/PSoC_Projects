/*******************************************************************************
* File Name: QuadDec_L.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the QuadDec_L
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_QuadDec_L_H)
#define CY_TCPWM_QuadDec_L_H

#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} QuadDec_L_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  QuadDec_L_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* TCPWM Configuration */
#define QuadDec_L_CONFIG                         (3lu)

/* Quad Mode */
/* Parameters */
#define QuadDec_L_QUAD_ENCODING_MODES            (2lu)

/* Signal modes */
#define QuadDec_L_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define QuadDec_L_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define QuadDec_L_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define QuadDec_L_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define QuadDec_L_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define QuadDec_L_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define QuadDec_L_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define QuadDec_L_TC_RUN_MODE                    (0lu)
#define QuadDec_L_TC_COUNTER_MODE                (0lu)
#define QuadDec_L_TC_COMP_CAP_MODE               (2lu)
#define QuadDec_L_TC_PRESCALER                   (0lu)

/* Signal modes */
#define QuadDec_L_TC_RELOAD_SIGNAL_MODE          (0lu)
#define QuadDec_L_TC_COUNT_SIGNAL_MODE           (3lu)
#define QuadDec_L_TC_START_SIGNAL_MODE           (0lu)
#define QuadDec_L_TC_STOP_SIGNAL_MODE            (0lu)
#define QuadDec_L_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define QuadDec_L_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define QuadDec_L_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define QuadDec_L_TC_START_SIGNAL_PRESENT        (0lu)
#define QuadDec_L_TC_STOP_SIGNAL_PRESENT         (0lu)
#define QuadDec_L_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define QuadDec_L_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define QuadDec_L_PWM_KILL_EVENT                 (0lu)
#define QuadDec_L_PWM_STOP_EVENT                 (0lu)
#define QuadDec_L_PWM_MODE                       (4lu)
#define QuadDec_L_PWM_OUT_N_INVERT               (0lu)
#define QuadDec_L_PWM_OUT_INVERT                 (0lu)
#define QuadDec_L_PWM_ALIGN                      (0lu)
#define QuadDec_L_PWM_RUN_MODE                   (0lu)
#define QuadDec_L_PWM_DEAD_TIME_CYCLE            (0lu)
#define QuadDec_L_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define QuadDec_L_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define QuadDec_L_PWM_COUNT_SIGNAL_MODE          (3lu)
#define QuadDec_L_PWM_START_SIGNAL_MODE          (0lu)
#define QuadDec_L_PWM_STOP_SIGNAL_MODE           (0lu)
#define QuadDec_L_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define QuadDec_L_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define QuadDec_L_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define QuadDec_L_PWM_START_SIGNAL_PRESENT       (0lu)
#define QuadDec_L_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define QuadDec_L_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define QuadDec_L_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define QuadDec_L_TC_PERIOD_VALUE                (65535lu)
#define QuadDec_L_TC_COMPARE_VALUE               (65535lu)
#define QuadDec_L_TC_COMPARE_BUF_VALUE           (65535lu)
#define QuadDec_L_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define QuadDec_L_PWM_PERIOD_VALUE               (65535lu)
#define QuadDec_L_PWM_PERIOD_BUF_VALUE           (65535lu)
#define QuadDec_L_PWM_PERIOD_SWAP                (0lu)
#define QuadDec_L_PWM_COMPARE_VALUE              (65535lu)
#define QuadDec_L_PWM_COMPARE_BUF_VALUE          (65535lu)
#define QuadDec_L_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define QuadDec_L__LEFT 0
#define QuadDec_L__RIGHT 1
#define QuadDec_L__CENTER 2
#define QuadDec_L__ASYMMETRIC 3

#define QuadDec_L__X1 0
#define QuadDec_L__X2 1
#define QuadDec_L__X4 2

#define QuadDec_L__PWM 4
#define QuadDec_L__PWM_DT 5
#define QuadDec_L__PWM_PR 6

#define QuadDec_L__INVERSE 1
#define QuadDec_L__DIRECT 0

#define QuadDec_L__CAPTURE 2
#define QuadDec_L__COMPARE 0

#define QuadDec_L__TRIG_LEVEL 3
#define QuadDec_L__TRIG_RISING 0
#define QuadDec_L__TRIG_FALLING 1
#define QuadDec_L__TRIG_BOTH 2

#define QuadDec_L__INTR_MASK_TC 1
#define QuadDec_L__INTR_MASK_CC_MATCH 2
#define QuadDec_L__INTR_MASK_NONE 0
#define QuadDec_L__INTR_MASK_TC_CC 3

#define QuadDec_L__UNCONFIG 8
#define QuadDec_L__TIMER 1
#define QuadDec_L__QUAD 3
#define QuadDec_L__PWM_SEL 7

#define QuadDec_L__COUNT_UP 0
#define QuadDec_L__COUNT_DOWN 1
#define QuadDec_L__COUNT_UPDOWN0 2
#define QuadDec_L__COUNT_UPDOWN1 3


/* Prescaler */
#define QuadDec_L_PRESCALE_DIVBY1                ((uint32)(0u << QuadDec_L_PRESCALER_SHIFT))
#define QuadDec_L_PRESCALE_DIVBY2                ((uint32)(1u << QuadDec_L_PRESCALER_SHIFT))
#define QuadDec_L_PRESCALE_DIVBY4                ((uint32)(2u << QuadDec_L_PRESCALER_SHIFT))
#define QuadDec_L_PRESCALE_DIVBY8                ((uint32)(3u << QuadDec_L_PRESCALER_SHIFT))
#define QuadDec_L_PRESCALE_DIVBY16               ((uint32)(4u << QuadDec_L_PRESCALER_SHIFT))
#define QuadDec_L_PRESCALE_DIVBY32               ((uint32)(5u << QuadDec_L_PRESCALER_SHIFT))
#define QuadDec_L_PRESCALE_DIVBY64               ((uint32)(6u << QuadDec_L_PRESCALER_SHIFT))
#define QuadDec_L_PRESCALE_DIVBY128              ((uint32)(7u << QuadDec_L_PRESCALER_SHIFT))

/* TCPWM set modes */
#define QuadDec_L_MODE_TIMER_COMPARE             ((uint32)(QuadDec_L__COMPARE         <<  \
                                                                  QuadDec_L_MODE_SHIFT))
#define QuadDec_L_MODE_TIMER_CAPTURE             ((uint32)(QuadDec_L__CAPTURE         <<  \
                                                                  QuadDec_L_MODE_SHIFT))
#define QuadDec_L_MODE_QUAD                      ((uint32)(QuadDec_L__QUAD            <<  \
                                                                  QuadDec_L_MODE_SHIFT))
#define QuadDec_L_MODE_PWM                       ((uint32)(QuadDec_L__PWM             <<  \
                                                                  QuadDec_L_MODE_SHIFT))
#define QuadDec_L_MODE_PWM_DT                    ((uint32)(QuadDec_L__PWM_DT          <<  \
                                                                  QuadDec_L_MODE_SHIFT))
#define QuadDec_L_MODE_PWM_PR                    ((uint32)(QuadDec_L__PWM_PR          <<  \
                                                                  QuadDec_L_MODE_SHIFT))

/* Quad Modes */
#define QuadDec_L_MODE_X1                        ((uint32)(QuadDec_L__X1              <<  \
                                                                  QuadDec_L_QUAD_MODE_SHIFT))
#define QuadDec_L_MODE_X2                        ((uint32)(QuadDec_L__X2              <<  \
                                                                  QuadDec_L_QUAD_MODE_SHIFT))
#define QuadDec_L_MODE_X4                        ((uint32)(QuadDec_L__X4              <<  \
                                                                  QuadDec_L_QUAD_MODE_SHIFT))

/* Counter modes */
#define QuadDec_L_COUNT_UP                       ((uint32)(QuadDec_L__COUNT_UP        <<  \
                                                                  QuadDec_L_UPDOWN_SHIFT))
#define QuadDec_L_COUNT_DOWN                     ((uint32)(QuadDec_L__COUNT_DOWN      <<  \
                                                                  QuadDec_L_UPDOWN_SHIFT))
#define QuadDec_L_COUNT_UPDOWN0                  ((uint32)(QuadDec_L__COUNT_UPDOWN0   <<  \
                                                                  QuadDec_L_UPDOWN_SHIFT))
#define QuadDec_L_COUNT_UPDOWN1                  ((uint32)(QuadDec_L__COUNT_UPDOWN1   <<  \
                                                                  QuadDec_L_UPDOWN_SHIFT))

/* PWM output invert */
#define QuadDec_L_INVERT_LINE                    ((uint32)(QuadDec_L__INVERSE         <<  \
                                                                  QuadDec_L_INV_OUT_SHIFT))
#define QuadDec_L_INVERT_LINE_N                  ((uint32)(QuadDec_L__INVERSE         <<  \
                                                                  QuadDec_L_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define QuadDec_L_TRIG_RISING                    (QuadDec_L__TRIG_RISING)
#define QuadDec_L_TRIG_FALLING                   (QuadDec_L__TRIG_FALLING)
#define QuadDec_L_TRIG_BOTH                      (QuadDec_L__TRIG_BOTH)
#define QuadDec_L_TRIG_LEVEL                     (QuadDec_L__TRIG_LEVEL)

/* Interrupt mask */
#define QuadDec_L_INTR_MASK_TC                   (QuadDec_L__INTR_MASK_TC)
#define QuadDec_L_INTR_MASK_CC_MATCH             (QuadDec_L__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define QuadDec_L_CC_MATCH_SET                   (0x00u)
#define QuadDec_L_CC_MATCH_CLEAR                 (0x01u)
#define QuadDec_L_CC_MATCH_INVERT                (0x02u)
#define QuadDec_L_CC_MATCH_NO_CHANGE             (0x03u)
#define QuadDec_L_OVERLOW_SET                    (0x00u)
#define QuadDec_L_OVERLOW_CLEAR                  (0x04u)
#define QuadDec_L_OVERLOW_INVERT                 (0x08u)
#define QuadDec_L_OVERLOW_NO_CHANGE              (0x0Cu)
#define QuadDec_L_UNDERFLOW_SET                  (0x00u)
#define QuadDec_L_UNDERFLOW_CLEAR                (0x10u)
#define QuadDec_L_UNDERFLOW_INVERT               (0x20u)
#define QuadDec_L_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define QuadDec_L_PWM_MODE_LEFT                  (QuadDec_L_CC_MATCH_CLEAR        |   \
                                                         QuadDec_L_OVERLOW_SET           |   \
                                                         QuadDec_L_UNDERFLOW_NO_CHANGE)
#define QuadDec_L_PWM_MODE_RIGHT                 (QuadDec_L_CC_MATCH_SET          |   \
                                                         QuadDec_L_OVERLOW_NO_CHANGE     |   \
                                                         QuadDec_L_UNDERFLOW_CLEAR)
#define QuadDec_L_PWM_MODE_CENTER                (QuadDec_L_CC_MATCH_INVERT       |   \
                                                         QuadDec_L_OVERLOW_NO_CHANGE     |   \
                                                         QuadDec_L_UNDERFLOW_CLEAR)
#define QuadDec_L_PWM_MODE_ASYM                  (QuadDec_L_CC_MATCH_NO_CHANGE    |   \
                                                         QuadDec_L_OVERLOW_SET           |   \
                                                         QuadDec_L_UNDERFLOW_CLEAR )

/* Command operations without condition */
#define QuadDec_L_CMD_CAPTURE                    (0u)
#define QuadDec_L_CMD_RELOAD                     (8u)
#define QuadDec_L_CMD_STOP                       (16u)
#define QuadDec_L_CMD_START                      (24u)

/* Status */
#define QuadDec_L_STATUS_DOWN                    (1u)
#define QuadDec_L_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   QuadDec_L_Init(void);
void   QuadDec_L_Enable(void);
void   QuadDec_L_Start(void);
void   QuadDec_L_Stop(void);

void   QuadDec_L_SetMode(uint32 mode);
void   QuadDec_L_SetCounterMode(uint32 counterMode);
void   QuadDec_L_SetPWMMode(uint32 modeMask);
void   QuadDec_L_SetQDMode(uint32 qdMode);

void   QuadDec_L_SetPrescaler(uint32 prescaler);
void   QuadDec_L_TriggerCommand(uint32 mask, uint32 command);
void   QuadDec_L_SetOneShot(uint32 oneShotEnable);
uint32 QuadDec_L_ReadStatus(void);

void   QuadDec_L_SetPWMSyncKill(uint32 syncKillEnable);
void   QuadDec_L_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   QuadDec_L_SetPWMDeadTime(uint32 deadTime);
void   QuadDec_L_SetPWMInvert(uint32 mask);

void   QuadDec_L_SetInterruptMode(uint32 interruptMask);
uint32 QuadDec_L_GetInterruptSourceMasked(void);
uint32 QuadDec_L_GetInterruptSource(void);
void   QuadDec_L_ClearInterrupt(uint32 interruptMask);
void   QuadDec_L_SetInterrupt(uint32 interruptMask);

void   QuadDec_L_WriteCounter(uint32 count);
uint32 QuadDec_L_ReadCounter(void);

uint32 QuadDec_L_ReadCapture(void);
uint32 QuadDec_L_ReadCaptureBuf(void);

void   QuadDec_L_WritePeriod(uint32 period);
uint32 QuadDec_L_ReadPeriod(void);
void   QuadDec_L_WritePeriodBuf(uint32 periodBuf);
uint32 QuadDec_L_ReadPeriodBuf(void);

void   QuadDec_L_WriteCompare(uint32 compare);
uint32 QuadDec_L_ReadCompare(void);
void   QuadDec_L_WriteCompareBuf(uint32 compareBuf);
uint32 QuadDec_L_ReadCompareBuf(void);

void   QuadDec_L_SetPeriodSwap(uint32 swapEnable);
void   QuadDec_L_SetCompareSwap(uint32 swapEnable);

void   QuadDec_L_SetCaptureMode(uint32 triggerMode);
void   QuadDec_L_SetReloadMode(uint32 triggerMode);
void   QuadDec_L_SetStartMode(uint32 triggerMode);
void   QuadDec_L_SetStopMode(uint32 triggerMode);
void   QuadDec_L_SetCountMode(uint32 triggerMode);

void   QuadDec_L_SaveConfig(void);
void   QuadDec_L_RestoreConfig(void);
void   QuadDec_L_Sleep(void);
void   QuadDec_L_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define QuadDec_L_BLOCK_CONTROL_REG              (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define QuadDec_L_BLOCK_CONTROL_PTR              ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define QuadDec_L_COMMAND_REG                    (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define QuadDec_L_COMMAND_PTR                    ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define QuadDec_L_INTRRUPT_CAUSE_REG             (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define QuadDec_L_INTRRUPT_CAUSE_PTR             ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define QuadDec_L_CONTROL_REG                    (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__CTRL )
#define QuadDec_L_CONTROL_PTR                    ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__CTRL )
#define QuadDec_L_STATUS_REG                     (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__STATUS )
#define QuadDec_L_STATUS_PTR                     ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__STATUS )
#define QuadDec_L_COUNTER_REG                    (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__COUNTER )
#define QuadDec_L_COUNTER_PTR                    ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__COUNTER )
#define QuadDec_L_COMP_CAP_REG                   (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__CC )
#define QuadDec_L_COMP_CAP_PTR                   ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__CC )
#define QuadDec_L_COMP_CAP_BUF_REG               (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__CC_BUFF )
#define QuadDec_L_COMP_CAP_BUF_PTR               ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__CC_BUFF )
#define QuadDec_L_PERIOD_REG                     (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__PERIOD )
#define QuadDec_L_PERIOD_PTR                     ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__PERIOD )
#define QuadDec_L_PERIOD_BUF_REG                 (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define QuadDec_L_PERIOD_BUF_PTR                 ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define QuadDec_L_TRIG_CONTROL0_REG              (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define QuadDec_L_TRIG_CONTROL0_PTR              ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define QuadDec_L_TRIG_CONTROL1_REG              (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define QuadDec_L_TRIG_CONTROL1_PTR              ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define QuadDec_L_TRIG_CONTROL2_REG              (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define QuadDec_L_TRIG_CONTROL2_PTR              ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define QuadDec_L_INTERRUPT_REQ_REG              (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__INTR )
#define QuadDec_L_INTERRUPT_REQ_PTR              ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__INTR )
#define QuadDec_L_INTERRUPT_SET_REG              (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__INTR_SET )
#define QuadDec_L_INTERRUPT_SET_PTR              ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__INTR_SET )
#define QuadDec_L_INTERRUPT_MASK_REG             (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__INTR_MASK )
#define QuadDec_L_INTERRUPT_MASK_PTR             ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__INTR_MASK )
#define QuadDec_L_INTERRUPT_MASKED_REG           (*(reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__INTR_MASKED )
#define QuadDec_L_INTERRUPT_MASKED_PTR           ( (reg32 *) QuadDec_L_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define QuadDec_L_MASK                           ((uint32)QuadDec_L_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define QuadDec_L_RELOAD_CC_SHIFT                (0u)
#define QuadDec_L_RELOAD_PERIOD_SHIFT            (1u)
#define QuadDec_L_PWM_SYNC_KILL_SHIFT            (2u)
#define QuadDec_L_PWM_STOP_KILL_SHIFT            (3u)
#define QuadDec_L_PRESCALER_SHIFT                (8u)
#define QuadDec_L_UPDOWN_SHIFT                   (16u)
#define QuadDec_L_ONESHOT_SHIFT                  (18u)
#define QuadDec_L_QUAD_MODE_SHIFT                (20u)
#define QuadDec_L_INV_OUT_SHIFT                  (20u)
#define QuadDec_L_INV_COMPL_OUT_SHIFT            (21u)
#define QuadDec_L_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define QuadDec_L_RELOAD_CC_MASK                 ((uint32)(QuadDec_L_1BIT_MASK        <<  \
                                                                            QuadDec_L_RELOAD_CC_SHIFT))
#define QuadDec_L_RELOAD_PERIOD_MASK             ((uint32)(QuadDec_L_1BIT_MASK        <<  \
                                                                            QuadDec_L_RELOAD_PERIOD_SHIFT))
#define QuadDec_L_PWM_SYNC_KILL_MASK             ((uint32)(QuadDec_L_1BIT_MASK        <<  \
                                                                            QuadDec_L_PWM_SYNC_KILL_SHIFT))
#define QuadDec_L_PWM_STOP_KILL_MASK             ((uint32)(QuadDec_L_1BIT_MASK        <<  \
                                                                            QuadDec_L_PWM_STOP_KILL_SHIFT))
#define QuadDec_L_PRESCALER_MASK                 ((uint32)(QuadDec_L_8BIT_MASK        <<  \
                                                                            QuadDec_L_PRESCALER_SHIFT))
#define QuadDec_L_UPDOWN_MASK                    ((uint32)(QuadDec_L_2BIT_MASK        <<  \
                                                                            QuadDec_L_UPDOWN_SHIFT))
#define QuadDec_L_ONESHOT_MASK                   ((uint32)(QuadDec_L_1BIT_MASK        <<  \
                                                                            QuadDec_L_ONESHOT_SHIFT))
#define QuadDec_L_QUAD_MODE_MASK                 ((uint32)(QuadDec_L_3BIT_MASK        <<  \
                                                                            QuadDec_L_QUAD_MODE_SHIFT))
#define QuadDec_L_INV_OUT_MASK                   ((uint32)(QuadDec_L_2BIT_MASK        <<  \
                                                                            QuadDec_L_INV_OUT_SHIFT))
#define QuadDec_L_MODE_MASK                      ((uint32)(QuadDec_L_3BIT_MASK        <<  \
                                                                            QuadDec_L_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define QuadDec_L_CAPTURE_SHIFT                  (0u)
#define QuadDec_L_COUNT_SHIFT                    (2u)
#define QuadDec_L_RELOAD_SHIFT                   (4u)
#define QuadDec_L_STOP_SHIFT                     (6u)
#define QuadDec_L_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define QuadDec_L_CAPTURE_MASK                   ((uint32)(QuadDec_L_2BIT_MASK        <<  \
                                                                  QuadDec_L_CAPTURE_SHIFT))
#define QuadDec_L_COUNT_MASK                     ((uint32)(QuadDec_L_2BIT_MASK        <<  \
                                                                  QuadDec_L_COUNT_SHIFT))
#define QuadDec_L_RELOAD_MASK                    ((uint32)(QuadDec_L_2BIT_MASK        <<  \
                                                                  QuadDec_L_RELOAD_SHIFT))
#define QuadDec_L_STOP_MASK                      ((uint32)(QuadDec_L_2BIT_MASK        <<  \
                                                                  QuadDec_L_STOP_SHIFT))
#define QuadDec_L_START_MASK                     ((uint32)(QuadDec_L_2BIT_MASK        <<  \
                                                                  QuadDec_L_START_SHIFT))

/* MASK */
#define QuadDec_L_1BIT_MASK                      ((uint32)0x01u)
#define QuadDec_L_2BIT_MASK                      ((uint32)0x03u)
#define QuadDec_L_3BIT_MASK                      ((uint32)0x07u)
#define QuadDec_L_6BIT_MASK                      ((uint32)0x3Fu)
#define QuadDec_L_8BIT_MASK                      ((uint32)0xFFu)
#define QuadDec_L_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define QuadDec_L_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define QuadDec_L_PWM_PR_INIT_VALUE              (1u)

#endif /* End CY_TCPWM_QuadDec_L_H */

/* [] END OF FILE */
