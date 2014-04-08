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
 
/*******************************************************************************
 * Header For LED Matrix Component/Project
 ********************************************************************************/
 
#include <CR_Addr.h>

/* Few defines to simplify setting A B C and LAT */
#define Row_Select(r)			CR_Addr_Control=(CR_Addr_Control&0xF8)|(r&0x07)

#define Set_LAT					CR_Addr_Control=(CR_Addr_Control|0x08)
#define Clear_LAT				CR_Addr_Control=(CR_Addr_Control&0xF7)			/* LAT is Addr_CR 3 */


/*******************************************************************************
* Type Declarations
********************************************************************************/
/* Struct to hold 5-bit RGB color planes (For Matrix) */
typedef struct
{
	uint8 r[5];
	uint8 g[5];
	uint8 b[5];
} color;

/* struct to hold actual (upto 8-bit) color */
typedef struct
{
	uint8 r;
	uint8 g;
	uint8 b;
} RGB;

/*******************************************************************************
* Array to hold the matrix image - defined in main
********************************************************************************/
extern color matrix[64];

/*******************************************************************************
* Function Prototypes
********************************************************************************/
void DrawPixel(uint8 x, uint8 y, RGB c, color *matrix);
void ClearPixel(uint8 x, uint8 y, color *matrix);
void ClearScreen(color *matrix);


//[] END OF FILE
