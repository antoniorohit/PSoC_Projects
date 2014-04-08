/*******************************************************************************
* File Name: CapSense_TunerHelper.c
* Version 1.0
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

#include "CapSense_TunerHelper.h"

#if (CapSense_TUNER_API_GENERATE)
    #include "CapSense_TunerIntf.h"
	#include "CapSense_TunerIntf_EZBUF_MODE.h"
    
    void CapSense_ProcessAllWidgets(volatile CapSense_OUTBOX *outbox);
    
    volatile CapSense_MAILBOXES CapSense_mailboxesComm;

    extern uint8 CapSense_SensorOnMask[(((CapSense_TOTAL_SENSOR_COUNT - 1u) / 8u) + 1u)];
#endif  /* (CapSense_TUNER_API_GENERATE) */


/*******************************************************************************
* Function Name: CapSense_TunerStart
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
void CapSense_TunerStart(void)
{
    #if (CapSense_TUNER_API_GENERATE)
        
        /* Init mbx and quick check */
        CapSense_InitMailbox(&CapSense_mailboxesComm.csdMailbox);
        CapSense_mailboxesComm.numMailBoxes = CapSense_DEFAULT_MAILBOXES_NUMBER;
        
        /* Start EzI2C, clears buf pointers */
        CapSense_TunerIntf_Start(); 
        
        /* Start CapSense and baselines */
        CapSense_Start();
        
        /* Initialize baselines */ 
        CapSense_InitializeAllBaselines();
        CapSense_InitializeAllBaselines();
        
        /* Starts scan all enabled sensors */
        CapSense_ScanEnabledWidgets();
    
    #endif  /* (CapSense_TUNER_API_GENERATE) */
}


/*******************************************************************************
* Function Name: CapSense_TunerComm
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
void CapSense_TunerComm(void)
{   
    #if (CapSense_TUNER_API_GENERATE)
            
        if (0u == CapSense_IsBusy())
        {	
            
            CapSense_TunerIntf_EzBufWriteByte((uint32)0u, 0);
            
            CapSense_ProcessAllWidgets(&CapSense_mailboxesComm.csdMailbox.outbox);
            CapSense_PostMessage(&CapSense_mailboxesComm.csdMailbox);
            
            do{
                CapSense_ClearCommand(CapSense_RESEND_REQ);
                CapSense_TxData(&CapSense_mailboxesComm.csdMailbox.outbox);
            }while(CapSense_RESEND_REQ & CapSense_ReadCommand());
            
        #if (CapSense_TUNING_METHOD == CapSense_MANUAL_TUNING)
				if(CapSense_HAVE_MSG & CapSense_ReadCommand())
				{
					CapSense_ClearCommand(CapSense_HAVE_MSG);
					CapSense_RxData(&CapSense_mailboxesComm.csdMailbox.inbox);
                	CapSense_ReadMessage(&CapSense_mailboxesComm.csdMailbox);
				}
        #endif  /* (CapSense_TUNING_METHOD == CapSense_MANUAL_TUNING) */
		
	    /* Update all baselines and process all widgets */
        CapSense_UpdateEnabledBaselines();
		
        /* Start scan all sensors */
        CapSense_ScanEnabledWidgets();
		
        }
        
    #endif /* (CapSense_TUNER_API_GENERATE) */
    
}


