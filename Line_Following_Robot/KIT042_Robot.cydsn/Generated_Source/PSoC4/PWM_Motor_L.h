/*******************************************************************************
* File Name: PWM_Motor_L.h
* Version 1.0
*
* Description:
*  This file provides constants and parameter values for the PWM_Motor_L
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

#if !defined(CY_TCPWM_PWM_Motor_L_H)
#define CY_TCPWM_PWM_Motor_L_H

#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} PWM_Motor_L_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  PWM_Motor_L_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* TCPWM Configuration */
#define PWM_Motor_L_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define PWM_Motor_L_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define PWM_Motor_L_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define PWM_Motor_L_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define PWM_Motor_L_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define PWM_Motor_L_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define PWM_Motor_L_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define PWM_Motor_L_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define PWM_Motor_L_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define PWM_Motor_L_TC_RUN_MODE                    (0lu)
#define PWM_Motor_L_TC_COUNTER_MODE                (0lu)
#define PWM_Motor_L_TC_COMP_CAP_MODE               (2lu)
#define PWM_Motor_L_TC_PRESCALER                   (0lu)

/* Signal modes */
#define PWM_Motor_L_TC_RELOAD_SIGNAL_MODE          (0lu)
#define PWM_Motor_L_TC_COUNT_SIGNAL_MODE           (3lu)
#define PWM_Motor_L_TC_START_SIGNAL_MODE           (0lu)
#define PWM_Motor_L_TC_STOP_SIGNAL_MODE            (0lu)
#define PWM_Motor_L_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWM_Motor_L_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define PWM_Motor_L_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define PWM_Motor_L_TC_START_SIGNAL_PRESENT        (0lu)
#define PWM_Motor_L_TC_STOP_SIGNAL_PRESENT         (0lu)
#define PWM_Motor_L_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWM_Motor_L_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define PWM_Motor_L_PWM_KILL_EVENT                 (0lu)
#define PWM_Motor_L_PWM_STOP_EVENT                 (0lu)
#define PWM_Motor_L_PWM_MODE                       (4lu)
#define PWM_Motor_L_PWM_OUT_N_INVERT               (0lu)
#define PWM_Motor_L_PWM_OUT_INVERT                 (0lu)
#define PWM_Motor_L_PWM_ALIGN                      (0lu)
#define PWM_Motor_L_PWM_RUN_MODE                   (0lu)
#define PWM_Motor_L_PWM_DEAD_TIME_CYCLE            (0lu)
#define PWM_Motor_L_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define PWM_Motor_L_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define PWM_Motor_L_PWM_COUNT_SIGNAL_MODE          (3lu)
#define PWM_Motor_L_PWM_START_SIGNAL_MODE          (0lu)
#define PWM_Motor_L_PWM_STOP_SIGNAL_MODE           (0lu)
#define PWM_Motor_L_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWM_Motor_L_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define PWM_Motor_L_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define PWM_Motor_L_PWM_START_SIGNAL_PRESENT       (0lu)
#define PWM_Motor_L_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define PWM_Motor_L_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWM_Motor_L_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define PWM_Motor_L_TC_PERIOD_VALUE                (65535lu)
#define PWM_Motor_L_TC_COMPARE_VALUE               (65535lu)
#define PWM_Motor_L_TC_COMPARE_BUF_VALUE           (65535lu)
#define PWM_Motor_L_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define PWM_Motor_L_PWM_PERIOD_VALUE               (65535lu)
#define PWM_Motor_L_PWM_PERIOD_BUF_VALUE           (65535lu)
#define PWM_Motor_L_PWM_PERIOD_SWAP                (0lu)
#define PWM_Motor_L_PWM_COMPARE_VALUE              (0lu)
#define PWM_Motor_L_PWM_COMPARE_BUF_VALUE          (65535lu)
#define PWM_Motor_L_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define PWM_Motor_L__LEFT 0
#define PWM_Motor_L__RIGHT 1
#define PWM_Motor_L__CENTER 2
#define PWM_Motor_L__ASYMMETRIC 3

