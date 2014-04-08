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

#include <control.h>

#define UINT8_MAX   255
#define UINT16_MAX  65535

#define CONTROL_MOTOR_CMP_LINE  40000

#define CONTROL_MODE_IDLE       0
#define CONTROL_MODE_FIND_LINE  1
#define CONTROL_MODE_FOL_LINE   2
#define CONTROL_MODE_OBSTACLE   3
#define CONTROL_MODE_LIGHT      4
#define CONTROL_MODE_TEMP       5
#define CONTROL_MODE_REMOTE     6
#define CONTROL_MODE_PROXIMITY  7
#define CONTROL_MODE_LOW_BATT   8
#define CONTROL_MODE_TEST       9

#define CONTROL_MODE_DEFAULT    CONTROL_MODE_IDLE

uint8 control_mode_current;
uint32 control_timerID;

typedef struct _control_mode
{
    void (* fnEnterMode)(); 	// function to execute on entry to this mode
	void (* fnHandleMode)(); 	// function to execute during this mode
	void (* fnExitMode)();		// function to execute on exit from this mode
} control_mode;

void control_mode_idle_Enter( void );
void control_mode_idle_Update( void );
void control_mode_idle_Exit( void );

void control_mode_findLine_Enter( void );
void control_mode_findLine_Update( void );
void control_mode_findLine_Exit( void );

void control_mode_folLine_Enter( void );
void control_mode_folLine_Update( void );
void control_mode_folLine_Exit( void );

void control_mode_obstacle_Enter( void );
void control_mode_obstacle_Update( void );
void control_mode_obstacle_Exit( void );

void control_mode_light_Enter( void );
void control_mode_light_Update( void );
void control_mode_light_Exit( void );

void control_mode_temp_Enter( void );
void control_mode_temp_Update( void );
void control_mode_temp_Exit( void );

void control_mode_remote_Enter( void );
void control_mode_remote_Update( void );
void control_mode_remote_Exit( void );

void control_mode_proximity_Enter( void );
void control_mode_proximity_Update( void );
void control_mode_proximity_Exit( void );

void control_mode_lowBatt_Enter( void );
void control_mode_lowBatt_Update( void );
void control_mode_lowBatt_Exit( void );

void control_mode_test_Enter( void );
void control_mode_test_Update( void );
void control_mode_test_Exit( void );

const control_mode control_mode_array[] = 
{
     /* This control mode:       */ /* mode entry function: */      /* mode update function: */     /* mode exit function: */
    {/* CONTROL_MODE_IDLE        */ &control_mode_idle_Enter,       &control_mode_idle_Update,      &control_mode_idle_Exit,        },
    {/* CONTROL_MODE_FIND_LINE   */ &control_mode_findLine_Enter,   &control_mode_findLine_Update,  &control_mode_findLine_Exit,    },
    {/* CONTROL_MODE_FOL_LINE    */ &control_mode_folLine_Enter,    &control_mode_folLine_Update,   &control_mode_folLine_Exit,     },
    {/* CONTROL_MODE_OBSTACLE    */ &control_mode_obstacle_Enter,   &control_mode_obstacle_Update,  &control_mode_obstacle_Exit,    },
    {/* CONTROL_MODE_LIGHT       */ &control_mode_light_Enter,      &control_mode_light_Update,     &control_mode_light_Exit,       },
    {/* CONTROL_MODE_TEMP        */ &control_mode_temp_Enter,       &control_mode_temp_Update,      &control_mode_temp_Exit,        },
    {/* CONTROL_MODE_REMOTE      */ &control_mode_remote_Enter,     &control_mode_remote_Update,    &control_mode_remote_Exit,      },
    {/* CONTROL_MODE_PROXIMITY   */ &control_mode_proximity_Enter,  &control_mode_proximity_Update, &control_mode_proximity_Exit,   },
    {/* CONTROL_MODE_LOW_BATT    */ &control_mode_lowBatt_Enter,    &control_mode_lowBatt_Update,   &control_mode_lowBatt_Exit,     },
    {/* CONTROL_MODE_TEST        */ &control_mode_test_Enter,       &control_mode_test_Update,      &control_mode_test_Exit,        },
};

//Function to enter the current mode using the function pointer array
void control_enterCurrentMode(void)
{
	(*control_mode_array[control_mode_current].fnEnterMode)();//execute the current state's "handle" behavior
}

//Function to handle the current mode using the function pointer array
void control_handleCurrentMode(void)
{
	//execute the current state's "handle" behavior
	(*control_mode_array[control_mode_current].fnHandleMode)();
}

