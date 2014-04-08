/*******************************************************************************
* File Name: QuadDec_R.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the QuadDec_R
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

#if !defined(CY_TCPWM_QuadDec_R_H)
#define CY_TCPWM_QuadDec_R_H

#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} QuadDec_R_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  QuadDec_R_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* TCPWM Configuration */
#define QuadDec_R_CONFIG                         (3lu)

/* Quad Mode */
/* Parameters */
#define QuadDec_R_QUAD_ENCODING_MODES            (2lu)

/* Signal modes */
#define QuadDec_R_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define QuadDec_R_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define QuadDec_R_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define QuadDec_R_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define QuadDec_R_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define QuadDec_R_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define QuadDec_R_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define QuadDec_R_TC_RUN_MODE                    (0lu)
#define QuadDec_R_TC_COUNTER_MODE                (0lu)
#define QuadDec_R_TC_COMP_CAP_MODE               (2lu)
#define QuadDec_R_TC_PRESCALER                   (0lu)

/* Signal modes */
#define QuadDec_R_TC_RELOAD_SIGNAL_MODE          (0lu)
#define QuadDec_R_TC_COUNT_SIGNAL_MODE           (3lu)
#define QuadDec_R_TC_START_SIGNAL_MODE           (0lu)
#define QuadDec_R_TC_STOP_SIGNAL_MODE            (0lu)
#define QuadDec_R_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define QuadDec_R_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define QuadDec_R_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define QuadDec_R_TC_START_SIGNAL_PRESENT        (0lu)
#define QuadDec_R_TC_STOP_SIGNAL_PRESENT         (0lu)
#define QuadDec_R_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define QuadDec_R_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define QuadDec_R_PWM_KILL_EVENT                 (0lu)
#define QuadDec_R_PWM_STOP_EVENT                 (0lu)
#define QuadDec_R_PWM_MODE                       (4lu)
#define QuadDec_R_PWM_OUT_N_INVERT               (0lu)
#define QuadDec_R_PWM_OUT_INVERT                 (0lu)
#define QuadDec_R_PWM_ALIGN                      (0lu)
#define QuadDec_R_PWM_RUN_MODE                   (0lu)
#define QuadDec_R_PWM_DEAD_TIME_CYCLE            (0lu)
#define QuadDec_R_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define QuadDec_R_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define QuadDec_R_PWM_COUNT_SIGNAL_MODE          (3lu)
#define QuadDec_R_PWM_START_SIGNAL_MODE          (0lu)
#define QuadDec_R_PWM_STOP_SIGNAL_MODE           (0lu)
#define QuadDec_R_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define QuadDec_R_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define QuadDec_R_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define QuadDec_R_PWM_START_SIGNAL_PRESENT       (0lu)
#define QuadDec_R_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define QuadDec_R_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define QuadDec_R_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define QuadDec_R_TC_PERIOD_VALUE                (65535lu)
#define QuadDec_R_TC_COMPARE_VALUE               (65535lu)
#define QuadDec_R_TC_COMPARE_BUF_VALUE           (65535lu)
#define QuadDec_R_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define QuadDec_R_PWM_PERIOD_VALUE               (65535lu)
#define QuadDec_R_PWM_PERIOD_BUF_VALUE           (65535lu)
#define QuadDec_R_PWM_PERIOD_SWAP                (0lu)
#define QuadDec_R_PWM_COMPARE_VALUE              (65535lu)
#define QuadDec_R_PWM_COMPARE_BUF_VALUE          (65535lu)
#define QuadDec_R_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define QuadDec_R__LEFT 0
#define QuadDec_R__RIGHT 1
#define QuadDec_R__CENTER 2
#define QuadDec_R__ASYMMETRIC 3

#define QuadDec_R__X1 0
#define QuadDec_R__X2 1
#define QuadDec_R__X4 2

#define QuadDec_R__PWM 4
#define QuadDec_R__PWM_DT 5
#define QuadDec_R__PWM_PR 6

#define QuadDec_R__INVERSE 1
#define QuadDec_R__DIRECT 0

#define QuadDec_R__CAPTURE 2
#define QuadDec_R__COMPARE 0

#define QuadDec_R__TRIG_LEVEL 3
#define QuadDec_R__TRIG_RISING 0
#define QuadDec_R__TRIG_FALLING 1
#define QuadDec_R__TRIG_BOTH 2

