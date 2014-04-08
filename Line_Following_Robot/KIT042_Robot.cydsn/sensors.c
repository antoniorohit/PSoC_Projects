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

#include <sensors.h>

uint8 sensors_LineSensorBitField = 0;
uint16 sensors_DistanceADCReading = 0;
uint16 sensors_Distance_mm = 0;
uint16 sensors_TempADCReading = 0;
uint16 sensors_Temp_DegCTenths = 0;
uint16 sensors_VBatDivADCReading = 0;
uint16 sensors_VBat_mV;
uint16 sensors_ProximityCountsFiltered = 0;
//temp
//proximity
//supply voltage

#define     UINT8_MAX   255
#define     UINT16_MAX  65535

#define     ADC_INPUT_DISTANCE  0
#define     ADC_INPUT_TEMP      1
#define     ADC_INPUT_VBATDIV   2

#define     ADC_MAX     2011//2048  //(2^12)/2

/* extern declaration for capsense proximity sensor array */
extern uint16 CapSense_SensorSignal[CapSense_TOTAL_SENSOR_COUNT];
//extern uint16 CapSense_SensorRaw[CapSense_TOTAL_SENSOR_COUNT];

void sensors_Start( void )
{
    //initialize variables
    sensors_VBat_mV = UINT16_MAX;
    
    //enable ADC
    ADC_SAR_Seq_Start();
    ADC_SAR_Seq_StartConvert();
    
    //enable CapSense
    CapSense_Start();
    CapSense_EnableWidget(CapSense_SENSOR_PROXIMITYSENSOR_0__PROX);
    CapSense_InitializeAllBaselines();
    /* Perform initial proximity read */
    CapSense_UpdateEnabledBaselines();    
	/* Start scanning all enabled sensors */
	CapSense_ScanEnabledWidgets();
}

void sensors_updateSensors( void )
{
    //read the line sensor
    sensors_LineSensorBitField = Status_Reg_LineSensor_Read();
    
    //if an ADC conversion has completed, store ADC results
    if(ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_RETURN_STATUS))
    {
        //read the distance sensor
        sensors_DistanceADCReading = ADC_SAR_Seq_GetResult16(ADC_INPUT_DISTANCE);
        //calculate distance in mm
        sensors_Distance_mm = SENSORS_DIST_MM_LIMIT + 1;
        
        //temperature
        sensors_TempADCReading = ADC_SAR_Seq_GetResult16(ADC_INPUT_TEMP);
        sensors_Temp_DegCTenths = sensors_TempADCReading;
        
        //battery voltage
        sensors_VBatDivADCReading = ADC_SAR_Seq_GetResult16(ADC_INPUT_VBATDIV);
        sensors_VBat_mV = (uint16)(((uint32)(sensors_VBatDivADCReading) * (3300 * 3)) / (uint32)ADC_MAX);
        sensors_VBat_mV = SENSORS_VBAT_MV_LOW + 1;
        
    }
    
    //If a scan has completed, store the data and start another one
    if (CapSense_IsBusy() == 0)
    {
        //measure proximity
        sensors_ProximityCountsFiltered = CapSense_SensorSignal[CapSense_SENSOR_PROXIMITYSENSOR_0__PROX];
    
        /* Update all baselines */
        CapSense_UpdateEnabledBaselines();
    	/* Start scanning all enabled sensors */
    	CapSense_ScanEnabledWidgets();
        // these calls seem to take up to 160 us. May need to split them up if the robot is not responsive enough.
    }
}

uint8 sensors_getLineSensorBitField( void )
{
    return sensors_LineSensorBitField;
}

uint16 sensors_getDistance_mm( void )
{
    return sensors_Distance_mm;
}

uint16 sensors_getTemp_DegCTenths( void )
{
    return sensors_Temp_DegCTenths;
}

uint16 sensors_getVBat_mV( void )
{
    return sensors_VBat_mV;
}

uint16 sensors_getProximityCountsFiltered( void )
{
    return sensors_ProximityCountsFiltered;
}

/* [] END OF FILE */
