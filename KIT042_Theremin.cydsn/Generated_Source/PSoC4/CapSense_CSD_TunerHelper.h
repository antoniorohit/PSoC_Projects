/*******************************************************************************
* File Name: CapSense_CSD_TunerHelper.h
* Version 1.11
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

#if !defined(CY_CAPSENSE_CSD_TUNERHELPER_CapSense_CSD_H)
#define CY_CAPSENSE_CSD_TUNERHELPER_CapSense_CSD_H

#include "CapSense_CSD.h"
#include "CapSense_CSD_CSHL.h"
#if (CapSense_CSD_TUNER_API_GENERATE)
    #include "CapSense_CSD_MBX.h"
#endif /* (CapSense_CSD_TUNER_API_GENERATE) */


/***************************************
*     Constants for mailboxes
***************************************/

#define CapSense_CSD_DEFAULT_MAILBOXES_NUMBER   (1u)


/***************************************
*        Function Prototypes
***************************************/

void CapSense_CSD_TunerStart(void);
void CapSense_CSD_TunerComm(void);


#endif  /* (CY_CAPSENSE_CSD_TUNERHELPER_CapSense_CSD_H)*/


/* [] END OF FILE */