#define QuadDec_R__INTR_MASK_TC 1
#define QuadDec_R__INTR_MASK_CC_MATCH 2
#define QuadDec_R__INTR_MASK_NONE 0
#define QuadDec_R__INTR_MASK_TC_CC 3

#define QuadDec_R__UNCONFIG 8
#define QuadDec_R__TIMER 1
#define QuadDec_R__QUAD 3
#define QuadDec_R__PWM_SEL 7

#define QuadDec_R__COUNT_UP 0
#define QuadDec_R__COUNT_DOWN 1
#define QuadDec_R__COUNT_UPDOWN0 2
#define QuadDec_R__COUNT_UPDOWN1 3


/* Prescaler */
#define QuadDec_R_PRESCALE_DIVBY1                ((uint32)(0u << QuadDec_R_PRESCALER_SHIFT))
#define QuadDec_R_PRESCALE_DIVBY2                ((uint32)(1u << QuadDec_R_PRESCALER_SHIFT))
#define QuadDec_R_PRESCALE_DIVBY4                ((uint32)(2u << QuadDec_R_PRESCALER_SHIFT))
#define QuadDec_R_PRESCALE_DIVBY8                ((uint32)(3u << QuadDec_R_PRESCALER_SHIFT))
#define QuadDec_R_PRESCALE_DIVBY16               ((uint32)(4u << QuadDec_R_PRESCALER_SHIFT))
#define QuadDec_R_PRESCALE_DIVBY32               ((uint32)(5u << QuadDec_R_PRESCALER_SHIFT))
#define QuadDec_R_PRESCALE_DIVBY64               ((uint32)(6u << QuadDec_R_PRESCALER_SHIFT))
#define QuadDec_R_PRESCALE_DIVBY128              ((uint32)(7u << QuadDec_R_PRESCALER_SHIFT))

/* TCPWM set modes */
#define QuadDec_R_MODE_TIMER_COMPARE             ((uint32)(QuadDec_R__COMPARE         <<  \
                                                                  QuadDec_R_MODE_SHIFT))
#define QuadDec_R_MODE_TIMER_CAPTURE             ((uint32)(QuadDec_R__CAPTURE         <<  \
                                                                  QuadDec_R_MODE_SHIFT))
#define QuadDec_R_MODE_QUAD                      ((uint32)(QuadDec_R__QUAD            <<  \
                                                                  QuadDec_R_MODE_SHIFT))
#define QuadDec_R_MODE_PWM                       ((uint32)(QuadDec_R__PWM             <<  \
                                                                  QuadDec_R_MODE_SHIFT))
#define QuadDec_R_MODE_PWM_DT                    ((uint32)(QuadDec_R__PWM_DT          <<  \
                                                                  QuadDec_R_MODE_SHIFT))
#define QuadDec_R_MODE_PWM_PR                    ((uint32)(QuadDec_R__PWM_PR          <<  \
                                                                  QuadDec_R_MODE_SHIFT))

/* Quad Modes */
#define QuadDec_R_MODE_X1                        ((uint32)(QuadDec_R__X1              <<  \
                                                                  QuadDec_R_QUAD_MODE_SHIFT))
#define QuadDec_R_MODE_X2                        ((uint32)(QuadDec_R__X2              <<  \
                                                                  QuadDec_R_QUAD_MODE_SHIFT))
#define QuadDec_R_MODE_X4                        ((uint32)(QuadDec_R__X4              <<  \
                                                                  QuadDec_R_QUAD_MODE_SHIFT))

/* Counter modes */
#define QuadDec_R_COUNT_UP                       ((uint32)(QuadDec_R__COUNT_UP        <<  \
                                                                  QuadDec_R_UPDOWN_SHIFT))
#define QuadDec_R_COUNT_DOWN                     ((uint32)(QuadDec_R__COUNT_DOWN      <<  \
                                                                  QuadDec_R_UPDOWN_SHIFT))
#define QuadDec_R_COUNT_UPDOWN0                  ((uint32)(QuadDec_R__COUNT_UPDOWN0   <<  \
                                                                  QuadDec_R_UPDOWN_SHIFT))
#define QuadDec_R_COUNT_UPDOWN1                  ((uint32)(QuadDec_R__COUNT_UPDOWN1   <<  \
                                                                  QuadDec_R_UPDOWN_SHIFT))

/* PWM output invert */
#define QuadDec_R_INVERT_LINE                    ((uint32)(QuadDec_R__INVERSE         <<  \
                                                                  QuadDec_R_INV_OUT_SHIFT))
