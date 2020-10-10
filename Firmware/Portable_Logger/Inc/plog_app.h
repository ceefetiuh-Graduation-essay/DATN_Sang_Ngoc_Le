/**
  ******************************************************************************
  * @file    	plog_app.h
  * @author  	Sang Ngoc Le
  * @version 	V1.0
  * @date    	1/3/2018
  * @brief   	This file contains all the function prototypes, 
	*						definitions and struct for the plog_app.c file
  ******************************************************************************
  * @copy
  * COPYRIGHT(c) 2018 NPL-SNL
  */ 
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __plog_app_H
#define __plog_app_H
#ifdef __cplusplus
 extern "C" {
#endif
	 
/* Includes ------------------------------------------------------------------*/ 
#include "main.h"
#include "string.h"
#include "usart.h"
#include "adc.h"
#include "dma.h"
	 
#include "led.h"
#include "bgs2_hal_dv.h"
#include "bgs2_hal_app.h"
#include "pwr_standby_rtc_wkup.h"
#include "AM2301_HAL.h"
#include "dwt_stm32_delay.h"
	 

	 
/* Private defines -----------------------------------------------------------*/
	 
/* Private typedef -----------------------------------------------------------*/

typedef struct 
{
	float battery_voltage;
	char DEVICE_ID[8];
	uint8_t sending_rate;
	uint8_t GSM_signal;
	
} DeviceInfo_TypeDef;
	 
/* Private function prototypes -----------------------------------------------*/	 
	 
void Demo_App(void); 
void Main_App(void);
void Hardware_Testing_App(void);
	 
void GSM_Module_Testing(void);
void ADC_Module_Testing(void);
void AM2301_Module_Testing(void);

#ifdef __cplusplus
}
#endif
#endif /*__plog_app_H */

/**
  * @}
  */

/**
  * @}
  */	 
/********************** End of file *******************************************/ 
