/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "iwdg.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "device_user_config_app.h"
#include "plog_app.h"
#include "string.h"
#include "led.h"
#include "pwr_standby_rtc_wkup.h"
#include "dwt_stm32_delay.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
DeviceInfo_TypeDef PlogInfo;
/* Console debug */
extern uint8_t DBG_RX_index , DBG_RX_byte[1], DBG_RX_Buffer[DBG_BUFFER_SIZE], DBG_Transfer_cplt;

/* GSM Module communication */
extern uint8_t GSM_RX_index , GSM_RX_byte[1], GSM_RX_Buffer[100], GSM_Transfer_cplt , get_n;
extern uint8_t GSM_ans_stt, GSM_send_error, GSM_receive_error;
extern char SIM_Buff[1024];
extern uint8_t flag_gsm;
extern uint8_t gsm;
extern uint8_t en_receive_response;

extern uint16_t gsm_buff_count;
extern uint8_t SIM_Rx_data;
extern uint8_t GSM_RX_indx;

/* ADC DMA */
extern uint16_t adc_val[7];

/* error counter */
uint8_t error_counting = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/**
  ******************************************************************************
  * @author					: Sang Ngoc Le
  * @version				: V0.1
  * @date    				: 27/2/2018
  * @brief					: Main program body
  ******************************************************************************
*/

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

	
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC_Init();
  //MX_IWDG_Init();
  MX_RTC_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM3_Init();
	
  /* USER CODE BEGIN 2 */
	
	if(DWT_Delay_Init())
  {
    _Error_Handler(__FILE__, __LINE__);
  }
	
	
	HAL_GPIO_WritePin(GPIOB, LD4_B_Pin|LD3_G_Pin, GPIO_PIN_SET); // Turn off LED
	
	/* Begin TIM3 Interrupt */
	while ((HAL_TIM_Base_Start_IT(&htim3)) != HAL_OK)
	{ 
		HAL_Delay(50);
		error_counting++;
		if(error_counting == 5)
		{
			_Error_Handler(__FILE__, __LINE__);
		}
	}
	error_counting = 0;
	
	/* Begin UART3 DMA */
	while((HAL_UART_Receive_DMA(&huart3, (uint8_t*) DBG_RX_byte, 1)) != HAL_OK) //Begin UART3 DMA
	{
		HAL_Delay(50);
		error_counting++;
		if(error_counting == 5)
		{
			_Error_Handler(__FILE__, __LINE__);
		}
	}		
	DBG_RX_index = 0;
	error_counting = 0;
	
	/* Begin UART1 DMA */
	while((HAL_UART_Receive_DMA(&huart1, (uint8_t*) GSM_RX_byte, 1)) != HAL_OK) //Begin UART3 DMA
	{
		HAL_Delay(50);
		error_counting++;
		if(error_counting == 5)
		{
			_Error_Handler(__FILE__, __LINE__);
		}
	}		
	error_counting = 0;
	
	/* Begin ADC DMA */
	while((HAL_ADC_Start_DMA(&hadc, (uint32_t*)adc_val, 7)) != HAL_OK)
	{
		HAL_Delay(50);
		error_counting++;
		if(error_counting == 5)
		{
			_Error_Handler(__FILE__, __LINE__);
		}
	}
	error_counting = 0;	
	
	//for (uint8_t i=0;i<100;i++) DBG_RX_Buffer[i] = '\0'; 				//Clear buffer
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint8_t sang = 0; //debug
	
	LedSetStatus(&led_run,1,0,LED_TURN_ON,0xffffffff);					// Device reboot status, LED on.  
	
	if(__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
	{
		/* Clear Standby flag */
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB); 
		Demo_App();
	}
	
	printf("\r\n||==========================================||  ");
	HAL_Delay(50);
	printf("\r\n||        ____      __    ____   ______	     ||  ");
	HAL_Delay(50);
	printf("\r\n||       / __ \\    / /   / __ \\ / ____/     ||  ");
	HAL_Delay(50);
	printf("\r\n||      / /_/ /   / /   / / / // / __       ||  ");
	HAL_Delay(50);
	printf("\r\n||     / ____/_  / /___/ /_/ // /_/ /       ||  ");
	HAL_Delay(50);
	printf("\r\n||    /_/    (_)/_____/\\____/ \\____/        ||  ");
	HAL_Delay(50);
	printf("\r\n||                                          ||  ");
	HAL_Delay(50);
	printf("\r\n||==========================================||\r\n  ");

	HAL_Delay(1000);
	
	User_Config();
	
  while (1)
  {
		
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		Demo_App();	
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	printf("\r\n ERROR in file: %c, at line: %d\r\n", *file, line);
	error_counting = 0;
  while(error_counting < 10)
  {
		HAL_GPIO_TogglePin(LD3_G_GPIO_Port, LD3_G_Pin);
		HAL_Delay(500);
		error_counting ++;
  }
	NVIC_SystemReset();		
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
