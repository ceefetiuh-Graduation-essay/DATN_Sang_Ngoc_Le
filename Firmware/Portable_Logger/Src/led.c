/**
  ******************************************************************************
  * @file    	led.c
  * @author  	Sang Ngoc Le
  * @version 	V1.0
  * @date    	28/2/2018
  * @brief   	This file provides all the functions for driving LED    
	*						
  ******************************************************************************
  * @copy
  * COPYRIGHT(c) 2018 NPL-SNL
  */ 
	
/* Includes ------------------------------------------------------------------*/ 
#include "led.h"

/* Private variables ---------------------------------------------------------*/
LED_TYPE	led_run, led_err;	

/* Private functions ---------------------------------------------------------*/

/**
	******************************************************************************
  * @brief  Initialize LED. 
  * @param  None
  * @retval None
	******************************************************************************
  */
void LedInit(void)			
{
	//LED_SET_OUTPUT;
	LedSetStatus(&led_run,LED_ON_TIME_DFG,LED_OFF_TIME_DFG,LED_TURN_ON,0xffffffff);
	
}

/**
	******************************************************************************
  * @brief  Configures the LED status. 
  * @param  ledCtr	 : Pointer to a LED_TYPE structure that contains
  *                	   the configuration information for the specified LED module.
	*	@param	onTime   : Turn on period. (x100ms)
	*	@param	offTime	 : Turn off period.(x100ms)
	*	@param	ledEnable: Enable LED.
	*	@param	times		 : Enabling time.
  * @retval None
	******************************************************************************
  */
void LedSetStatus(LED_TYPE *ledCtr,uint32_t onTime,uint32_t offTime,uint32_t ledEnable,uint32_t times)		
{
	ledCtr->ledOnTime = onTime;
	ledCtr->ledOffTime = offTime;
	ledCtr->ledCounter = 0;
	ledCtr->ledEnable = ledEnable;
	ledCtr->ledTimes = times;
}													


void CtrLed(uint32_t time)
{
		static uint64_t ledTimeNew = 0,ledTimeOld = 0;
		static uint32_t timeOld = 0;
		ledTimeNew += time - timeOld;
		LedCtr(&led_run,ledTimeNew - ledTimeOld);
		ledTimeOld = ledTimeNew; 
		timeOld = time;
	
	if(led_run.ledStatus == LED_ON)
	{
		LED_PIN_SET();
	}
	else 
	{
		LED_PIN_CLR();
	}
}	
											
void LedCtr(LED_TYPE *ledCtr, uint32_t times)	
{
	if(ledCtr->ledEnable == LED_TURN_ON) 
	{
			if(ledCtr->ledCounter > times)
				ledCtr->ledCounter -= times;
			else ledCtr->ledCounter = 0;
				
			if(ledCtr->ledCounter == 0) 
			{
				if(ledCtr->ledTimes) 
				{
					ledCtr->ledTimes--;
					ledCtr->ledCounter = ledCtr->ledOffTime + ledCtr->ledOnTime;
					ledCtr->ledStatus = LED_ON;
				}
			}
			
			if(ledCtr->ledCounter <= ledCtr->ledOffTime) 
				ledCtr->ledStatus = LED_OFF;
	}
}
