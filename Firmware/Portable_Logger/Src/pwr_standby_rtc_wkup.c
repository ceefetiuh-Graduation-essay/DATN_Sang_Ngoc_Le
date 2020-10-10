/**
  ******************************************************************************
  * @file    	pwr_standby_rtc_wkup.c
  * @author  	Sang Ngoc Le
  * @version 	V1.0
  * @date    	19/4/2018
  * @brief   	This file provides all the functions for standby mode and wakeup by RTC  
	*						
  ******************************************************************************
  * @copy
  * COPYRIGHT(c) 2018 NPL-SNL
  */ 
	
/* Includes ------------------------------------------------------------------*/ 
#include "pwr_standby_rtc_wkup.h"
/* Private variables ---------------------------------------------------------*/
extern RTC_HandleTypeDef hrtc;
/* Private functions ---------------------------------------------------------*/
void enter_stanby_mode(uint32_t wkup_time)
{
	if(__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
  {
    /* Clear Standby flag */
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB); 
  }
	
	  /* The Following Wakeup sequence is highly recommended prior to each Standby mode entry
    mainly  when using more than one wakeup source this is to not miss any wakeup event.
    - Disable all used wakeup sources,
    - Clear all related wakeup flags, 
    - Re-enable all used wakeup sources,
    - Enter the Standby mode.
  */
  /* Disable all used wakeup sources*/
	HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
	
	/* Re-enable all used wakeup sources*/
  /* ## Setting the Wake up time ############################################*/
  /*  RTC Wakeup Interrupt Generation:
    Wakeup Time Base = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSE))
    Wakeup Time = Wakeup Time Base * WakeUpCounter 
      = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSI)) * WakeUpCounter
      ==> WakeUpCounter = Wakeup Time / Wakeup Time Base
  
    To configure the wake up timer to 4s the WakeUpCounter is set to 0x1FFF:
    RTC_WAKEUPCLOCK_RTCCLK_DIV = RTCCLK_Div16 = 16 
    Wakeup Time Base = 16 /(~32.768KHz) = ~0,488 ms
    Wakeup Time = ~10s = 0,488ms  * WakeUpCounter
      ==> WakeUpCounter = ~10s/0,488ms = 20492 = 0x2616 
					WakeUpCounter = ~10000ms/0,488ms = 20492 = 0x2616	*/
	
	
	
  HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, (wkup_time/0.488), RTC_WAKEUPCLOCK_RTCCLK_DIV16);  //Change it
	
	  /* Clear all related wakeup flags */
  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
  
  /* Enter the Standby mode */
  HAL_PWR_EnterSTANDBYMode();
	
}



/************************* End of File ****************************************/
