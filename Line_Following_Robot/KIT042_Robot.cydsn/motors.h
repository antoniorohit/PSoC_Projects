/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>

#define     MOTORS_DIR_R_FORWARD    0
#define     MOTORS_DIR_R_BACKWARD   1
#define     MOTORS_DIR_L_FORWARD    0
#define     MOTORS_DIR_L_BACKWARD   2

#define     MOTORS_PWM_COMPARE_MIN_3V   30000
#define     MOTORS_PWM_COMPARE_MIN_3V7  30000
#define     MOTORS_PWM_COMPARE_MIN_7V2  20000
#define     MOTORS_PWM_COMPARE_MIN_11V1 20000
#define     MOTORS_PWM_COMPARE_MIN_12V  12000

#define     MOTORS_PWM_COMPARE_MAX_7V2  40000

#define     MOTORS_PWM_COMPARE_MAX      65535

void motors_Start(void);
void motors_SetDir(uint8 motorDirections);
void motors_SetPWM(uint16 dutyCycleRight, uint16 dutyCycleLeft);
void motors_WriteControl_i16(int16 motor_control);
void motors_WriteControl_ui8(uint8 motor_control);

/* [] END OF FILE */