#define PWM_Motor_L__X1 0
#define PWM_Motor_L__X2 1
#define PWM_Motor_L__X4 2

#define PWM_Motor_L__PWM 4
#define PWM_Motor_L__PWM_DT 5
#define PWM_Motor_L__PWM_PR 6

#define PWM_Motor_L__INVERSE 1
#define PWM_Motor_L__DIRECT 0

#define PWM_Motor_L__CAPTURE 2
#define PWM_Motor_L__COMPARE 0

#define PWM_Motor_L__TRIG_LEVEL 3
#define PWM_Motor_L__TRIG_RISING 0
#define PWM_Motor_L__TRIG_FALLING 1
#define PWM_Motor_L__TRIG_BOTH 2

#define PWM_Motor_L__INTR_MASK_TC 1
#define PWM_Motor_L__INTR_MASK_CC_MATCH 2
#define PWM_Motor_L__INTR_MASK_NONE 0
#define PWM_Motor_L__INTR_MASK_TC_CC 3

#define PWM_Motor_L__UNCONFIG 8
#define PWM_Motor_L__TIMER 1
#define PWM_Motor_L__QUAD 3
#define PWM_Motor_L__PWM_SEL 7

#define PWM_Motor_L__COUNT_UP 0
#define PWM_Motor_L__COUNT_DOWN 1
#define PWM_Motor_L__COUNT_UPDOWN0 2
#define PWM_Motor_L__COUNT_UPDOWN1 3


/* Prescaler */
#define PWM_Motor_L_PRESCALE_DIVBY1                ((uint32)(0u << PWM_Motor_L_PRESCALER_SHIFT))
#define PWM_Motor_L_PRESCALE_DIVBY2                ((uint32)(1u << PWM_Motor_L_PRESCALER_SHIFT))
#define PWM_Motor_L_PRESCALE_DIVBY4                ((uint32)(2u << PWM_Motor_L_PRESCALER_SHIFT))
#define PWM_Motor_L_PRESCALE_DIVBY8                ((uint32)(3u << PWM_Motor_L_PRESCALER_SHIFT))
#define PWM_Motor_L_PRESCALE_DIVBY16               ((uint32)(4u << PWM_Motor_L_PRESCALER_SHIFT))
#define PWM_Motor_L_PRESCALE_DIVBY32               ((uint32)(5u << PWM_Motor_L_PRESCALER_SHIFT))
#define PWM_Motor_L_PRESCALE_DIVBY64               ((uint32)(6u << PWM_Motor_L_PRESCALER_SHIFT))
#define PWM_Motor_L_PRESCALE_DIVBY128              ((uint32)(7u << PWM_Motor_L_PRESCALER_SHIFT))

/* TCPWM set modes */
#define PWM_Motor_L_MODE_TIMER_COMPARE             ((uint32)(PWM_Motor_L__COMPARE         <<  \
                                                                  PWM_Motor_L_MODE_SHIFT))
#define PWM_Motor_L_MODE_TIMER_CAPTURE             ((uint32)(PWM_Motor_L__CAPTURE         <<  \
                                                                  PWM_Motor_L_MODE_SHIFT))
#define PWM_Motor_L_MODE_QUAD                      ((uint32)(PWM_Motor_L__QUAD            <<  \
                                                                  PWM_Motor_L_MODE_SHIFT))
#define PWM_Motor_L_MODE_PWM                       ((uint32)(PWM_Motor_L__PWM             <<  \
                                                                  PWM_Motor_L_MODE_SHIFT))
#define PWM_Motor_L_MODE_PWM_DT                    ((uint32)(PWM_Motor_L__PWM_DT          <<  \
                                                                  PWM_Motor_L_MODE_SHIFT))
#define PWM_Motor_L_MODE_PWM_PR                    ((uint32)(PWM_Motor_L__PWM_PR          <<  \
                                                                  PWM_Motor_L_MODE_SHIFT))

