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
#include <motors.h>

#define     UINT8_MAX   255
#define     UINT16_MAX  65535

#define UINT8_1_4TH     UINT8_MAX * 1 / 4
#define UINT8_2_4TH     UINT8_MAX * 2 / 4
#define UINT8_3_4TH     UINT8_MAX * 3 / 4

void motors_Start(void)
{
    PWM_Motor_R_Start();
    PWM_Motor_L_Start();
}

void motors_SetDir(uint8 motorDirections)
{
    if(motorDirections & MOTORS_DIR_R_BACKWARD)
    {
        P0_1_DIR_R_Write(0xff);
    }
    else
    {
        P0_1_DIR_R_Write(0x00);
    }
    
    if(motorDirections & MOTORS_DIR_L_BACKWARD)
    {
        P0_3_DIR_L_Write(0xff);
    }
    else
    {
        P0_3_DIR_L_Write(0x00);
    }    
}

void motors_SetPWM(uint16 dutyCycleRight, uint16 dutyCycleLeft)
{
    PWM_Motor_R_WriteCompare(dutyCycleRight);
    PWM_Motor_L_WriteCompare(dutyCycleLeft);
}

void motors_WriteControl_i16(int16 motor_control)
{
    uint8 motors_dir;
    uint16 motors_dutyCycleLeft, motors_dutyCycleRight;
    
    if(motor_control == 0)
    {
        //full speed straight ahead
        motors_dir = MOTORS_DIR_R_FORWARD | MOTORS_DIR_L_FORWARD;
        motors_dutyCycleRight = MOTORS_PWM_COMPARE_MAX_7V2;
        motors_dutyCycleLeft = MOTORS_PWM_COMPARE_MAX_7V2;
    }
    else if (motor_control > 0)
    {
        //turn right
        //left motor full speed ahead
        motors_dutyCycleLeft = MOTORS_PWM_COMPARE_MAX_7V2;
        if(motor_control > (INT16_MAX / 2))
        {
            //very hard right, put right motor in reverse
            motors_dir = MOTORS_DIR_R_BACKWARD | MOTORS_DIR_L_FORWARD;
            motors_dutyCycleRight = MOTORS_PWM_COMPARE_MIN_7V2 + (uint16) (((MOTORS_PWM_COMPARE_MAX_7V2 - MOTORS_PWM_COMPARE_MIN_7V2) * ((int32)motor_control - (INT16_MAX / 2)))/ (INT16_MAX / 2));
        }
        else
        {
            //soft right, keep right motor in slow forward
            motors_dir = MOTORS_DIR_R_FORWARD | MOTORS_DIR_L_FORWARD;
            motors_dutyCycleRight = MOTORS_PWM_COMPARE_MIN_7V2 + (uint16) (((MOTORS_PWM_COMPARE_MAX_7V2 - MOTORS_PWM_COMPARE_MIN_7V2) * ((int32)(INT16_MAX / 2) - motor_control))/ (INT16_MAX / 2));
        }
    }
    else
    {
        //turn left
        //right motor full speed ahead
        motors_dutyCycleRight = MOTORS_PWM_COMPARE_MAX_7V2;
        if(motor_control < (-INT16_MAX / 2))
        {
            //very hard left, put left motor in reverse
            motors_dir = MOTORS_DIR_R_FORWARD | MOTORS_DIR_L_BACKWARD;
            motors_dutyCycleLeft = MOTORS_PWM_COMPARE_MIN_7V2 + (uint16) (((MOTORS_PWM_COMPARE_MAX_7V2 - MOTORS_PWM_COMPARE_MIN_7V2) * ((int32)-motor_control - (INT16_MAX / 2)))/ (INT16_MAX / 2));
        }
        else
        {
            //soft right, keep right motor in slow forward
            motors_dir = MOTORS_DIR_R_FORWARD | MOTORS_DIR_L_FORWARD;
            motors_dutyCycleLeft = MOTORS_PWM_COMPARE_MIN_7V2 + (uint16) (((MOTORS_PWM_COMPARE_MAX_7V2 - MOTORS_PWM_COMPARE_MIN_7V2) * ((int32)(INT16_MAX / 2) - - motor_control))/ (INT16_MAX / 2));
        }
    }
    
    motors_SetDir(motors_dir);
    motors_SetPWM(motors_dutyCycleRight, motors_dutyCycleLeft);
}

void motors_WriteControl_ui8(uint8 motor_control)
{
    uint8 motors_dir;
    uint16 motors_fastDutyCycle, motors_slowDutyCycle;
    uint16 motors_dutyCycleLeft, motors_dutyCycleRight;
    
    //set two duty cycles independently, then assign them to the sides
    //fast motor always at 100% duty cycle
    motors_fastDutyCycle = MOTORS_PWM_COMPARE_MAX_7V2;
    
    //set slow duty cycle based on control
    if(((motor_control%128) > UINT8_1_4TH) )
    {
        //duty cycle increasing with control
        motors_slowDutyCycle = MOTORS_PWM_COMPARE_MIN_7V2 + ((MOTORS_PWM_COMPARE_MAX_7V2 - MOTORS_PWM_COMPARE_MIN_7V2) * ((motor_control%128) - 64))/64;
    }
    else
    {
        //duty cycle decreasing with control
        motors_slowDutyCycle = MOTORS_PWM_COMPARE_MIN_7V2 + ((MOTORS_PWM_COMPARE_MAX_7V2 - MOTORS_PWM_COMPARE_MIN_7V2) * (64 - (motor_control%128)))/64;
    }
    
    //determine which motor is fast, which is slow, and what directions they are turning in
    if (motor_control < UINT8_2_4TH)
    {
        //turn right
        //left motor full speed ahead
        motors_dutyCycleLeft = motors_fastDutyCycle;
        //right motor has slower speed determined above
        motors_dutyCycleRight = motors_slowDutyCycle;
        
        //determine right motor direction
        if(motor_control < UINT8_1_4TH)
        {
            //very hard right, put right motor in reverse
            motors_dir = MOTORS_DIR_R_BACKWARD | MOTORS_DIR_L_FORWARD;
        }
        else
        {
            //soft right, keep right motor in slow forward
            motors_dir = MOTORS_DIR_R_FORWARD | MOTORS_DIR_L_FORWARD;
        }
    }
    else
    {
        //turn left
        //right motor full speed ahead
        motors_dutyCycleRight = MOTORS_PWM_COMPARE_MAX_7V2;
        //left motor has slower speed determined above
        motors_dutyCycleLeft = motors_slowDutyCycle;
        
        //determine left motor direction
        if(motor_control > UINT8_3_4TH)
        {
            //very hard left, put left motor in reverse
            motors_dir = MOTORS_DIR_R_FORWARD | MOTORS_DIR_L_BACKWARD;
        }
        else
        {
            //soft right, keep right motor in slow forward
            motors_dir = MOTORS_DIR_R_FORWARD | MOTORS_DIR_L_FORWARD;
        }
    }
    
    motors_SetDir(motors_dir);
    motors_SetPWM(motors_dutyCycleRight, motors_dutyCycleLeft);
}

/* [] END OF FILE */
