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

#define SENSORS_VBAT_MV_LOW     6800 //6.8V minimum
#define SENSORS_DIST_MM_LIMIT   100

void sensors_Start( void );

void sensors_updateSensors( void );

uint8 sensors_getLineSensorBitField( void );

uint16 sensors_getDistance_mm( void );
uint16 sensors_getTemp_DegCTenths( void );
uint16 sensors_getVBat_mV( void );

uint16 sensors_getProximityCountsFiltered( void );

/* [] END OF FILE */