/* Quad Modes */
#define PWM_Motor_L_MODE_X1                        ((uint32)(PWM_Motor_L__X1              <<  \
                                                                  PWM_Motor_L_QUAD_MODE_SHIFT))
#define PWM_Motor_L_MODE_X2                        ((uint32)(PWM_Motor_L__X2              <<  \
                                                                  PWM_Motor_L_QUAD_MODE_SHIFT))
#define PWM_Motor_L_MODE_X4                        ((uint32)(PWM_Motor_L__X4              <<  \
                                                                  PWM_Motor_L_QUAD_MODE_SHIFT))

/* Counter modes */
#define PWM_Motor_L_COUNT_UP                       ((uint32)(PWM_Motor_L__COUNT_UP        <<  \
                                                                  PWM_Motor_L_UPDOWN_SHIFT))
#define PWM_Motor_L_COUNT_DOWN                     ((uint32)(PWM_Motor_L__COUNT_DOWN      <<  \
                                                                  PWM_Motor_L_UPDOWN_SHIFT))
#define PWM_Motor_L_COUNT_UPDOWN0                  ((uint32)(PWM_Motor_L__COUNT_UPDOWN0   <<  \
                                                                  PWM_Motor_L_UPDOWN_SHIFT))
#define PWM_Motor_L_COUNT_UPDOWN1                  ((uint32)(PWM_Motor_L__COUNT_UPDOWN1   <<  \
                                                                  PWM_Motor_L_UPDOWN_SHIFT))

/* PWM output invert */
#define PWM_Motor_L_INVERT_LINE                    ((uint32)(PWM_Motor_L__INVERSE         <<  \
                                                                  PWM_Motor_L_INV_OUT_SHIFT))
#define PWM_Motor_L_INVERT_LINE_N                  ((uint32)(PWM_Motor_L__INVERSE         <<  \
                                                                  PWM_Motor_L_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define PWM_Motor_L_TRIG_RISING                    (PWM_Motor_L__TRIG_RISING)
#define PWM_Motor_L_TRIG_FALLING                   (PWM_Motor_L__TRIG_FALLING)
#define PWM_Motor_L_TRIG_BOTH                      (PWM_Motor_L__TRIG_BOTH)
#define PWM_Motor_L_TRIG_LEVEL                     (PWM_Motor_L__TRIG_LEVEL)

/* Interrupt mask */
#define PWM_Motor_L_INTR_MASK_TC                   (PWM_Motor_L__INTR_MASK_TC)
#define PWM_Motor_L_INTR_MASK_CC_MATCH             (PWM_Motor_L__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define PWM_Motor_L_CC_MATCH_SET                   (0x00u)
#define PWM_Motor_L_CC_MATCH_CLEAR                 (0x01u)
#define PWM_Motor_L_CC_MATCH_INVERT                (0x02u)
#define PWM_Motor_L_CC_MATCH_NO_CHANGE             (0x03u)
#define PWM_Motor_L_OVERLOW_SET                    (0x00u)
#define PWM_Motor_L_OVERLOW_CLEAR                  (0x04u)
#define PWM_Motor_L_OVERLOW_INVERT                 (0x08u)
#define PWM_Motor_L_OVERLOW_NO_CHANGE              (0x0Cu)
#define PWM_Motor_L_UNDERFLOW_SET                  (0x00u)
#define PWM_Motor_L_UNDERFLOW_CLEAR                (0x10u)
#define PWM_Motor_L_UNDERFLOW_INVERT               (0x20u)
#define PWM_Motor_L_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define PWM_Motor_L_PWM_MODE_LEFT                  (PWM_Motor_L_CC_MATCH_CLEAR        |   \
                                                         PWM_Motor_L_OVERLOW_SET           |   \
                                                         PWM_Motor_L_UNDERFLOW_NO_CHANGE)
