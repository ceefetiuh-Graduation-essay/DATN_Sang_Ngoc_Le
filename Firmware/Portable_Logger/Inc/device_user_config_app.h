/**
  ******************************************************************************
  * @file    	device_user_config_app.h
  * @author  	Sang Ngoc Le
  * @version 	V1.0
  * @date    	1/3/2018
  * @brief   	This file contains all the function prototypes, 
	*						definitions and struct for the device_user_config_app.c file
  ******************************************************************************
  * @copy
  * COPYRIGHT(c) 2018 NPL-SNL 
  */ 
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __device_user_config_app_H
#define __device_user_config_app_H
#ifdef __cplusplus
 extern "C" {
#endif
	 
/* Includes ------------------------------------------------------------------*/ 
#include "usart.h"
#include "main.h"
#include "led.h"
#include "string.h"

#include "plog_app.h"
/* Private defines -----------------------------------------------------------*/
#define DEFAULT_ID "00000000"
/* Private typedef -----------------------------------------------------------*/
	 
/* Private function prototypes -----------------------------------------------*/	 
	 
void User_Config(void);
	


	 
#ifdef __cplusplus
}
#endif
#endif /*__device_user_config_app_H */

/**
  * @}
  */

/**
  * @}
  */	 
/********************** End of file *******************************************/ 
