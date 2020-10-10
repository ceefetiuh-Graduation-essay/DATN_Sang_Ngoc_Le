/**
  ******************************************************************************
  * @file    	pwr_standby_rtc_wkup.h
  * @author  	Sang Ngoc Le
  * @version 	V1.0
  * @date    	19/4/2018
  * @brief   	This file contains all the function prototypes, 
	*						definitions and struct for the pwr_standby_rtc_wkup.c file
  ******************************************************************************
  * @copy
  * COPYRIGHT(c) 2018 NPL-SNL
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __pwr_standby_rtc_wkup_H
#define __pwr_standby_rtc_wkup_H
#ifdef __cplusplus
 extern "C" {
#endif
	 
/* Includes ------------------------------------------------------------------*/ 
//#include "stm32l1xx_hal_pwr.h"
//#include "stm32l1xx_hal_pwr_ex.h"
#include "rtc.h"

/* Private defines -----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
	 
/* Private function prototypes -----------------------------------------------*/
void enter_stanby_mode(uint32_t wkup_time);
	 
#ifdef __cplusplus
}
#endif
#endif /*__ led_H */

/**
  * @}
  */

/**
  * @}
  */	 
/********************** End of file *******************************************/ 