//Function to exit the current state using the function pointer array
void control_exitCurrentMode(void)
{
	(*control_mode_array[control_mode_current].fnExitMode)();//execute the current state's "handle" behavior
}

void control_Start( void )
{
    SysTimers_Start();
    
    control_mode_current = CONTROL_MODE_DEFAULT;
    control_enterCurrentMode();
}

void control_IterateControl(void)
{
    static uint16 buttonDebounce;
    static uint8 buttonNewPress;
    
    //update button debounce variables
    //detect a new buttonpress event (button is active low)
    if((!buttonNewPress) && (buttonDebounce==0x8000) && (!P0_7_Button_Read()))
    {
        buttonNewPress = 0xff;
    }
    //update the button debounce variable
    buttonDebounce <<= 1;
    if(P0_7_Button_Read())
    {
        buttonDebounce |= 0x01;
    }
    
    //check for actionable events, update state
    if(sensors_getVBat_mV() <= SENSORS_VBAT_MV_LOW) //low battery
    {
        control_exitCurrentMode();
        control_mode_current = CONTROL_MODE_LOW_BATT;
        control_enterCurrentMode();
    }
    else if(buttonNewPress && (control_mode_current != CONTROL_MODE_LOW_BATT)) //switch pressed
    {
        control_exitCurrentMode();
        
        //clear the "new button press" flag
        buttonNewPress = 0;
        
        //change in and out of idle mode on buttonpress
        if(control_mode_current == CONTROL_MODE_IDLE)
        {
            control_mode_current = CONTROL_MODE_FIND_LINE;                
        }
        else
        {
            control_mode_current = CONTROL_MODE_IDLE;
        }

        control_enterCurrentMode();            
    }
    //else if( CapSense_CheckIsWidgetActive(CapSense_SENSOR_PROXIMITYSENSOR_0__PROX) && (control_mode_current != CONTROL_MODE_LOW_BATT) && (control_mode_current != CONTROL_MODE_IDLE)&& (control_mode_current != CONTROL_MODE_PROXIMITY)) //proximity detected
    else if( 0x00 ) //proximity detected
    {
        control_exitCurrentMode();
        control_mode_current = CONTROL_MODE_PROXIMITY;
        control_enterCurrentMode();
    }
    else if((sensors_getDistance_mm() <= SENSORS_DIST_MM_LIMIT) && ((control_mode_current == CONTROL_MODE_FIND_LINE) || (control_mode_current == CONTROL_MODE_FOL_LINE))) //obstacle detected
    {
        control_exitCurrentMode();
        control_mode_current = CONTROL_MODE_OBSTACLE;
        control_enterCurrentMode();
    }
    else if(sensors_getLineSensorBitField() && (control_mode_current == CONTROL_MODE_FIND_LINE)) //line detected
    {
        control_exitCurrentMode();
        control_mode_current = CONTROL_MODE_FOL_LINE;
        control_enterCurrentMode();
    }
    else if((!sensors_getLineSensorBitField()) && (control_mode_current == CONTROL_MODE_FOL_LINE)) //line lost
    {
        control_exitCurrentMode();
        control_mode_current = CONTROL_MODE_FIND_LINE;
        control_enterCurrentMode();
    }
    //return to line seeking from prox or distance timeout?
    
    control_handleCurrentMode();
}

void control_mode_idle_Enter( void )
{

}
void control_mode_idle_Update( void )
{

}
void control_mode_idle_Exit( void )
{

}

void control_mode_findLine_Enter( void )
{
    //set PWMs to full duty cycle, full steam ahead
    motors_SetPWM( CONTROL_MOTOR_CMP_LINE, CONTROL_MOTOR_CMP_LINE );
    motors_SetDir( MOTORS_DIR_R_FORWARD | MOTORS_DIR_L_FORWARD );
}
void control_mode_findLine_Update( void )
{

}
void control_mode_findLine_Exit( void )
{
    //stop the motors
    motors_SetPWM(0, 0);
}

void control_mode_folLine_Enter( void )
{
//    //set PWMs to full duty cycle, full steam ahead
//    motors_SetPWM( CONTROL_MOTOR_CMP_LINE, CONTROL_MOTOR_CMP_LINE );
//    motors_SetDir( MOTORS_DIR_R_FORWARD | MOTORS_DIR_L_FORWARD );
    
    //initialize PID control variables
    pid_reset_control();
    
    //configure timer for PID (update every 200 us)
    control_timerID = SysTimers_GetTimer(SysTimers_TICKS_PER_SECOND / 200);  // 5 kHz
}
void control_mode_folLine_Update( void )
{
    uint8 updatedControl;
    
    //update the control loop if enough time has passed
    if(SysTimers_GetTimerStatus(control_timerID))
    {
        //get the updated control value
        updatedControl = pid_get_updated_control();
        
        //write this value to the motor driver
        motors_WriteControl_i16(updatedControl);
    }
}
void control_mode_folLine_Exit( void )
{
    //stop the motors
    motors_SetPWM(0, 0);
    
    //release the timer
    SysTimers_ReleaseTimer(control_timerID);
}

