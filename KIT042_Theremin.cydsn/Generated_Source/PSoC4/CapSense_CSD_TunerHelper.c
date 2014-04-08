/*******************************************************************************
* File Name: CapSense_CSD_TunerHelper.c
* Version 1.11
*
* Description:
*  This file provides the source code of Tuner helper APIs for the CapSense CSD 
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CapSense_CSD_TunerHelper.h"

#if (CapSense_CSD_TUNER_API_GENERATE)
    #include "SCB.h"
    #include "SCB_EZI2C.h"

	CapSense_CSD_NO_STRICT_VOLATILE void CapSense_CSD_ProcessAllWidgets(volatile CapSense_CSD_OUTBOX *outbox);
    volatile CapSense_CSD_MAILBOXES CapSense_CSD_mailboxesComm;

    extern uint8 CapSense_CSD_sensorOnMask[(((CapSense_CSD_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];
#endif  /* (CapSense_CSD_TUNER_API_GENERATE) */


/*******************************************************************************
* Function Name: CapSense_CSD_TunerStart
********************************************************************************
*
* Summary:
*  Initializes CapSense CSD component and EzI2C communication componenet to use
*  mailbox data structure for communication with Tuner GUI.
*  Start the scanning, after initialization complete.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_CSD_TunerStart(void)
{
    #if (CapSense_CSD_TUNER_API_GENERATE)
        
        /* Init mbx and quick check */
        CapSense_CSD_InitMailbox(&CapSense_CSD_mailboxesComm.csdMailbox);
        CapSense_CSD_mailboxesComm.numMailBoxes = CapSense_CSD_DEFAULT_MAILBOXES_NUMBER;
        
        /* Start CapSense and baselines */
        CapSense_CSD_Start();
        
        /* Initialize baselines */ 
        CapSense_CSD_InitializeAllBaselines();
        CapSense_CSD_InitializeAllBaselines();
        
        /* Start EzI2C, clears buf pointers */
        SCB_Start();
        
        /* Setup EzI2C buffers */
        SCB_EzI2CSetBuffer1(sizeof(CapSense_CSD_mailboxesComm), sizeof(CapSense_CSD_mailboxesComm),
                                        (void *) &CapSense_CSD_mailboxesComm);
        
        /* Starts scan all enabled sensors */
        CapSense_CSD_ScanEnabledWidgets();
    
    #endif  /* (CapSense_CSD_TUNER_API_GENERATE) */
}


/*******************************************************************************
* Function Name: CapSense_CSD_TunerComm
********************************************************************************
*
* Summary:
*  This function is blocking. It waits till scaning loop is completed and apply
*  new parameters from Tuner GUI if available (manual tuning mode only). Updates
*  enabled baselines and state of widgets. Waits while Tuner GUI reports that 
*  content of mailbox could be modified. Then loads the report data into outbox 
*  and sets the busy flag. Starts new scanning loop.
*  
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void CapSense_CSD_TunerComm(void)
{
    #if (CapSense_CSD_TUNER_API_GENERATE)
        if (0u == CapSense_CSD_IsBusy())
        {   
            /* Apply new settings */
            #if (CapSense_CSD_TUNING_METHOD == CapSense_CSD_MANUAL_TUNING)
                CapSense_CSD_ReadMessage(&CapSense_CSD_mailboxesComm.csdMailbox);
            #endif  /* (CapSense_CSD_TUNING_METHOD == CapSense_CSD_MANUAL_TUNING) */

            /* Update all baselines and process all widgets */
            CapSense_CSD_UpdateEnabledBaselines();
            CapSense_CSD_ProcessAllWidgets(&CapSense_CSD_mailboxesComm.csdMailbox.outbox);
            CapSense_CSD_PostMessage(&CapSense_CSD_mailboxesComm.csdMailbox);

            /* Enable EZI2C interrupts, after scan complete */
            SCB_EnableInt();

            while((CapSense_CSD_mailboxesComm.csdMailbox.type != CapSense_CSD_TYPE_ID) || \
                  (SCB_EzI2CGetActivity() & SCB_EZI2C_STATUS_BUSY)){}
            
            /* Disable EZI2C interrupts, while scanning */
            SCB_DisableInt();
            
            /* Start scan all sensors */
            CapSense_CSD_ScanEnabledWidgets();
        }
    #endif /* (CapSense_CSD_TUNER_API_GENERATE) */
}