#define PWM_Motor_L_PWM_MODE_RIGHT                 (PWM_Motor_L_CC_MATCH_SET          |   \
                                                         PWM_Motor_L_OVERLOW_NO_CHANGE     |   \
                                                         PWM_Motor_L_UNDERFLOW_CLEAR)
#define PWM_Motor_L_PWM_MODE_CENTER                (PWM_Motor_L_CC_MATCH_INVERT       |   \
                                                         PWM_Motor_L_OVERLOW_NO_CHANGE     |   \
                                                         PWM_Motor_L_UNDERFLOW_CLEAR)
#define PWM_Motor_L_PWM_MODE_ASYM                  (PWM_Motor_L_CC_MATCH_NO_CHANGE    |   \
                                                         PWM_Motor_L_OVERLOW_SET           |   \
                                                         PWM_Motor_L_UNDERFLOW_CLEAR )

/* Command operations without condition */
#define PWM_Motor_L_CMD_CAPTURE                    (0u)
#define PWM_Motor_L_CMD_RELOAD                     (8u)
#define PWM_Motor_L_CMD_STOP                       (16u)
#define PWM_Motor_L_CMD_START                      (24u)

/* Status */
#define PWM_Motor_L_STATUS_DOWN                    (1u)
#define PWM_Motor_L_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   PWM_Motor_L_Init(void);
void   PWM_Motor_L_Enable(void);
void   PWM_Motor_L_Start(void);
void   PWM_Motor_L_Stop(void);

void   PWM_Motor_L_SetMode(uint32 mode);
void   PWM_Motor_L_SetCounterMode(uint32 counterMode);
void   PWM_Motor_L_SetPWMMode(uint32 modeMask);
void   PWM_Motor_L_SetQDMode(uint32 qdMode);

void   PWM_Motor_L_SetPrescaler(uint32 prescaler);
void   PWM_Motor_L_TriggerCommand(uint32 mask, uint32 command);
void   PWM_Motor_L_SetOneShot(uint32 oneShotEnable);
uint32 PWM_Motor_L_ReadStatus(void);

void   PWM_Motor_L_SetPWMSyncKill(uint32 syncKillEnable);
void   PWM_Motor_L_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   PWM_Motor_L_SetPWMDeadTime(uint32 deadTime);
void   PWM_Motor_L_SetPWMInvert(uint32 mask);

void   PWM_Motor_L_SetInterruptMode(uint32 interruptMask);
uint32 PWM_Motor_L_GetInterruptSourceMasked(void);
uint32 PWM_Motor_L_GetInterruptSource(void);
void   PWM_Motor_L_ClearInterrupt(uint32 interruptMask);
void   PWM_Motor_L_SetInterrupt(uint32 interruptMask);

void   PWM_Motor_L_WriteCounter(uint32 count);
uint32 PWM_Motor_L_ReadCounter(void);

uint32 PWM_Motor_L_ReadCapture(void);
uint32 PWM_Motor_L_ReadCaptureBuf(void);

void   PWM_Motor_L_WritePeriod(uint32 period);
uint32 PWM_Motor_L_ReadPeriod(void);
void   PWM_Motor_L_WritePeriodBuf(uint32 periodBuf);
uint32 PWM_Motor_L_ReadPeriodBuf(void);

void   PWM_Motor_L_WriteCompare(uint32 compare);
uint32 PWM_Motor_L_ReadCompare(void);
void   PWM_Motor_L_WriteCompareBuf(uint32 compareBuf);
uint32 PWM_Motor_L_ReadCompareBuf(void);

void   PWM_Motor_L_SetPeriodSwap(uint32 swapEnable);
void   PWM_Motor_L_SetCompareSwap(uint32 swapEnable);

void   PWM_Motor_L_SetCaptureMode(uint32 triggerMode);
void   PWM_Motor_L_SetReloadMode(uint32 triggerMode);
void   PWM_Motor_L_SetStartMode(uint32 triggerMode);
void   PWM_Motor_L_SetStopMode(uint32 triggerMode);
void   PWM_Motor_L_SetCountMode(uint32 triggerMode);

