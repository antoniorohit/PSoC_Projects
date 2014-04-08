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
#include <control.h>
#include <motors.h>
#include <sensors.h>

#define WATCHDOG_ENABLED    1

CY_ISR(isr_wdt);

void initialize(void);

int main()
{    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    initialize();
    
    for(;;)
    {
        /* Place your application code here. */
        
        //debug pin toggle
        P4_0_Debug_Write(0xff);
        
        //measure sensor inputs
        sensors_updateSensors();
        
        //debug pin toggle
        P4_0_Debug_Write(0x00);
        
        //iterate the control loop
        control_IterateControl();
        
        //feed watchdog
        CySysWdtResetCounters(CY_SYS_WDT_COUNTER1_RESET);
    }
}

//watchdog timer ISR
CY_ISR(isr_wdt)
{
    //do nothing (for now)
    
    /* Clear interrupts state */
	CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
    CyIntClearPending(9);
}

//firmware initialization
void initialize(void)
{
    //debug pin toggle
    P4_0_Debug_Write(0xff);
    //debug pin toggle
    P4_0_Debug_Write(0x00);
    //debug pin toggle
    P4_0_Debug_Write(0xff);
    //debug pin toggle
    P4_0_Debug_Write(0x00);
    
    //enable interrupts
    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
    
    //start watchdog
    /* Setup WDT ISR */
    CyIntSetVector(9, isr_wdt);
    CyIntEnable(9);
	/* Setup first WDT counter to generate interrupt on match 0x4FFF */
	CySysWdtWriteMode(CY_SYS_WDT_COUNTER0,CY_SYS_WDT_MODE_INT);
	CySysWdtWriteMatch(CY_SYS_WDT_COUNTER0,0x4FFF);
	CySysWdtWriteClearOnMatch(CY_SYS_WDT_COUNTER0, 1u);
    /* Enable WDT timers 0 and 1 cascade */
	CySysWdtWriteCascade(CY_SYS_WDT_CASCADE_01);
	/* Set WDT reset after counter 1 reach 0x0002 */
	CySysWdtWriteMatch(CY_SYS_WDT_COUNTER1,0x0002);
	CySysWdtWriteMode(CY_SYS_WDT_COUNTER1,CY_SYS_WDT_MODE_RESET);
    CySysWdtWriteClearOnMatch(CY_SYS_WDT_COUNTER1, 1u);
    /* Enable WDT counters 0 and 1 */
    //#if(WATCHDOG_ENABLED)
	CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK | CY_SYS_WDT_COUNTER1_MASK);
    //#endif 

    //start components
    sensors_Start();
    motors_Start();
    control_Start();
}

/* [] END OF FILE */
