/**
  ******************************************************************************
  * @file    	bgs2_hal_dv.h
  * @author  	Sang Ngoc Le
  * @version 	V1.0
  * @date    	29/2/2018
  * @brief   	This file contains all the function prototypes, 
	*						definitions and struct for the bgs2_hal_dv.c file
  ******************************************************************************
  * @copy
  * COPYRIGHT(c) 2018 NPL-SNL 
  */ 
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __bgs2_hal_dv_H
#define __bgs2_hal_dv_H
#ifdef __cplusplus
 extern "C" {
#endif
	 
/* Includes ------------------------------------------------------------------*/ 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>	 

#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "led.h"
#include "string.h" 	 
	 

/* Private defines -----------------------------------------------------------*/
/* BGS2 PIN MAPPING */
/* Power On Pin */
#define SIM_PW_PIN          GSM_ON_Pin
#define SIM_PW_PORT         GSM_ON_GPIO_Port

/* Reset Pin */
#define SIM_RST_PIN         GSM_RST_Pin
#define SIM_RST_PORT        GSM_RST_GPIO_Port

/* BGS2 Power management */
#define SIM_ON()			HAL_GPIO_WritePin(SIM_PW_PORT, SIM_PW_PIN, GPIO_PIN_RESET) 	
#define SIM_OFF()			HAL_GPIO_WritePin(SIM_PW_PORT, SIM_PW_PIN, GPIO_PIN_SET)  
#define SIM_RST_OFF()	HAL_GPIO_WritePin(SIM_RST_PORT, SIM_RST_PIN, GPIO_PIN_RESET)  
#define SIM_RST_ON()	HAL_GPIO_WritePin(SIM_RST_PORT, SIM_RST_PIN, GPIO_PIN_SET) 

typedef enum 
{ 
 Unknown 				=	0,
 VinaPhone 			=	1,
 Viettel 				=	2,
 MobiPhone 			=	3,
 VietnamMobile	= 4,
 AutoDetect   	= 6
} GSMSERVICE_TYPE;

/* Private function prototypes -----------------------------------------------*/	

/* BGS2 driver functions */

//void DV_SIM_GPIO_Init(void);
//void DV_SIM_USART_Init(void);
void DV_SIM_printf(uint8_t *s);
uint8_t DV_SIM_Gprs_On(uint8_t SIM_Service);
uint8_t DV_SIM_Startup(void);
uint8_t DV_SIM_AT_Cmd(char *data);
uint8_t DV_SIM_AT_Sync(void);
uint8_t DV_SIM_Check_Service(void);
uint8_t DV_SIM_Reset(void);

uint8_t SIM_Reset(void); //Reset GSM_module
uint8_t SIM_sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout); //Gui lenh AT
uint8_t SIM_AT_Sync(void); //Dong bo baudrate
uint8_t SIM_Check_Service(void); //Kiem tra dich vu
uint8_t SIM_Startup(void); //Khoi dong GSM_Module
uint8_t SIM_Gprs_On(uint8_t SIM_Service); //Bat GPRS

/* application functions */



uint8_t user_strcmp(char *u1, char *u2);
int LookingForWord(char source[], char text[]);


	 
#ifdef __cplusplus
}
#endif
#endif /*__ bgs2_hal_dv_H */

/**
  * @}
  */

/**
  * @}
  */	 
/********************** End of file *******************************************/ 
