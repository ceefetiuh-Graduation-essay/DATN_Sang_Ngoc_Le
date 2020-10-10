/**
  ******************************************************************************
  * @file    	led.h
  * @author  	Sang Ngoc Le
  * @version 	V1.0
  * @date    	28/2/2018
  * @brief   	This file contains all the function prototypes, 
	*						definitions and struct for the led.c file
  ******************************************************************************
  * @copy
  * COPYRIGHT(c) 2018 NPL-SNL
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __led_H
#define __led_H
#ifdef __cplusplus
 extern "C" {
#endif
	 
/* Includes ------------------------------------------------------------------*/ 
#include <stdint.h>
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "stm32l1xx_hal_gpio.h"

/* Private defines -----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
typedef struct _ledDEF
{
    uint32_t ledOnTime;
		uint32_t ledOffTime;
		uint32_t ledCounter;
		uint8_t ledStatus;
		uint8_t ledEnable;
		uint32_t ledTimes;
} LED_TYPE;	 

extern LED_TYPE	led_run, led_err;	
	
#define TIMER_PERIOD	100	//ms


#define LED_ON_TIME_DFG	(50 / TIMER_PERIOD) /*1s */
#define LED_OFF_TIME_DFG	(50 / TIMER_PERIOD) /*1s */
#define LED_TURN_ON	1
#define LED_TURN_OFF 0

#define LED_PORT	LD4_B_GPIO_Port
#define LED_PIN		LD4_B_Pin
//#define LED_SET_OUTPUT			HAL_GPIO_WritePin(LED_PORT, LED_PIN); //LED_PORT->CRH	&= ~(GPIO_CRH_MODE6 | GPIO_CRH_CNF6); LED_PORT->CRH	|= (GPIO_CRH_MODE6_0)
//#define LED_SET_INPUT				LED_PORT->CRH	&= ~(GPIO_CRH_MODE6 | GPIO_CRH_CNF6); LED_PORT->CRH	|= (GPIO_CRH_CNF6_0)
#define LED_PIN_SET()					HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); //LED_PORT->BSRR = LED_PIN
#define LED_PIN_CLR()				HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET); //LED_PORT->BRR = LED_PIN

#define LED_ON	1
#define LED_OFF 0

/* Private function prototypes -----------------------------------------------*/	 
	 
void LedCtr(LED_TYPE *ledCtr,uint32_t times);
void LedSetStatus(LED_TYPE *ledCtr,uint32_t onTime,uint32_t offTime,uint32_t ledEnable,uint32_t times);
void LedInit(void);
void CtrLed(uint32_t time);	 
	  
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
