/**
  ******************************************************************************
  * @file    	device_user_config_app.c
  * @author  	Sang Ngoc Le
  * @version 	V2.0
  * @date    	1/3/2018
  * @brief   	This file provides all the functions for User configuration via CLI  
	*						
  ******************************************************************************
  * @copy
  * COPYRIGHT(c) 2018 NPL-SNL
  */ 
	
/* Includes ------------------------------------------------------------------*/ 
#include "device_user_config_app.h"

/* Private variables ---------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/
extern DeviceInfo_TypeDef PlogInfo;
extern uint8_t DBG_RX_index , DBG_RX_byte[2], DBG_RX_Buffer[DBG_BUFFER_SIZE], DBG_Transfer_cplt;

/* Private functions ---------------------------------------------------------*/

/******************************************************************************
** Function name: User_Config(void)
** Description: Config system through UART Interface
** Return value: None
** Remarks: None
******************************************************************************/

void User_Config(void)
{
	uint32_t count = 0;
	DBG_RX_index = 0;
	printf("\n\rP.Log:> Press 'a' to run Application!");
	printf("\n\r      > Press 'c' to enter User Configuration Mode!");
	printf("\n\r      > P.log will run application automatically in 10 seconds!");
	
	/* Waiting for user configuration */
	while((DBG_RX_byte[0] != 'c') && (DBG_RX_byte[0] != 'C'))
	{
		count++;
		HAL_Delay(1000);
		printf(".");
		if(count > 10 || (DBG_RX_byte[0] == 'a')) return;
	}
	
Config_menu:
	DBG_RX_index = 0;
	DBG_RX_byte[0] = '\0';
	LedSetStatus(&led_run,5,5,LED_TURN_ON,0xffffffff); //0.5s on, 0.5s off
	printf("\n\r\n\r>>CONFIGURATION MODE: ");
	printf("\n\r\t- Press [0] to run 'Hardware testing'.");		
	printf("\n\r\t- Press [1] to config 'Device's ID'.");
	printf("\n\r\t- Press [2] to config Sending rate.");	
	printf("\n\r\t- Press [3] to Exit");
	printf("\n\n\r>>User input: ");
	
	/* Waiting loop */
	count = HAL_GetTick();
	while((DBG_RX_byte[0] <'0') || (DBG_RX_byte[0] >'3'))
	{
		if((DBG_RX_byte[0] != '\0') && ((DBG_RX_byte[0] < '0') || (DBG_RX_byte[0] > '3')))
		{
			//putchar(DBG_RX_byte[0]);
			printf("\r\n\r\nP.Log:> Invalid input! Please choose again!\r\n");
			HAL_Delay(1000);
			goto Config_menu;
		}
		if((HAL_GetTick() - count) > 300000) 
		{
			printf("\r\n\r\nP.Log:> Config Mode Time Out!");
			return ;
		}				
	} // End of While loop of choosing.
	
	//putchar(DBG_RX_byte[0]);
	
	/* Mode 0 */
	if(DBG_RX_byte[0] == '0')
	{
		Hardware_Testing_App();
	}
	
	else if(DBG_RX_byte[0] == '1')
	{
		strcpy(PlogInfo.DEVICE_ID, DEFAULT_ID);
		char user_input[8];
		
		while(1)
		{
			
			printf("\r\n\n\r\t>>CONFIG DEVICE ID[%s]", PlogInfo.DEVICE_ID);
			printf("\n\r-->Please insert Device ID: ");
			DBG_RX_byte[0] = 0; DBG_RX_index = 0;
			DBG_Transfer_cplt = 0;
			HAL_Delay(1);
			
			LedSetStatus(&led_run, 1, 1, LED_TURN_ON, 0xffff);
			do
				{
					HAL_Delay(1);	
					if(DBG_RX_byte[0] == 27) goto Config_menu;
				}
			while(DBG_Transfer_cplt == 0); // user complete input
			
			if(DBG_Transfer_cplt == 1)
			{
				DBG_Transfer_cplt = 0;
				strcpy(user_input, (const char *)DBG_RX_Buffer);
				printf("\n\rP.log:> DEVICE ID:[%s]" , DBG_RX_Buffer);
				printf("\n\r-->Press [y] to accept.");
				printf("\n\r-->Press [n] to re-insert.");
											
				do { HAL_Delay(1); }
				while((DBG_RX_byte[0] != 'y' && DBG_RX_byte[0] != 'n'));
										
				if(DBG_RX_byte[0] == 'y')
				{
					strcpy(PlogInfo.DEVICE_ID, (const char *)user_input);
					printf("\n\rP.log:> Config success, DEVICE ID:[%s]" , PlogInfo.DEVICE_ID);
					HAL_Delay(1000);
					goto Config_menu;																			
				}
			}
		}
	}
	
	else if(DBG_RX_byte[0] == '2')
	{
		
		
		printf("\r\n\r\nP.Log:> Config mode is still in develop, ahihi ^^!!!");
		HAL_Delay(1000);
		goto Config_menu;
	}
	
	else if(DBG_RX_byte[0] == '3')
	{
		printf("\r\n\r\nP.Log:> Run Application!!!");
		HAL_Delay(1000);
		return;
	}

}

/********************** End of file *******************************************/ 