#define QuadDec_R_INVERT_LINE_N                  ((uint32)(QuadDec_R__INVERSE         <<  \
                                                                  QuadDec_R_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define QuadDec_R_TRIG_RISING                    (QuadDec_R__TRIG_RISING)
#define QuadDec_R_TRIG_FALLING                   (QuadDec_R__TRIG_FALLING)
#define QuadDec_R_TRIG_BOTH                      (QuadDec_R__TRIG_BOTH)
#define QuadDec_R_TRIG_LEVEL                     (QuadDec_R__TRIG_LEVEL)

/* Interrupt mask */
#define QuadDec_R_INTR_MASK_TC                   (QuadDec_R__INTR_MASK_TC)
#define QuadDec_R_INTR_MASK_CC_MATCH             (QuadDec_R__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define QuadDec_R_CC_MATCH_SET                   (0x00u)
#define QuadDec_R_CC_MATCH_CLEAR                 (0x01u)
#define QuadDec_R_CC_MATCH_INVERT                (0x02u)
#define QuadDec_R_CC_MATCH_NO_CHANGE             (0x03u)
#define QuadDec_R_OVERLOW_SET                    (0x00u)
#define QuadDec_R_OVERLOW_CLEAR                  (0x04u)
#define QuadDec_R_OVERLOW_INVERT                 (0x08u)
#define QuadDec_R_OVERLOW_NO_CHANGE              (0x0Cu)
#define QuadDec_R_UNDERFLOW_SET                  (0x00u)
#define QuadDec_R_UNDERFLOW_CLEAR                (0x10u)
#define QuadDec_R_UNDERFLOW_INVERT               (0x20u)
#define QuadDec_R_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define QuadDec_R_PWM_MODE_LEFT                  (QuadDec_R_CC_MATCH_CLEAR        |   \
                                                         QuadDec_R_OVERLOW_SET           |   \
                                                         QuadDec_R_UNDERFLOW_NO_CHANGE)
#define QuadDec_R_PWM_MODE_RIGHT                 (QuadDec_R_CC_MATCH_SET          |   \
                                                         QuadDec_R_OVERLOW_NO_CHANGE     |   \
                                                         QuadDec_R_UNDERFLOW_CLEAR)
#define QuadDec_R_PWM_MODE_CENTER                (QuadDec_R_CC_MATCH_INVERT       |   \
                                                         QuadDec_R_OVERLOW_NO_CHANGE     |   \
                                                         QuadDec_R_UNDERFLOW_CLEAR)
#define QuadDec_R_PWM_MODE_ASYM                  (QuadDec_R_CC_MATCH_NO_CHANGE    |   \
                                                         QuadDec_R_OVERLOW_SET           |   \
                                                         QuadDec_R_UNDERFLOW_CLEAR )

/* Command operations without condition */
#define QuadDec_R_CMD_CAPTURE                    (0u)
#define QuadDec_R_CMD_RELOAD                     (8u)
#define QuadDec_R_CMD_STOP                       (16u)
#define QuadDec_R_CMD_START                      (24u)

/* Status */
#define QuadDec_R_STATUS_DOWN                    (1u)
#define QuadDec_R_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   QuadDec_R_Init(void);
void   QuadDec_R_Enable(void);
void   QuadDec_R_Start(void);
void   QuadDec_R_Stop(void);

void   QuadDec_R_SetMode(uint32 mode);
void   QuadDec_R_SetCounterMode(uint32 counterMode);
void   QuadDec_R_SetPWMMode(uint32 modeMask);
void   QuadDec_R_SetQDMode(uint32 qdMode);

void   QuadDec_R_SetPrescaler(uint32 prescaler);
void   QuadDec_R_TriggerCommand(uint32 mask, uint32 command);
void   QuadDec_R_SetOneShot(uint32 oneShotEnable);
uint32 QuadDec_R_ReadStatus(void);

void   QuadDec_R_SetPWMSyncKill(uint32 syncKillEnable);
void   QuadDec_R_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   QuadDec_R_SetPWMDeadTime(uint32 deadTime);
void   QuadDec_R_SetPWMInvert(uint32 mask);

void   QuadDec_R_SetInterruptMode(uint32 interruptMask);
uint32 QuadDec_R_GetInterruptSourceMasked(void);
uint32 QuadDec_R_GetInterruptSource(void);
void   QuadDec_R_ClearInterrupt(uint32 interruptMask);
void   QuadDec_R_SetInterrupt(uint32 interruptMask);

