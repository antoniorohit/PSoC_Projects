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

#ifndef `$INSTANCE_NAME`_HEADER
#define `$INSTANCE_NAME`_HEADER

#include "cytypes.h"
#include "cyfitter.h"
#include <device.h>

// A0 register and pointer definitions
#define `$INSTANCE_NAME`_A0_PTR			((reg8 *) `$INSTANCE_NAME`_datapath_u0__A0_REG)
#define `$INSTANCE_NAME`_A0_REG			(*(reg8 *) `$INSTANCE_NAME`_datapath_u0__A0_REG)

// A1 register and pointer definitions
#define `$INSTANCE_NAME`_A1_PTR			((reg8 *) `$INSTANCE_NAME`_datapath_u0__A1_REG)
#define `$INSTANCE_NAME`_A1_REG			(*(reg8 *) `$INSTANCE_NAME`_datapath_u0__A1_REG)

// D0 register and pointer definitions
#define `$INSTANCE_NAME`_D0_PTR			((reg8 *) `$INSTANCE_NAME`_datapath_u0__D0_REG)
#define `$INSTANCE_NAME`_D0_REG			(*(reg8 *) `$INSTANCE_NAME`_datapath_u0__D0_REG)

// D1 register and pointer definitions
#define `$INSTANCE_NAME`_D1_PTR			((reg8 *) `$INSTANCE_NAME`_datapath_u0__D1_REG)
#define `$INSTANCE_NAME`_D1_REG			(*(reg8 *) `$INSTANCE_NAME`_datapath_u0__D1_REG)

// F0 register and pointer definitions
#define `$INSTANCE_NAME`_F0_PTR			((reg8 *) `$INSTANCE_NAME`_datapath_u0__F0_REG)
#define `$INSTANCE_NAME`_F0_REG			(*(reg8 *) `$INSTANCE_NAME`_datapath_u0__F0_REG)

// F1 register and pointer definitions
#define `$INSTANCE_NAME`_F1_PTR			((reg8 *) `$INSTANCE_NAME`_datapath_u0__F1_REG)
#define `$INSTANCE_NAME`_F1_REG			(*(reg8 *) `$INSTANCE_NAME`_datapath_u0__F1_REG)

// AUX CTL register and pointer definitions
#define `$INSTANCE_NAME`_AUX_CTL_A_PTR	((reg8 *) `$INSTANCE_NAME`_datapath_u0__DP_AUX_CTL_REG)
#define `$INSTANCE_NAME`_AUX_CTL_A_REG	(*(reg8 *) `$INSTANCE_NAME`_datapath_u0__DP_AUX_CTL_REG)

// A0 A1 register and pointer definitions
#define `$INSTANCE_NAME`_A0_A1_PTR		((reg16 *) `$INSTANCE_NAME`_datapath_u0__A0_A1_REG)
#define `$INSTANCE_NAME`_A0_A1_REG		(*(reg16 *) `$INSTANCE_NAME`_datapath_u0__A0_A1_REG)

// D0 D1 register and pointer definitions
#define `$INSTANCE_NAME`_D0_D1_PTR		((reg16 *) `$INSTANCE_NAME`_datapath_u0__D0_D1_REG)
#define `$INSTANCE_NAME`_D0_D1_REG		(*(reg16 *) `$INSTANCE_NAME`_datapath_u0__D0_D1_REG)

// F0 F1 register and pointer definitions
#define `$INSTANCE_NAME`_F0_F1_PTR		((reg16 *) `$INSTANCE_NAME`_datapath_u0__F0_F1_REG)
#define `$INSTANCE_NAME`_F0_F1_REG		(*(reg16 *) `$INSTANCE_NAME`_datapath_u0__F0_F1_REG)

// AUX CTL definitions
//  ----------------- MASKS ----------------------
#define `$INSTANCE_NAME`_F1_LEVEL_MASK				(0x08u)
#define `$INSTANCE_NAME`_F0_LEVEL_MASK				(0x04u)
#define `$INSTANCE_NAME`_F1_SINGLE_BUFFER_MASK		(0x02u)
#define `$INSTANCE_NAME`_F0_SINGLE_BUFFER_MASK		(0x01u)