void control_mode_obstacle_Enter( void )
{

}
void control_mode_obstacle_Update( void )
{

}
void control_mode_obstacle_Exit( void )
{

}

void control_mode_light_Enter( void )
{

}
void control_mode_light_Update( void )
{

}
void control_mode_light_Exit( void )
{

}

void control_mode_temp_Enter( void )
{

}
void control_mode_temp_Update( void )
{

}
void control_mode_temp_Exit( void )
{

}

void control_mode_remote_Enter( void )
{

}
void control_mode_remote_Update( void )
{

}
void control_mode_remote_Exit( void )
{

}

void control_mode_proximity_Enter( void )
{

}
void control_mode_proximity_Update( void )
{

}
void control_mode_proximity_Exit( void )
{

}

void control_mode_lowBatt_Enter( void )
{
    
}
void control_mode_lowBatt_Update( void )
{
    
}
void control_mode_lowBatt_Exit( void )
{
    
}

void control_mode_test_Enter( void )
{
    //setup timer
    control_timerID = SysTimers_GetTimer(SysTimers_TICKS_PER_SECOND / 1000);  // 1 kHz
}
void control_mode_test_Update( void )
{
    //update the control loop if enough time has passed
    if(SysTimers_GetTimerStatus(control_timerID))
    {

        static uint16 PWM_Compare;
        static uint8 dir;
        
        //LineSensorValue = sensors_getLineSensorBitField();
        
        
        //PWM_Compare = (getDistanceValue() - 600) * (65535 / 500);
//        PWM_Compare += 256;
//        
//        if(PWM_Compare>(65535-256))
//        {
//            dir = !dir;
//            PWM_Compare=0;
//        }
        PWM_Compare = MOTORS_PWM_COMPARE_MIN_3V7;//sensors_getProximityCountsFiltered()<<7;
        //PWM_Compare = sensors_getDistance_mm();//LineSensorValue<<8;
        
        motors_SetPWM(PWM_Compare, PWM_Compare);

        if(dir)
        {
            motors_SetDir( MOTORS_DIR_R_BACKWARD | MOTORS_DIR_L_BACKWARD);
        }
        else
        {
            motors_SetDir( MOTORS_DIR_R_FORWARD | MOTORS_DIR_L_FORWARD);
        }

        //CyDelay(1);
    }
}
void control_mode_test_Exit( void )
{
    //release timer
    SysTimers_ReleaseTimer(control_timerID);
}

//old line following code
//    switch(LineSensorValue){
//		case 0b00011000:
//        case 0b00111000:
//        case 0b00010000:
//        case 0b00001000:
//        case 0b00011100:
//            //keep going straight if the line is in the middle
//			motors_SetDir( MOTORS_DIR_R_FORWARD | MOTORS_DIR_L_FORWARD);
//            motors_SetPWM( CONTROL_MOTOR_CMP_LINE, CONTROL_MOTOR_CMP_LINE );
//			break;
//        case 0b00110000:
//        case 0b00100000:
//        case 0b01110000:
//        case 0b11111000:
//        case 0b01100000:
//        case 0b11110000:
//        case 0b01000000:
//        case 0b11100000:
//        case 0b11000000:
//        case 0b10000000:
//            //turn left if the line is on the left side
//            motors_SetDir( MOTORS_DIR_R_FORWARD | MOTORS_DIR_L_BACKWARD);
//            motors_SetPWM(CONTROL_MOTOR_CMP_LINE, 0);
//			break;
//        case 0b00001100:
//        case 0b00000100:
//        case 0b00001110:
//        case 0b00011111:
//        case 0b00000110:
//        case 0b00001111:
//        case 0b00000010:
//        case 0b00000111:
//        case 0b00000011:
//        case 0b00000001:
//            //turn right if the line is on the right side
//            motors_SetDir( MOTORS_DIR_R_BACKWARD | MOTORS_DIR_L_FORWARD);
//            motors_SetPWM(0, CONTROL_MOTOR_CMP_LINE);
//			break;
//        case 0b00000000:
//		default:
//            //back up if we've lost the line, or anything weird happens
//			motors_SetDir( MOTORS_DIR_R_BACKWARD | MOTORS_DIR_L_BACKWARD);
//			break;
//	}

/* [] END OF FILE */
