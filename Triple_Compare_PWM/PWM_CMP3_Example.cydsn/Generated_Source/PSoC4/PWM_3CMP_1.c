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
#include "PWM_3CMP_1.h"

/*******************************************************************************
* Function Name: PWM_3CMP_1_Start()
********************************************************************************
*
* Summary:
*  This function starts the 3-Compare PWM
*
* Parameters: None

* Return:
*   None
*
*******************************************************************************/
void PWM_3CMP_1_Start()
{
	uint8 interruptState;

	/* Enter critical section - AUX_CTL is shared by multiple hardware Components */
	interruptState = CyEnterCriticalSection();

	/* Enable FIFO0 and FIFO1 in single buffer mode */
	PWM_3CMP_1_AUX_CTL_A_REG |= (PWM_3CMP_1_F0_SINGLE_BUFFER_ENABLE << PWM_3CMP_1_F0_SINGLE_BUFFER_SHIFT);
	PWM_3CMP_1_AUX_CTL_A_REG |= (PWM_3CMP_1_F1_SINGLE_BUFFER_ENABLE << PWM_3CMP_1_F1_SINGLE_BUFFER_SHIFT);
	
	/* Exit critical section */
	CyExitCriticalSection(interruptState);
	
	/* Don't write period as 255, because compares are less-than compares, and this would not allow putting all LEDs completely OFF */
	PWM_3CMP_1_WritePeriod(254);
	
	return;
}

/*******************************************************************************
* Function Name: PWM_3CMP_1_Write_RGB()
********************************************************************************
*
* Summary:
*  Function to simplify writing an RGB value to the PWM. 
*
* Parameters: 32-bit color encoded as 0x00RRGGBB, where R is pwm0, G is pwm1 and B is pwm2

* Return:
*   None
*
*******************************************************************************/
void PWM_3CMP_1_Write_RGB(uint32 color)
{
    PWM_3CMP_1_WriteIntensity0(((color & 0xFF0000u) >> 16));
    PWM_3CMP_1_WriteIntensity1(((color & 0xFF00u) >> 8));
    PWM_3CMP_1_WriteIntensity2((color & 0xFFu));
}

/* [] END OF FILE */
