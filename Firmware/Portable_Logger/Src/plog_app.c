/**
  ******************************************************************************
  * @file    	plog_app.c
  * @author  	Sang Ngoc Le
  * @version 	V1.0
  * @date    	2/3/2018
  * @brief   	This file provides all the functions for P.LOG Application 
	*						
  ******************************************************************************
  * @copy
  * COPYRIGHT(c) 2018 NPL-SNL
  */ 

/* Includes ------------------------------------------------------------------*/ 
#include "plog_app.h"

/* Private variables ---------------------------------------------------------*/


/* Global variables ----------------------------------------------------------*/

extern DeviceInfo_TypeDef PlogInfo;
/* Console */
extern uint8_t DBG_RX_index , DBG_RX_byte[1], DBG_RX_Buffer[DBG_BUFFER_SIZE], DBG_Transfer_cplt;

/* ADC DMA */
extern uint16_t adc_val[7];

extern uint8_t error_counting;
/* Private functions ---------------------------------------------------------*/

/******************************************************************************
** Function name: Hardware_Testing_App(void)
** Description: Testing hardware of P.Log 
** Return value: None
** Remarks: None
******************************************************************************/

void Hardware_Testing_App(void)
{
	while(1)
	{
	Testing_menu:
		LedSetStatus(&led_run,1,1,LED_TURN_ON,0xffffffff);
		DBG_RX_index = 0;
		DBG_RX_byte[0] = '\0';
		printf("\n\r\n\r>>HARDWARE TEST APPLICATION: ");
		printf("\n\r\t- Press [0] to test GSM module.");
		printf("\n\r\t- Press [1] to test ADC SENSOR module.");
		printf("\n\r\t- Press [2] to test AM2301 SENSOR module.");
		printf("\n\r\t- Press [3] to test xxx module.");
		printf("\n\r\t- Press [4] to test xxx module.");
		printf("\n\r\t- Press [5] to test xxx module.");
		printf("\n\r\t- Press [6] to exit Test Mode.");
		printf("\n\n\r>>User input: ");
		
		//putchar('<');
		//putchar(DBG_RX_byte[0]);
		//putchar('>');
		//while(DBG_RX_byte[0] == '\0');
		
		while((DBG_RX_byte[0] < '0') || (DBG_RX_byte[0] > '6'))
		{
			HAL_Delay(1);
			if((DBG_RX_byte[0] != '\0') && ((DBG_RX_byte[0] <'0') || (DBG_RX_byte[0] >'6')))
			{
				putchar(DBG_RX_byte[0]);
				printf("\r\n\r\nP.Log:> Invalid input! Please choose again!\r\n");
				HAL_Delay(1000);
				goto Testing_menu;
			}			
		} // End of While loop of choosing.
			
		//putchar(DBG_RX_byte[0]);
		
	
		switch(DBG_RX_byte[0])
		{
			case '0':
				GSM_Module_Testing();			
				break;
			
			case '1':
				ADC_Module_Testing();
				//printf("\r\n\r\nP.Log:> Config. mode is still in develop, ahihi ^^!!!");
				HAL_Delay(1000);
				break;
			
			case '2':
				AM2301_Module_Testing();
				break;
			
			case '3':
				//Test_SDCard();
				printf("\r\n\r\nP.Log:> Config. mode is still in develop, ahihi ^^!!!");
				HAL_Delay(1000);
				break;
			
			case '4':
				//Test_RS485();
				printf("\r\n\r\nP.Log:> Config. mode is still in develop, ahihi ^^!!!");
				HAL_Delay(1000);
				break;
			
			case '5':
				//Test_Power_Sensor();
				printf("\r\n\r\nP.Log:> Config mode is still in develop, ahihi ^^!!!");
				HAL_Delay(1000);
				break;
			
			case '6':
				return;
				//break;	
			
			default:
				printf("\r\n\r\nP.Log:>Invalid input! Please choose again!\r\n");
			}
			
	}//
}

/******************************************************************************
** Function name: GSM_Module_Testing(void)
** Description: Testing GSM module(BGS2E)
** Return value: None
** Remarks: None
******************************************************************************/

void GSM_Module_Testing(void)
{
	uint8_t GSM_ans_stt = 0;
	error_counting = 0;
	char http_test_string[100];
	DBG_RX_byte[0] = '\0';
	printf("\r\n\r\n---------------BEGIN GSM TEST----------------\r\n");
	HAL_Delay(500);
	SIM_Reset();
	SIM_Check_Account(4); //Viettel
	
	HAL_Delay(200);
	
	while(DBG_RX_byte[0] != 27)
	{
		snprintf(http_test_string, sizeof(http_test_string), "/data?sensor1=%d&sensor2=%d", adc_val[0], adc_val[1]);
		modem_send_http_request("34.211.245.223:1880", http_test_string);
		//HAL_Delay(1000);
	}
	DBG_RX_byte[0] = '\0';
	
	while(DBG_RX_byte[0] != 27)
	{
		printf("\r\nP.log:> Please enter an AT-command! Press [ESC] to exit!\r\n\r\n>>User input: ");
		LedSetStatus(&led_run, 1, 10, LED_TURN_ON, 0xffff);
		do
			{
				HAL_Delay(1);	
				if(DBG_RX_byte[0] == 27) break;
			}
		while(DBG_Transfer_cplt == 0); // user complete input
		
		LedSetStatus(&led_run, 1, 1, LED_TURN_ON, 0xffff);
		
		if(DBG_RX_byte[0] == 27) break;
			
		if(DBG_Transfer_cplt == 1)
		{
			DBG_Transfer_cplt = 0;
			printf("\r\nP.log:> Sending AT-Command: \r\n< %s>", DBG_RX_Buffer);
			while((GSM_ans_stt = SIM_sendATcommand((char*)DBG_RX_Buffer, "OK", 5000)) == 0)
			{
				error_counting++;
				SIM_RST_ON();
				HAL_Delay(100);
				SIM_RST_OFF();
				HAL_Delay(100);
				if(error_counting == 10)
				{
					GSM_ans_stt = 0;
					break;
				}
			}
			//GSM_ans_stt = 1;
			
			if (GSM_ans_stt == 0)
			{
					printf("\r\nP.log:> No response - Send again!\r\n");		
					HAL_Delay(200);
			}
			
			else if (GSM_ans_stt == 1)
			{
				printf("\r\nP.log:> SEND OK!\r\n");
				HAL_Delay(200);
			} 
		}
	}
	
	printf("\r\nP.log:> End testing...\r\n");
	HAL_Delay(500);
}