void   QuadDec_R_WriteCounter(uint32 count);
uint32 QuadDec_R_ReadCounter(void);

uint32 QuadDec_R_ReadCapture(void);
uint32 QuadDec_R_ReadCaptureBuf(void);

void   QuadDec_R_WritePeriod(uint32 period);
uint32 QuadDec_R_ReadPeriod(void);
void   QuadDec_R_WritePeriodBuf(uint32 periodBuf);
uint32 QuadDec_R_ReadPeriodBuf(void);

void   QuadDec_R_WriteCompare(uint32 compare);
uint32 QuadDec_R_ReadCompare(void);
void   QuadDec_R_WriteCompareBuf(uint32 compareBuf);
uint32 QuadDec_R_ReadCompareBuf(void);

void   QuadDec_R_SetPeriodSwap(uint32 swapEnable);
void   QuadDec_R_SetCompareSwap(uint32 swapEnable);

void   QuadDec_R_SetCaptureMode(uint32 triggerMode);
void   QuadDec_R_SetReloadMode(uint32 triggerMode);
void   QuadDec_R_SetStartMode(uint32 triggerMode);
void   QuadDec_R_SetStopMode(uint32 triggerMode);
void   QuadDec_R_SetCountMode(uint32 triggerMode);

void   QuadDec_R_SaveConfig(void);
void   QuadDec_R_RestoreConfig(void);
void   QuadDec_R_Sleep(void);
void   QuadDec_R_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define QuadDec_R_BLOCK_CONTROL_REG              (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define QuadDec_R_BLOCK_CONTROL_PTR              ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define QuadDec_R_COMMAND_REG                    (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define QuadDec_R_COMMAND_PTR                    ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define QuadDec_R_INTRRUPT_CAUSE_REG             (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define QuadDec_R_INTRRUPT_CAUSE_PTR             ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define QuadDec_R_CONTROL_REG                    (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__CTRL )
#define QuadDec_R_CONTROL_PTR                    ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__CTRL )
#define QuadDec_R_STATUS_REG                     (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__STATUS )
#define QuadDec_R_STATUS_PTR                     ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__STATUS )
#define QuadDec_R_COUNTER_REG                    (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__COUNTER )
#define QuadDec_R_COUNTER_PTR                    ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__COUNTER )
#define QuadDec_R_COMP_CAP_REG                   (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__CC )
#define QuadDec_R_COMP_CAP_PTR                   ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__CC )
#define QuadDec_R_COMP_CAP_BUF_REG               (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__CC_BUFF )
#define QuadDec_R_COMP_CAP_BUF_PTR               ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__CC_BUFF )
#define QuadDec_R_PERIOD_REG                     (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__PERIOD )
#define QuadDec_R_PERIOD_PTR                     ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__PERIOD )
#define QuadDec_R_PERIOD_BUF_REG                 (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define QuadDec_R_PERIOD_BUF_PTR                 ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define QuadDec_R_TRIG_CONTROL0_REG              (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define QuadDec_R_TRIG_CONTROL0_PTR              ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define QuadDec_R_TRIG_CONTROL1_REG              (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define QuadDec_R_TRIG_CONTROL1_PTR              ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define QuadDec_R_TRIG_CONTROL2_REG              (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define QuadDec_R_TRIG_CONTROL2_PTR              ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define QuadDec_R_INTERRUPT_REQ_REG              (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__INTR )
#define QuadDec_R_INTERRUPT_REQ_PTR              ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__INTR )
#define QuadDec_R_INTERRUPT_SET_REG              (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__INTR_SET )
#define QuadDec_R_INTERRUPT_SET_PTR              ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__INTR_SET )
#define QuadDec_R_INTERRUPT_MASK_REG             (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__INTR_MASK )
#define QuadDec_R_INTERRUPT_MASK_PTR             ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__INTR_MASK )
#define QuadDec_R_INTERRUPT_MASKED_REG           (*(reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__INTR_MASKED )
#define QuadDec_R_INTERRUPT_MASKED_PTR           ( (reg32 *) QuadDec_R_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define QuadDec_R_MASK                           ((uint32)QuadDec_R_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define QuadDec_R_RELOAD_CC_SHIFT                (0u)
#define QuadDec_R_RELOAD_PERIOD_SHIFT            (1u)
#define QuadDec_R_PWM_SYNC_KILL_SHIFT            (2u)
#define QuadDec_R_PWM_STOP_KILL_SHIFT            (3u)
#define QuadDec_R_PRESCALER_SHIFT                (8u)
#define QuadDec_R_UPDOWN_SHIFT                   (16u)
#define QuadDec_R_ONESHOT_SHIFT                  (18u)
#define QuadDec_R_QUAD_MODE_SHIFT                (20u)
#define QuadDec_R_INV_OUT_SHIFT                  (20u)
#define QuadDec_R_INV_COMPL_OUT_SHIFT            (21u)
#define QuadDec_R_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define QuadDec_R_RELOAD_CC_MASK                 ((uint32)(QuadDec_R_1BIT_MASK        <<  \
                                                                            QuadDec_R_RELOAD_CC_SHIFT))
#define QuadDec_R_RELOAD_PERIOD_MASK             ((uint32)(QuadDec_R_1BIT_MASK        <<  \
                                                                            QuadDec_R_RELOAD_PERIOD_SHIFT))