void   PWM_Motor_L_SaveConfig(void);
void   PWM_Motor_L_RestoreConfig(void);
void   PWM_Motor_L_Sleep(void);
void   PWM_Motor_L_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define PWM_Motor_L_BLOCK_CONTROL_REG              (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWM_Motor_L_BLOCK_CONTROL_PTR              ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWM_Motor_L_COMMAND_REG                    (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWM_Motor_L_COMMAND_PTR                    ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWM_Motor_L_INTRRUPT_CAUSE_REG             (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWM_Motor_L_INTRRUPT_CAUSE_PTR             ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWM_Motor_L_CONTROL_REG                    (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__CTRL )
#define PWM_Motor_L_CONTROL_PTR                    ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__CTRL )
#define PWM_Motor_L_STATUS_REG                     (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__STATUS )
#define PWM_Motor_L_STATUS_PTR                     ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__STATUS )
#define PWM_Motor_L_COUNTER_REG                    (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__COUNTER )
#define PWM_Motor_L_COUNTER_PTR                    ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__COUNTER )
#define PWM_Motor_L_COMP_CAP_REG                   (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__CC )
#define PWM_Motor_L_COMP_CAP_PTR                   ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__CC )
#define PWM_Motor_L_COMP_CAP_BUF_REG               (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWM_Motor_L_COMP_CAP_BUF_PTR               ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWM_Motor_L_PERIOD_REG                     (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__PERIOD )
#define PWM_Motor_L_PERIOD_PTR                     ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__PERIOD )
#define PWM_Motor_L_PERIOD_BUF_REG                 (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWM_Motor_L_PERIOD_BUF_PTR                 ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWM_Motor_L_TRIG_CONTROL0_REG              (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWM_Motor_L_TRIG_CONTROL0_PTR              ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWM_Motor_L_TRIG_CONTROL1_REG              (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWM_Motor_L_TRIG_CONTROL1_PTR              ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWM_Motor_L_TRIG_CONTROL2_REG              (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWM_Motor_L_TRIG_CONTROL2_PTR              ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWM_Motor_L_INTERRUPT_REQ_REG              (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__INTR )
#define PWM_Motor_L_INTERRUPT_REQ_PTR              ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__INTR )
#define PWM_Motor_L_INTERRUPT_SET_REG              (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__INTR_SET )
#define PWM_Motor_L_INTERRUPT_SET_PTR              ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__INTR_SET )
#define PWM_Motor_L_INTERRUPT_MASK_REG             (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWM_Motor_L_INTERRUPT_MASK_PTR             ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWM_Motor_L_INTERRUPT_MASKED_REG           (*(reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__INTR_MASKED )
#define PWM_Motor_L_INTERRUPT_MASKED_PTR           ( (reg32 *) PWM_Motor_L_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define PWM_Motor_L_MASK                           ((uint32)PWM_Motor_L_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define PWM_Motor_L_RELOAD_CC_SHIFT                (0u)
#define PWM_Motor_L_RELOAD_PERIOD_SHIFT            (1u)
#define PWM_Motor_L_PWM_SYNC_KILL_SHIFT            (2u)
#define PWM_Motor_L_PWM_STOP_KILL_SHIFT            (3u)
#define PWM_Motor_L_PRESCALER_SHIFT                (8u)
#define PWM_Motor_L_UPDOWN_SHIFT                   (16u)
#define PWM_Motor_L_ONESHOT_SHIFT                  (18u)
#define PWM_Motor_L_QUAD_MODE_SHIFT                (20u)
#define PWM_Motor_L_INV_OUT_SHIFT                  (20u)
#define PWM_Motor_L_INV_COMPL_OUT_SHIFT            (21u)
#define PWM_Motor_L_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define PWM_Motor_L_RELOAD_CC_MASK                 ((uint32)(PWM_Motor_L_1BIT_MASK        <<  \
                                                                            PWM_Motor_L_RELOAD_CC_SHIFT))
#define PWM_Motor_L_RELOAD_PERIOD_MASK             ((uint32)(PWM_Motor_L_1BIT_MASK        <<  \
                                                                            PWM_Motor_L_RELOAD_PERIOD_SHIFT))