#if (CapSense_CSD_TUNER_API_GENERATE)
    /*******************************************************************************
    * Function Name: CapSense_CSD_ProcessAllWidgets
    ********************************************************************************
    *
    * Summary:
    *  Call required functions to update all widgets state:
    *   - CapSense_CSD_GetCentroidPos() - calls only if linear sliders 
    *     available.
    *   - CapSense_CSD_GetRadialCentroidPos() - calls only if radial slider 
    *     available.
    *   - CapSense_CSD_GetTouchCentroidPos() - calls only if touch pad slider 
    *     available.
    *   - CapSense_CSD_CheckIsAnyWidgetActive();
    *  The results of opeartions are copied to OUTBOX.
    *   
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  CapSense_CSD_OUTBOX outbox - structure which is used as ouput 
    *  buffer for report data to Tuner GUI.
    *  Update fields:
    *    - position[];
    *    - OnMask[];
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
	void CapSense_CSD_ProcessAllWidgets(volatile CapSense_CSD_OUTBOX *outbox)
    {
        uint8 i = 0u;

        #if (CapSense_CSD_TOTAL_TOUCH_PADS_COUNT)
            uint16 pos[2];
        #endif  /* (CapSense_CSD_TOTAL_TOUCH_PADS_COUNT) */
        
        #if ( (CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT) || (CapSense_CSD_TOTAL_TOUCH_PADS_COUNT) || \
              (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT) )
            uint8 widgetCnt = 0u;
        #endif  /* ((CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT) || (CapSense_CSD_TOTAL_TOUCH_PADS_COUNT)) || 
                *   (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT)
                */
        
        /* Calculate widget with centroids */
        #if (CapSense_CSD_TOTAL_LINEAR_SLIDERS_COUNT)
            for(; i < CapSense_CSD_TOTAL_LINEAR_SLIDERS_COUNT; i++)
            {
                outbox->position[i] = CapSense_CSD_GetCentroidPos(i);
            }
        #endif /* (CapSense_CSD_TOTAL_LINEAR_SLIDERS_COUNT) */
        
        #if (CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT)
            widgetCnt = i;
            for(; i < widgetCnt + CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT; i++)
            {
                outbox->position[i] = CapSense_CSD_GetRadialCentroidPos(i);
            }
        #endif /* (CapSense_CSD_TOTAL_RADIAL_SLIDERS_COUNT) */
        
        #if (CapSense_CSD_TOTAL_TOUCH_PADS_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + (CapSense_CSD_TOTAL_TOUCH_PADS_COUNT * 2)); i=i+2)
            {
                if(CapSense_CSD_GetTouchCentroidPos(i, pos) == 0u)
                {
                    outbox->position[i] = 0xFFFFu;
                    outbox->position[i+1] = 0xFFFFu;
                }
                else
                {
                    outbox->position[i] = (uint16) pos[0u];
                    outbox->position[i+1] = (uint16) pos[1u];
                }
            }
        #endif /* (CapSense_CSD_TOTAL_TOUCH_PADS_COUNT) */

        #if (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT)
            i += CapSense_CSD_TOTAL_BUTTONS_COUNT;
            widgetCnt = 0;
            for(; widgetCnt < (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT * 2); i += 2)
            {
                if(CapSense_CSD_GetMatrixButtonPos(i, ((uint8*) &outbox->mb_position[widgetCnt])) == 0)
                {
                    outbox->mb_position[widgetCnt] = 0xFFu;
                    outbox->mb_position[widgetCnt+1] = 0xFF;
                }
                widgetCnt += 2;
            }
        #endif /* (CapSense_CSD_TOTAL_MATRIX_BUTTONS_COUNT) */

        /* Update On/Off State */
        CapSense_CSD_CheckIsAnyWidgetActive();

        /* Copy OnMask */
        for(i=0; i < CapSense_CSD_TOTAL_SENSOR_MASK_COUNT; i++)
        {
            outbox->onMask[i]  = CapSense_CSD_sensorOnMask[i];
        }
    }
#endif /* (CapSense_CSD_TUNER_API_GENERATE) */


/* [] END OF FILE */