/******************************************************************************
** Function name: ADC_Module_Testing(void)
** Description: Testing ADC module (DMA Mode)
** Return value: None
** Remarks: None
******************************************************************************/

void ADC_Module_Testing(void)
{
	printf("\r\n\r\n---------------BEGIN ADC TEST----------------\r\n");
	printf("\r\nP.log:> ADC value is displayed every 2 seconds!\r\n      > Press [ESC] to exit!\r\n\r\n");
	HAL_Delay(500);

	
	while(DBG_RX_byte[0] != 27 )
	{	
		printf("\r\nP.Log:");
		for(uint8_t i = 0; i < 7; i++)
		{	
			printf("> ADC value %d: %d\r\n      ", i, adc_val[i]);	
			HAL_Delay(50);
		}
		printf("\r\n");
		
		HAL_Delay(2000);
	}
	
	printf("\r\nP.log:> End testing...\r\n");
	HAL_Delay(500);
	
}

/******************************************************************************
** Function name: AM2301_Module_Testing(void)
** Description: Testing AM2301 module
** Return value: None
** Remarks: None
******************************************************************************/

void AM2301_Module_Testing(void)
{
	uint16_t humi;
	int16_t temp;
	
	printf("\r\n\r\n---------------BEGIN AM2301 TEST----------------\r\n");
	
	printf("\r\nP.log:> Humidity and temperature value is displayed every 1 seconds!\r\n      > Press [ESC] to exit!\r\n\r\n");
	HAL_Delay(500);
	
	DBG_RX_byte[0] = '\0';
	
  while(DBG_RX_byte[0] != 27)
	{
		HAL_Delay(1000);
		
		if(AM2301_Read(&temp,&humi) == 0)       
    {
      printf("\r\nP.log:> Humidity: %.2f %%\r\n        Temperature: %.2f oC", (float)humi/10, (float)temp/10);
    }
	}
}

void Demo_App(void)
{
	printf("\r\n\r\n---------------DEMO APPLICATION----------------\r\n");
	
	uint16_t adc_val_filted[7];
	
	uint16_t humi;
	int16_t temp;
	
	uint8_t GSM_ans_stt = 0;
	error_counting = 0;
	char http_test_string[200];
	DBG_RX_byte[0] = '\0';
	HAL_Delay(500);
	LedSetStatus(&led_run, 5, 10, LED_TURN_ON, 0xffff);
	
	SIM_Reset();
	
	while(DBG_RX_byte[0] != 27)
	{
		
		/* Enable Ultra low power mode */
		HAL_PWREx_EnableUltraLowPower();

		/* Enable the fast wake up from Ultra low power mode */
		HAL_PWREx_EnableFastWakeUp();
		
		if(__HAL_PWR_GET_FLAG(PWR_FLAG_SB) != RESET)
		{
				/* Clear Standby flag */
			__HAL_PWR_CLEAR_FLAG(PWR_FLAG_SB); 
		}
		printf("\r\nP.log:> Wait for sensor response\r\n");
		while(AM2301_Read(&temp,&humi) != 0)       
    {
			printf(".");
			HAL_Delay(500);
    }
		printf("\r\nP.log:> Humidity: %d %%\r\n        Temperature: %d oC\r\n", humi, temp);
				
		snprintf(http_test_string, sizeof(http_test_string), "/data?sensor1=%d&sensor2=%d&sensor3=%d&sensor4=%d&sensor5=%d&sensor6=%d", adc_val[0], adc_val[2], adc_val[3], adc_val[4], humi, temp);
		while(modem_send_http_request("34.211.245.223:1880", http_test_string) == 0)
		{
			error_counting++;
			SIM_Reset();
			if(error_counting > 5) 
			{
				printf("P.Log:> GSM error, reset system...\n\r");			
				NVIC_SystemReset();
			}			
		}
		error_counting = 0;
		//modem_send_http_request("34.211.245.223:1880", http_test_string);
		
		printf("\r\nP.log:> Enter standby mode...\r\n"); HAL_Delay(200);
		enter_stanby_mode(10000); // 10000ms = 10s
	}
	DBG_RX_byte[0] = '\0';
	
	/*
	while(1)
	{
		printf("\r|\r"); HAL_Delay(200);
		printf("\r/\r"); HAL_Delay(200);
		printf("\r-\r"); HAL_Delay(200);
		printf("\r\\\r"); HAL_Delay(200);
	}
	*/
	
	
}
	 
void Main_App(void)
{
	
}

/********************** End of file *******************************************/ 