#define QuadDec_R_PWM_SYNC_KILL_MASK             ((uint32)(QuadDec_R_1BIT_MASK        <<  \
                                                                            QuadDec_R_PWM_SYNC_KILL_SHIFT))
#define QuadDec_R_PWM_STOP_KILL_MASK             ((uint32)(QuadDec_R_1BIT_MASK        <<  \
                                                                            QuadDec_R_PWM_STOP_KILL_SHIFT))
#define QuadDec_R_PRESCALER_MASK                 ((uint32)(QuadDec_R_8BIT_MASK        <<  \
                                                                            QuadDec_R_PRESCALER_SHIFT))
#define QuadDec_R_UPDOWN_MASK                    ((uint32)(QuadDec_R_2BIT_MASK        <<  \
                                                                            QuadDec_R_UPDOWN_SHIFT))
#define QuadDec_R_ONESHOT_MASK                   ((uint32)(QuadDec_R_1BIT_MASK        <<  \
                                                                            QuadDec_R_ONESHOT_SHIFT))
#define QuadDec_R_QUAD_MODE_MASK                 ((uint32)(QuadDec_R_3BIT_MASK        <<  \
                                                                            QuadDec_R_QUAD_MODE_SHIFT))
#define QuadDec_R_INV_OUT_MASK                   ((uint32)(QuadDec_R_2BIT_MASK        <<  \
                                                                            QuadDec_R_INV_OUT_SHIFT))
#define QuadDec_R_MODE_MASK                      ((uint32)(QuadDec_R_3BIT_MASK        <<  \
                                                                            QuadDec_R_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define QuadDec_R_CAPTURE_SHIFT                  (0u)
#define QuadDec_R_COUNT_SHIFT                    (2u)
#define QuadDec_R_RELOAD_SHIFT                   (4u)
#define QuadDec_R_STOP_SHIFT                     (6u)
#define QuadDec_R_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define QuadDec_R_CAPTURE_MASK                   ((uint32)(QuadDec_R_2BIT_MASK        <<  \
                                                                  QuadDec_R_CAPTURE_SHIFT))
#define QuadDec_R_COUNT_MASK                     ((uint32)(QuadDec_R_2BIT_MASK        <<  \
                                                                  QuadDec_R_COUNT_SHIFT))
#define QuadDec_R_RELOAD_MASK                    ((uint32)(QuadDec_R_2BIT_MASK        <<  \
                                                                  QuadDec_R_RELOAD_SHIFT))
#define QuadDec_R_STOP_MASK                      ((uint32)(QuadDec_R_2BIT_MASK        <<  \
                                                                  QuadDec_R_STOP_SHIFT))
#define QuadDec_R_START_MASK                     ((uint32)(QuadDec_R_2BIT_MASK        <<  \
                                                                  QuadDec_R_START_SHIFT))

/* MASK */
#define QuadDec_R_1BIT_MASK                      ((uint32)0x01u)
#define QuadDec_R_2BIT_MASK                      ((uint32)0x03u)
#define QuadDec_R_3BIT_MASK                      ((uint32)0x07u)
#define QuadDec_R_6BIT_MASK                      ((uint32)0x3Fu)
#define QuadDec_R_8BIT_MASK                      ((uint32)0xFFu)
#define QuadDec_R_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define QuadDec_R_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define QuadDec_R_PWM_PR_INIT_VALUE              (1u)

#endif /* End CY_TCPWM_QuadDec_R_H */

/* [] END OF FILE */
