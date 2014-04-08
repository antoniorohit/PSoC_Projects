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
#include <pid.h>

#define UINT8_MAX           255
#define UINT16_MAX          65535

#define PID_INT8_LINE_ERR   128
#define PID_INT8_LINE_MAX   127
#define PID_INT8_LINE_MIN   -127

/* Set this to limit the error range. Setting this too small could lead to
	early input saturation, which would make the loop response sluggish. But 
	setting this too high could lead to registor rollover down the signal 
	chain. */
    //note our error is bounded by our return values, so we don't need this step
#define	PID_ERR_SAT_L			-2000
#define	PID_ERR_SAT_H			2000
	
/* Set the input gain as powers of 2. This has the affect of reducing the
	total gain as well as trimming the input resolution. */
#define	PID_PRE_GAIN			0

/* These are the coefficients for a two-zero network. This can be related
	back to Kp, Ki, and Kd if needed. */
#define	PID_A1					1800
#define	PID_A2					0//-13703
#define	PID_A3					0

/* This is the output saturation for the compensator. Typically the control 
 	input to any system starts from zero and terminates to some positive 
	value (i.e. PWM input from 0 to 255). The limit must account for the 
	post gain stage (i.e. a post gain of 2^16 combined with an output limit
	of 255 leads to 255 * 65536 = 16711680). */
#define	PID_OUTPUT_SAT_L		0
#define	PID_OUTPUT_SAT_H		UINT8_MAX << PID_POST_GAIN

/* Set the output gain as powers of 2. This has the affect of reducing the
	total gain. It is generally optimal to keep this restricted to byte 
	alignment for optimal code generation (i.e. 8 or 16).*/
#define	PID_POST_GAIN			16

//these variables must be stored between iterations of the PID control loop.
//they must also be reset when re-starting the control system
int16 pid_err_z1, pid_err_z2;
uint32 pid_area;

int8 pid_decode_line_position (uint8 LineSensorValue);

void pid_reset_control(void)
{
    //initialize values to 0
    pid_err_z1 = 0;
    pid_err_z2 = 0;
    pid_area = PID_OUTPUT_SAT_H / 2; //0; //initialize to middle value?
}

int16 pid_get_updated_control(void)
{    
    uint8 LineSensorValue;
    int8 pid_in;
    int8 pid_ref = 0;  //we always want to keep the line centered in the sensor
    int16 pid_err_z0;
    uint8 pid_out;
    
    //read the line position
    LineSensorValue = sensors_getLineSensorBitField();
    
    //decode the line position
    pid_in = pid_decode_line_position(LineSensorValue);

    /* Compute the error */
    pid_err_z0 = pid_ref - pid_in;
    /* Saturate... limit the error within the design range of the compensator. */
    //note our error is bounded by our return values, so we don't need this step
//    if (pid_err_z0 > PID_ERR_SAT_H) 
//    {
//       pid_err_z0 = PID_ERR_SAT_H;
//    }
//    else if (pid_err_z0 < PID_ERR_SAT_L) 
//    {
//       pid_err_z0 = PID_ERR_SAT_L;
//    }
    
    /* Tweak the front-end gain */
    pid_err_z0 >>= PID_PRE_GAIN;
    /* Process PID compensation */
    pid_area += ((int16)pid_err_z0 * (int32)PID_A1);
    pid_area += ((int16)pid_err_z1 * (int32)PID_A2);
    //pid_area += ((int16)pid_err_z2 * (int32)PID_A3); //z2 unused
    
    /* Track the history */
    //pid_err_z2 = pid_err_z1; //z2 unused
    pid_err_z1 = pid_err_z0;
    
    /* Saturate... limit the output within the design range of the modulator */
    if (((int32)pid_area) > PID_OUTPUT_SAT_H) 
    {
       pid_area = (uint32)PID_OUTPUT_SAT_H;
    }
    else if (((int32)pid_area) < PID_OUTPUT_SAT_L) 
    {
        pid_area = (uint32)PID_OUTPUT_SAT_L;
    }
    
    /* Write to the modulator */
    pid_out = (int16)(pid_area >> PID_POST_GAIN);
    
    return pid_out;
}

int8 pid_decode_line_position (uint8 LineSensorValue)
{
    static int8 linePosition;
    
    //determine line position
    switch(LineSensorValue)
    {
        case 0b10000000:
        case 0b11000000:
        case 0b11100000:
        case 0b11110000:
        case 0b11111000:
            //full left
            linePosition = PID_INT8_LINE_MIN;
            break;
        case 0b01000000:
            linePosition = (int8) (((int16)PID_INT8_LINE_MIN)*5/8);
            break;
        case 0b01100000:
		    linePosition = (int8) (((int16)PID_INT8_LINE_MIN)*4/8);
            break;
        case 0b00100000:
        case 0b01110000:
            linePosition = (int8) (((int16)PID_INT8_LINE_MIN)*3/8);
            break;
        case 0b00110000:
        case 0b01111000:
            linePosition = (int8) (((int16)PID_INT8_LINE_MIN)*2/8);
            break;
        case 0b00111000:
        case 0b00010000:
            linePosition = (int8) (((int16)PID_INT8_LINE_MIN)*1/8);
			break;
		case 0b00011000:
        case 0b00111100:
        case 0b01111110:
            //in the middle
            linePosition = 0;
			break;
        case 0b00001000:
        case 0b00011100:
            linePosition = (int8) (((int16)PID_INT8_LINE_MAX)*1/8);
			break;
        case 0b00001100:
        case 0b00011110:
            linePosition = (int8) (((int16)PID_INT8_LINE_MAX)*2/8);
            break;
        case 0b00000100:
        case 0b00001110:
            linePosition = (int8) (((int16)PID_INT8_LINE_MAX)*3/8);
            break;
        case 0b00000110:
            linePosition = (int8) (((int16)PID_INT8_LINE_MAX)*4/8);
            break;
        case 0b00000010:
            linePosition = (int8) (((int16)PID_INT8_LINE_MAX)*5/8);
            break;
        case 0b00011111:
        case 0b00001111:
        case 0b00000111:
        case 0b00000011:
        case 0b00000001:
            //full right
            linePosition = PID_INT8_LINE_MAX;
			break;
        case 0b00000000:
		default:
            //this means we lost the line
            //simply return the previous line position if it does (don't change the return value)
			break;
	}
    
    return linePosition;
}

/* [] END OF FILE */
