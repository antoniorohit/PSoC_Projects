/* ========================================
 *
 * The following firmware was developed by Cypress Semiconductor
 * This work is licensed under a Creative Commons Attribution 3.0 Unported License.
 * 
 * http://creativecommons.org/licenses/by/3.0/deed.en_US
 * 
 * You are free to:
 * -To Share — to copy, distribute and transmit the work 
 * -To Remix — to adapt the work 
 * -To make commercial use of the work
 *
 * ========================================
 */
 
 /* Example project to test out the triple compare PWM (in one UDB) 
  * Targeted at the PSoC 4 Pioneer Kit. 
  * Program the PSoC 4 with this project to see the RGB LED on board 
  * cycle through the entire color wheel
  */

#include <device.h>
#include <LED_RGB.h>

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Demonstrates the functionality of the 3-compare PWM and its APIs
*
* Parameters: None

* Return:
*   None
*
*******************************************************************************/
void main()
{
	uint16 i;

	PWM_3CMP_1_Start();

	PWM_3CMP_1_Write_RGB(0x00FF001F);

	CyDelay(1000);

	PWM_3CMP_1_WriteIntensity0(0);
	PWM_3CMP_1_WriteIntensity1(0);
	PWM_3CMP_1_WriteIntensity2(0);

	CyDelay(1000);
	
    for(;;)
    {
		i++;
		
		/* Use a function from the LED_RGB library */
		LED_RGB_SetColorCircle(i);

		CyDelayUs(100);
	}
}

/* [] END OF FILE */
