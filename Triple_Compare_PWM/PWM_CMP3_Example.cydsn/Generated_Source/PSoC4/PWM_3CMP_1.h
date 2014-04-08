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

#ifndef PWM_3CMP_1_HEADER
#define PWM_3CMP_1_HEADER

#include "cytypes.h"
#include "cyfitter.h"
#include <device.h>

// A0 register and pointer definitions
#define PWM_3CMP_1_A0_PTR			((reg8 *) PWM_3CMP_1_datapath_u0__A0_REG)
#define PWM_3CMP_1_A0_REG			(*(reg8 *) PWM_3CMP_1_datapath_u0__A0_REG)

// A1 register and pointer definitions
#define PWM_3CMP_1_A1_PTR			((reg8 *) PWM_3CMP_1_datapath_u0__A1_REG)
#define PWM_3CMP_1_A1_REG			(*(reg8 *) PWM_3CMP_1_datapath_u0__A1_REG)

// D0 register and pointer definitions
#define PWM_3CMP_1_D0_PTR			((reg8 *) PWM_3CMP_1_datapath_u0__D0_REG)
#define PWM_3CMP_1_D0_REG			(*(reg8 *) PWM_3CMP_1_datapath_u0__D0_REG)

// D1 register and pointer definitions
#define PWM_3CMP_1_D1_PTR			((reg8 *) PWM_3CMP_1_datapath_u0__D1_REG)
#define PWM_3CMP_1_D1_REG			(*(reg8 *) PWM_3CMP_1_datapath_u0__D1_REG)

// F0 register and pointer definitions
#define PWM_3CMP_1_F0_PTR			((reg8 *) PWM_3CMP_1_datapath_u0__F0_REG)
#define PWM_3CMP_1_F0_REG			(*(reg8 *) PWM_3CMP_1_datapath_u0__F0_REG)

// F1 register and pointer definitions
#define PWM_3CMP_1_F1_PTR			((reg8 *) PWM_3CMP_1_datapath_u0__F1_REG)
#define PWM_3CMP_1_F1_REG			(*(reg8 *) PWM_3CMP_1_datapath_u0__F1_REG)

// AUX CTL register and pointer definitions
#define PWM_3CMP_1_AUX_CTL_A_PTR	((reg8 *) PWM_3CMP_1_datapath_u0__DP_AUX_CTL_REG)
#define PWM_3CMP_1_AUX_CTL_A_REG	(*(reg8 *) PWM_3CMP_1_datapath_u0__DP_AUX_CTL_REG)

// A0 A1 register and pointer definitions
#define PWM_3CMP_1_A0_A1_PTR		((reg16 *) PWM_3CMP_1_datapath_u0__A0_A1_REG)
#define PWM_3CMP_1_A0_A1_REG		(*(reg16 *) PWM_3CMP_1_datapath_u0__A0_A1_REG)

// D0 D1 register and pointer definitions
#define PWM_3CMP_1_D0_D1_PTR		((reg16 *) PWM_3CMP_1_datapath_u0__D0_D1_REG)
#define PWM_3CMP_1_D0_D1_REG		(*(reg16 *) PWM_3CMP_1_datapath_u0__D0_D1_REG)

// F0 F1 register and pointer definitions
#define PWM_3CMP_1_F0_F1_PTR		((reg16 *) PWM_3CMP_1_datapath_u0__F0_F1_REG)
#define PWM_3CMP_1_F0_F1_REG		(*(reg16 *) PWM_3CMP_1_datapath_u0__F0_F1_REG)

// AUX CTL definitions
//  ----------------- MASKS ----------------------
#define PWM_3CMP_1_F1_LEVEL_MASK				(0x08u)
#define PWM_3CMP_1_F0_LEVEL_MASK				(0x04u)
#define PWM_3CMP_1_F1_SINGLE_BUFFER_MASK		(0x02u)
#define PWM_3CMP_1_F0_SINGLE_BUFFER_MASK		(0x01u)

//  ----------------- MODES ----------------------
#define PWM_3CMP_1_F1_LEVEL_MODE_0			(0u)
#define PWM_3CMP_1_F1_LEVEL_MODE_1			(1u)

#define PWM_3CMP_1_F0_LEVEL_MODE_0			(0u)
#define PWM_3CMP_1_F0_LEVEL_MODE_1			(1u)

#define PWM_3CMP_1_F1_SINGLE_BUFFER_DISABLE	(0u)
#define PWM_3CMP_1_F1_SINGLE_BUFFER_ENABLE	(1u)

#define PWM_3CMP_1_F0_SINGLE_BUFFER_DISABLE	(0u)
#define PWM_3CMP_1_F0_SINGLE_BUFFER_ENABLE	(1u)

// ----------------- SHIFT -----------------------
#define PWM_3CMP_1_F1_LEVEL_SHIFT				(3u)
#define PWM_3CMP_1_F0_LEVEL_SHIFT				(2u)
#define PWM_3CMP_1_F1_SINGLE_BUFFER_SHIFT		(1u)
#define PWM_3CMP_1_F0_SINGLE_BUFFER_SHIFT		(0u)

//-------------------------------------------------
#define PWM_3CMP_1_ReadPeriod()					CY_GET_REG8(PWM_3CMP_1_F0_PTR)

#define PWM_3CMP_1_WritePeriod(period)			CY_SET_REG8(PWM_3CMP_1_F0_PTR, (uint8)(period))

#define PWM_3CMP_1_ReadCompare0()					CY_GET_REG8(PWM_3CMP_1_D0_PTR)
#define PWM_3CMP_1_ReadCompare1()					CY_GET_REG8(PWM_3CMP_1_D1_PTR)
#define PWM_3CMP_1_ReadCompare2()					CY_GET_REG8(PWM_3CMP_1_F1_PTR)

#define PWM_3CMP_1_WriteCompare0(compare)			CY_SET_REG8(PWM_3CMP_1_D0_PTR, (uint8)(compare))
#define PWM_3CMP_1_WriteCompare1(compare)			CY_SET_REG8(PWM_3CMP_1_D1_PTR, (uint8)(compare))
#define PWM_3CMP_1_WriteCompare2(compare)			CY_SET_REG8(PWM_3CMP_1_F1_PTR, (uint8)(compare))

#define PWM_3CMP_1_ReadCounter0()					CY_GET_REG8(PWM_3CMP_1_A0_PTR)
#define PWM_3CMP_1_ReadCounter1()					CY_GET_REG8(PWM_3CMP_1_A1_PTR)

#define PWM_3CMP_1_WriteCounter0(value)			CY_SET_REG8(PWM_3CMP_1_A0_PTR, (uint8)(value))
#define PWM_3CMP_1_WriteCounter1(value)			CY_SET_REG8(PWM_3CMP_1_A1_PTR, (uint8)(value))

#define PWM_3CMP_1_WriteIntensity0(intensity)		PWM_3CMP_1_WriteCompare0((~(uint8)(intensity)))
#define PWM_3CMP_1_WriteIntensity1(intensity)		PWM_3CMP_1_WriteCompare1((~(uint8)(intensity)))
#define PWM_3CMP_1_WriteIntensity2(intensity)		PWM_3CMP_1_WriteCompare2((~(uint8)(intensity)))

void PWM_3CMP_1_Start();
void PWM_3CMP_1_Write_RGB(uint32 color);


#endif
//[] END OF FILE