#if (CapSense_TUNER_API_GENERATE)
    /*******************************************************************************
    * Function Name: CapSense_ProcessAllWidgets
    ********************************************************************************
    *
    * Summary:
    *  Call required functions to update all widgets state:
    *   - CapSense_GetCentroidPos() - calls only if linear sliders 
    *     available.
    *   - CapSense_GetRadialCentroidPos() - calls only if radial slider 
    *     available.
    *   - CapSense_GetTouchCentroidPos() - calls only if touch pad slider 
    *     available.
    *   - CapSense_CheckIsAnyWidgetActive();
    *  The results of opeartions are copied to OUTBOX.
    *   
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  CapSense_OUTBOX outbox - structure which is used as ouput 
    *  buffer for report data to Tuner GUI.
    *  Update fields:
    *    - position[];
    *    - OnMask[];
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void CapSense_ProcessAllWidgets(volatile CapSense_OUTBOX *outbox)
    {
        uint8 i = 0u;

        #if (CapSense_TOTAL_TOUCH_PADS_COUNT)
            uint16 pos[2];
        #endif  /* (CapSense_TOTAL_TOUCH_PADS_COUNT) */
        
        #if ( (CapSense_TOTAL_RADIAL_SLIDERS_COUNT) || (CapSense_TOTAL_TOUCH_PADS_COUNT) || \
              (CapSense_TOTAL_MATRIX_BUTTONS_COUNT) )
            uint8 widgetCnt = 0u;
        #endif  /* ((CapSense_TOTAL_RADIAL_SLIDERS_COUNT) || (CapSense_TOTAL_TOUCH_PADS_COUNT)) || 
                *   (CapSense_TOTAL_MATRIX_BUTTONS_COUNT)
                */
        
        /* Calculate widget with centroids */
        #if (CapSense_TOTAL_LINEAR_SLIDERS_COUNT)
            for(; i < CapSense_TOTAL_LINEAR_SLIDERS_COUNT; i++)
            {
                outbox->position[i] = (uint16)CapSense_GetCentroidPos(i);
            }
        #endif /* (CapSense_TOTAL_LINEAR_SLIDERS_COUNT) */
        
        #if (CapSense_TOTAL_RADIAL_SLIDERS_COUNT)
            widgetCnt = i;
            for(; i < widgetCnt + CapSense_TOTAL_RADIAL_SLIDERS_COUNT; i++)
            {
                outbox->position[i] = (uint16)CapSense_GetRadialCentroidPos(i);
            }
        #endif /* (CapSense_TOTAL_RADIAL_SLIDERS_COUNT) */
        
        #if (CapSense_TOTAL_TOUCH_PADS_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + (CapSense_TOTAL_TOUCH_PADS_COUNT * 2)); i=i+2)
            {
                if(CapSense_GetTouchCentroidPos(i, pos) == 0u)
                {
                    outbox->position[i] = 0xFFFFu;
                    outbox->position[i+1] = 0xFFFFu;
                }
                else
                {
                    outbox->position[i] = (uint16) pos[0u];
                    outbox->position[i+1] =(uint16) pos[1u];
                }
            }
        #endif /* (CapSense_TOTAL_TOUCH_PADS_COUNT) */

        #if (CapSense_TOTAL_MATRIX_BUTTONS_COUNT)
            i += CapSense_TOTAL_BUTTONS_COUNT;
            widgetCnt = 0;
            for(; widgetCnt < (CapSense_TOTAL_MATRIX_BUTTONS_COUNT * 2); i += 2)
            {
                if(CapSense_GetMatrixButtonPos(i, ((uint8*) &outbox->mb_position[widgetCnt])) == 0)
                {
                    outbox->mb_position[widgetCnt] = 0xFFu;
                    outbox->mb_position[widgetCnt+1] = 0xFF;
                }
                widgetCnt += 2;
            }
        #endif /* (CapSense_TOTAL_MATRIX_BUTTONS_COUNT) */

        /* Update On/Off State */
        CapSense_CheckIsAnyWidgetActive();

        /* Copy OnMask */
        for(i=0; i < CapSense_TOTAL_SENSOR_MASK_COUNT; i++)
        {
            outbox->onMask[i]  = CapSense_SensorOnMask[i];
        }
    }


    /*******************************************************************************
    * Function Name: CapSense_ReadCommand
    ********************************************************************************
    *
    * Summary:
    *  Intended to getting commands from EzI2C buffer. 
    *  
    * Parameters:
    *  None
    *
    * Return:
    *  Returns command from tuner.
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    uint8 CapSense_ReadCommand(void)
    {
        return ((uint8)CapSense_TunerIntf_EzBufReadByte((uint32)0u));
    }


    /*******************************************************************************
    * Function Name: CapSense_ReadCommand
    ********************************************************************************
    *
    * Summary:
    *  Intended to writing command for tuner into EzI2C buffer. 
    *  
    * Parameters:
    *  Command that need to be executed by tuner.
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void CapSense_WriteCommand(uint32 cmd)
    {
        uint32 tmp_cmd = cmd | CapSense_TunerIntf_EzBufReadByte((uint32)0u); 
        CapSense_TunerIntf_EzBufWriteByte((uint32)0u, tmp_cmd);
    }
    
    
    /*******************************************************************************
    * Function Name: CapSense_ClearCommand
    ********************************************************************************
    *
    * Summary:
    *  Intended to clearing command in EzI2C buffer after execution. 
    *  
    * Parameters:
    *  Flags that need to be cleared.
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void CapSense_ClearCommand(uint32 cmd)
    {
        uint32 tmp_cmd = ~cmd & CapSense_TunerIntf_EzBufReadByte((uint32)0u); 
        CapSense_TunerIntf_EzBufWriteByte((uint32)0u, tmp_cmd);
    }


    /*******************************************************************************
    * Function Name: CapSense_TxData
    ********************************************************************************
    *
    * Summary:
    *  Transmission of data from target to the tuner. 
    *  
    * Parameters:
    *  Pointer to the outbox buffer.
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
    void CapSense_TxData(volatile CapSense_OUTBOX *outbox)
    {
        uint32 cmdWaitTimer;
        uint16 outboxIndex = 0u;
        uint8  txBufferIndex = 1u;
        uint8 *outboxPtr = (uint8*)outbox;
        
        while((outboxIndex < outbox->size) && (!((CapSense_START_SCAN | CapSense_RESEND_REQ | CapSense_HAVE_MSG) & CapSense_ReadCommand())))
        {
            txBufferIndex = 1u;
            cmdWaitTimer = 0u;
            
            while((txBufferIndex < 32u) && (outboxIndex < CapSense_OUTBOX_SIZE))
            {
                CapSense_TunerIntf_EzBufWriteByte(txBufferIndex, outboxPtr[outboxIndex]);
                txBufferIndex++;
                outboxIndex++;
            }
            if(outboxIndex < 32u)
            {
                CapSense_WriteCommand(CapSense_START_FRAME);
            }
            if(outboxIndex == outbox->size)
            {
                CapSense_WriteCommand(CapSense_END_FRAME);
            }
            else
            {
                CapSense_WriteCommand(CapSense_NEXT_FRAME);
            }
            
            while(!((CapSense_START_SCAN | CapSense_READY | CapSense_RESEND_REQ | CapSense_HAVE_MSG) & CapSense_ReadCommand()))
            {
                cmdWaitTimer++;
            }
            CapSense_ClearCommand(CapSense_READY);
        }
    }
    
	#if (CapSense_TUNING_METHOD == CapSense_MANUAL_TUNING)
    
    
    /*******************************************************************************
    * Function Name: CapSense_RxData
    ********************************************************************************
    *
    * Summary:
    *  Transmision data from tuner to target. 
    *  
    * Parameters:
    *  Pointer to the inbox buffer.
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *******************************************************************************/
	    void CapSense_RxData(volatile CapSense_INBOX *inbox)
	    {
	        uint8 *inboxPtr = (uint8*)inbox;
	        uint8  txBufferIndex = 0u;
	        
	        for(txBufferIndex = 0u; txBufferIndex < CapSense_INBOX_SIZE; txBufferIndex++)
	        {
	            inboxPtr[txBufferIndex] = CapSense_TunerIntf_EzBufReadByte(txBufferIndex + 1u);
	        }
	    }
	#endif  /* (CapSense_TUNING_METHOD == CapSense_MANUAL_TUNING) */
	
#endif /* (CapSense_TUNER_API_GENERATE) */

/* [] END OF FILE */
