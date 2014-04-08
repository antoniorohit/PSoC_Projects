/*******************************************************************************
* File Name: CapSense_TunerHelper.h
* Version 1.0
*
* Description:
*  This file provides constants and structure declarations for the tunner hepl
*  APIs for CapSense CSD component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_TUNERHELPER_CapSense_H)
#define CY_CAPSENSE_CSD_TUNERHELPER_CapSense_H

#include "CapSense.h"
#include "CapSense_CSHL.h"
#if (CapSense_TUNER_API_GENERATE)
    #include "CapSense_MBX.h"
#endif /* (CapSense_TUNER_API_GENERATE) */


/***************************************
*     Constants for mailboxes
***************************************/

#define CapSense_DEFAULT_MAILBOXES_NUMBER   (1u)
#define CapSense_CMD_WAIT_TIMEOUT           (0xFFFFFFFFu)


/***************************************
*        Function Prototypes
***************************************/

void CapSense_TunerStart(void);
void CapSense_TunerComm(void);

#if (CapSense_TUNER_API_GENERATE)
    uint8 CapSense_ReadCommand(void);
    void CapSense_WriteCommand(uint32 cmd);
    void CapSense_ClearCommand(uint32 cmd);
    void CapSense_TxData(volatile CapSense_OUTBOX *inbox);
	
	#if (CapSense_TUNING_METHOD == CapSense_MANUAL_TUNING)
    	void CapSense_RxData(volatile CapSense_INBOX *inbox);
	#endif  /* (CapSense_TUNING_METHOD == CapSense_MANUAL_TUNING) */	

#endif /* (CapSense_TUNER_API_GENERATE) */

#endif  /* (CY_CAPSENSE_CSD_TUNERHELPER_CapSense_H)*/


/* [] END OF FILE */