//  ----------------- MODES ----------------------
#define `$INSTANCE_NAME`_F1_LEVEL_MODE_0			(0u)
#define `$INSTANCE_NAME`_F1_LEVEL_MODE_1			(1u)

#define `$INSTANCE_NAME`_F0_LEVEL_MODE_0			(0u)
#define `$INSTANCE_NAME`_F0_LEVEL_MODE_1			(1u)

#define `$INSTANCE_NAME`_F1_SINGLE_BUFFER_DISABLE	(0u)
#define `$INSTANCE_NAME`_F1_SINGLE_BUFFER_ENABLE	(1u)

#define `$INSTANCE_NAME`_F0_SINGLE_BUFFER_DISABLE	(0u)
#define `$INSTANCE_NAME`_F0_SINGLE_BUFFER_ENABLE	(1u)

// ----------------- SHIFT -----------------------
#define `$INSTANCE_NAME`_F1_LEVEL_SHIFT				(3u)
#define `$INSTANCE_NAME`_F0_LEVEL_SHIFT				(2u)
#define `$INSTANCE_NAME`_F1_SINGLE_BUFFER_SHIFT		(1u)
#define `$INSTANCE_NAME`_F0_SINGLE_BUFFER_SHIFT		(0u)

//-------------------------------------------------
#define `$INSTANCE_NAME`_ReadPeriod()					CY_GET_REG8(`$INSTANCE_NAME`_F0_PTR)

#define `$INSTANCE_NAME`_WritePeriod(period)			CY_SET_REG8(`$INSTANCE_NAME`_F0_PTR, (uint8)(period))

#define `$INSTANCE_NAME`_ReadCompare0()					CY_GET_REG8(`$INSTANCE_NAME`_D0_PTR)
#define `$INSTANCE_NAME`_ReadCompare1()					CY_GET_REG8(`$INSTANCE_NAME`_D1_PTR)
#define `$INSTANCE_NAME`_ReadCompare2()					CY_GET_REG8(`$INSTANCE_NAME`_F1_PTR)

#define `$INSTANCE_NAME`_WriteCompare0(compare)			CY_SET_REG8(`$INSTANCE_NAME`_D0_PTR, (uint8)(compare))
#define `$INSTANCE_NAME`_WriteCompare1(compare)			CY_SET_REG8(`$INSTANCE_NAME`_D1_PTR, (uint8)(compare))
#define `$INSTANCE_NAME`_WriteCompare2(compare)			CY_SET_REG8(`$INSTANCE_NAME`_F1_PTR, (uint8)(compare))

#define `$INSTANCE_NAME`_ReadCounter0()					CY_GET_REG8(`$INSTANCE_NAME`_A0_PTR)
#define `$INSTANCE_NAME`_ReadCounter1()					CY_GET_REG8(`$INSTANCE_NAME`_A1_PTR)

#define `$INSTANCE_NAME`_WriteCounter0(value)			CY_SET_REG8(`$INSTANCE_NAME`_A0_PTR, (uint8)(value))
#define `$INSTANCE_NAME`_WriteCounter1(value)			CY_SET_REG8(`$INSTANCE_NAME`_A1_PTR, (uint8)(value))

#define `$INSTANCE_NAME`_WriteIntensity0(intensity)		`$INSTANCE_NAME`_WriteCompare0((~(uint8)(intensity)))
#define `$INSTANCE_NAME`_WriteIntensity1(intensity)		`$INSTANCE_NAME`_WriteCompare1((~(uint8)(intensity)))
#define `$INSTANCE_NAME`_WriteIntensity2(intensity)		`$INSTANCE_NAME`_WriteCompare2((~(uint8)(intensity)))

void `$INSTANCE_NAME`_Start();
void `$INSTANCE_NAME`_Write_RGB(uint32 color);


#endif
//[] END OF FILE
