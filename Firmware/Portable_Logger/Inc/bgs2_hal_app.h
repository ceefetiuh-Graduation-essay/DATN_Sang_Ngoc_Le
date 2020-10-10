/**
  ******************************************************************************
  * @file    	bgs2_hal_app.h
  * @author  	Sang Ngoc Le
  * @version 	V2.0
  * @date    	1/3/2018
  * @brief   	This file contains all the function prototypes, 
	*						definitions and struct for the bgs2_hal_app.c file
  ******************************************************************************
  * @copy
  * COPYRIGHT(c) 2018 HBQ Tecnology 
  */ 
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __bgs2_hal_app_H
#define __bgs2_hal_app_H
#ifdef __cplusplus
 extern "C" {
#endif
	 
/* Includes ------------------------------------------------------------------*/ 
#include "usart.h"
#include "main.h"
#include "led.h"
#include "string.h" 	 
	 
/* Private defines -----------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/	
uint8_t SIM_Init(void);
uint8_t SIM_Check_Account(uint8_t SIM_Service);
uint8_t SIM_Send_SMS(char num[], char sms[]);
uint8_t SIM_Sync_Time(uint8_t service_sim);
uint8_t SIM_Signal_Quality(void);
uint8_t SIM_Http_Request(char *http, char *dataFrame,uint16_t port);
uint8_t modem_send_http_request(char *http, char *dataFrame);
	 
#ifdef __cplusplus
}
#endif
#endif /*__ bgs2_hal_app_H */

/**
  * @}
  */

/**
  * @}
  */	 
/********************** End of file *******************************************/ 