#define PWM_Motor_L_PWM_SYNC_KILL_MASK             ((uint32)(PWM_Motor_L_1BIT_MASK        <<  \
                                                                            PWM_Motor_L_PWM_SYNC_KILL_SHIFT))
#define PWM_Motor_L_PWM_STOP_KILL_MASK             ((uint32)(PWM_Motor_L_1BIT_MASK        <<  \
                                                                            PWM_Motor_L_PWM_STOP_KILL_SHIFT))
#define PWM_Motor_L_PRESCALER_MASK                 ((uint32)(PWM_Motor_L_8BIT_MASK        <<  \
                                                                            PWM_Motor_L_PRESCALER_SHIFT))
#define PWM_Motor_L_UPDOWN_MASK                    ((uint32)(PWM_Motor_L_2BIT_MASK        <<  \
                                                                            PWM_Motor_L_UPDOWN_SHIFT))
#define PWM_Motor_L_ONESHOT_MASK                   ((uint32)(PWM_Motor_L_1BIT_MASK        <<  \
                                                                            PWM_Motor_L_ONESHOT_SHIFT))
#define PWM_Motor_L_QUAD_MODE_MASK                 ((uint32)(PWM_Motor_L_3BIT_MASK        <<  \
                                                                            PWM_Motor_L_QUAD_MODE_SHIFT))
#define PWM_Motor_L_INV_OUT_MASK                   ((uint32)(PWM_Motor_L_2BIT_MASK        <<  \
                                                                            PWM_Motor_L_INV_OUT_SHIFT))
#define PWM_Motor_L_MODE_MASK                      ((uint32)(PWM_Motor_L_3BIT_MASK        <<  \
                                                                            PWM_Motor_L_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define PWM_Motor_L_CAPTURE_SHIFT                  (0u)
#define PWM_Motor_L_COUNT_SHIFT                    (2u)
#define PWM_Motor_L_RELOAD_SHIFT                   (4u)
#define PWM_Motor_L_STOP_SHIFT                     (6u)
#define PWM_Motor_L_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define PWM_Motor_L_CAPTURE_MASK                   ((uint32)(PWM_Motor_L_2BIT_MASK        <<  \
                                                                  PWM_Motor_L_CAPTURE_SHIFT))
#define PWM_Motor_L_COUNT_MASK                     ((uint32)(PWM_Motor_L_2BIT_MASK        <<  \
                                                                  PWM_Motor_L_COUNT_SHIFT))
#define PWM_Motor_L_RELOAD_MASK                    ((uint32)(PWM_Motor_L_2BIT_MASK        <<  \
                                                                  PWM_Motor_L_RELOAD_SHIFT))
#define PWM_Motor_L_STOP_MASK                      ((uint32)(PWM_Motor_L_2BIT_MASK        <<  \
                                                                  PWM_Motor_L_STOP_SHIFT))
#define PWM_Motor_L_START_MASK                     ((uint32)(PWM_Motor_L_2BIT_MASK        <<  \
                                                                  PWM_Motor_L_START_SHIFT))

/* MASK */
#define PWM_Motor_L_1BIT_MASK                      ((uint32)0x01u)
#define PWM_Motor_L_2BIT_MASK                      ((uint32)0x03u)
#define PWM_Motor_L_3BIT_MASK                      ((uint32)0x07u)
#define PWM_Motor_L_6BIT_MASK                      ((uint32)0x3Fu)
#define PWM_Motor_L_8BIT_MASK                      ((uint32)0xFFu)
#define PWM_Motor_L_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define PWM_Motor_L_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define PWM_Motor_L_PWM_PR_INIT_VALUE              (1u)

#endif /* End CY_TCPWM_PWM_Motor_L_H */

/* [] END OF FILE */
