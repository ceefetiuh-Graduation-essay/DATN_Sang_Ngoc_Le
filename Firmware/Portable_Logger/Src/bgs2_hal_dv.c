/**
  ******************************************************************************
  * @file    	bgs2_hal_dv.c
  * @author  	Sang Ngoc Le
  * @version 	V2.0
  * @date    	28/2/2018
  * @brief   	This file provides all the functions for driving BGS2 GSM module  
	*						
  ******************************************************************************
  * @copy
  * COPYRIGHT(c) 2018 NPL-SNL
  */ 
	
/* Includes ------------------------------------------------------------------*/ 
#include "bgs2_hal_dv.h"
/* Private variables ---------------------------------------------------------*/
GSMSERVICE_TYPE GSMService;

uint8_t GSM_RX_index = 0, GSM_RX_byte[1], GSM_RX_Buffer[100], GSM_Transfer_cplt = 0, get_n = 0; //Bien du lieu module GSM
uint8_t GSM_ans_stt, GSM_send_error=0, GSM_receive_error=0; //Bien trang thai module GSM, bien trang thai error

char SIM_Buff[1024];
uint8_t flag_gsm = 0;
uint8_t gsm;
uint8_t en_receive_response = 0;

uint16_t gsm_buff_count;
uint8_t SIM_Rx_data;
uint8_t GSM_RX_indx;

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
 * Function Name  : LookingForWord(char source[],char text[])
 * Description    : find and return location of the last charactor of source
 *                : string in text string
 * Input          : - source[]: string you need find
 *                : - text[]  : string contain source[]
 * Output         : None
 * Return         : - location: this's location of the last charcter
 *******************************************************************************/
int LookingForWord(char source[], char text[])
{
  int i = 0, k, l, check1 = 0, check2 = 0, location = 0, num_s = 0, num_t = 0;
  while (source[i] != '\0')
  {
    num_s++;
    i++;
  }
  i = 0;
  while (text[i] != '\0')
  {
    num_t++;
    i++;
  }
  i = 0;
  while (check1 == 0 && i < num_t)
  {
    if (source[0] == text[i]) //do tung ky tu source voi text
    {
      k = 0;
      l = i;
      while (check2 == 0 && k < num_s)
      {
        if (source[k] == text[l])
        {
          location = l + 1;
          check2 = 0;

        }
        else if (source[k] != text[l])
        {
          location = 0;
          check2 = 1;
        }
        k++;
        l++;
      }
      if (location)
        check1 = 1;
    }
    check2 = 0;
    i++;
  }
  
  /* return the last location of character in the text compare */
  return location;
}


/*******************************************************************************
 * Function Name  : user_strcmp(char *u1, char *u2)
 * Description    : compare lenght of 2 string
 * Input          : *u1 - string 1
 *                : *u2 - string 2
 * Output         : None
 * Return         : 0: same - 1: not same
 *******************************************************************************/
uint8_t user_strcmp(char *u1, char *u2)
{
  uint32_t l1, l2, i, l;

  l1 = 0;
  while (u1[l1] != '\0')
  {
    l1++;
  }

  l2 = 0;
  while (u2[l2] != '\0')
  {
    l2++;
  }
  if (l1 >= l2)
    l = l2;
  else l = l1;

  for (i = 0; i < l; i++)
  {
    if (u1[i] != u2[i])
      return 1;
  }
  return 0;
}

/*******************************************************************************
* Function Name  : DV_SIM_printf(uint8_t *s)
* Description    : send a string to SIM. This funcion same as USART3_print_str
* Input          : - *s: string sends to SIM
* Output         : None
* Return         : None
*******************************************************************************/
void DV_SIM_printf(uint8_t *s)
{
	uint32_t i = 0;	
	/* counts lenght of data string*/
  while (s[i] != '\0')
  {
    i++;
  }
	HAL_UART_Transmit(&huart1, (uint8_t *)s, i, 0xff);
}

/*******************************************************************************
* Function Name  : DV_SIM_AT_Cmd(char* data)
* Description    : Send a command to SIM
* Input          : - *data: this is string command 
* Output         : None
* Return         : - 1: not error - 0: error
*******************************************************************************/
uint8_t DV_SIM_AT_Cmd(char *data)
{
  uint32_t i = 0;
  uint8_t error = 1;
  uint16_t time_out = 1000;
  
  /* counts lenght of data string*/
  while (data[i] != '\0')
  {
    i++;
  }
  
  /* send data string to sim */
	DV_SIM_printf((uint8_t *) data);
  //HAL_UART_Transmit(&hlpuart1, (uint8_t *)data, i, 1000);
  /* clear buff */
  SIM_Buff[0] = ' ';
  SIM_Buff[1] = ' ';
  
  /* send <CR> */
	//HAL_UART_Transmit(&hlpuart1, (uint8_t *)0x0d, 1, 1);
	//HAL_UART_Transmit(&hlpuart1, (uint8_t *)0x0a, 1, 1);
  //USART_SendData(SIM_USART_X,0x0d);
  //while (USART_GetFlagStatus(SIM_USART_X, USART_FLAG_TC) == 0);
  
  while (1)
  {
    if (user_strcmp(SIM_Buff, "OK") == 0)
    {
      error = 0;
      break;
    }
    if (user_strcmp(SIM_Buff, "ERROR") == 0)
    {
      error = 1;
			//printf("%s\r\n", SIM_Buff); 
      break;
    }
//		if (strstr(SIM_Buff, "OK") != NULL)
//    {
//      error = 0;
//			printf("%s\r\n", SIM_Buff); 
//      break;
//    }
//    if (strstr(SIM_Buff, "ERROR") != NULL)
//    {
//      error = 1;
//			printf("%s\r\n", SIM_Buff); 
//      break;
//    }
    HAL_Delay(1);
    time_out--;
    if (!time_out) return 0;
  }
  
//  delay_ms(150);
	printf("%s\r\n", SIM_Buff);
  if (error == 0) return 1;
  else return 0; //Error
}

/*******************************************************************************
* Function Name  : DV_SIM_AT_Sync(void)
* Description    : synchronous baudrate of module sim with MCU
* Input          : None
* Output         : None
* Return         : - 1: not error - 0: error
*******************************************************************************/
uint8_t DV_SIM_AT_Sync(void)
{
  uint8_t count = 0;

  printf("\n\rSend \"AT\" command to synchronous baudrate\n\r");

  while (count < 20)
  {
    /* send "AT" command to synchronous module sim */
    if (DV_SIM_AT_Cmd("AT\r\n") == 0)
		{
      count++;
			printf("SIM_Buff= <%s>\r\n", SIM_Buff);
		}
    else 
      return 1;
  }
  //DV_SIM_AT_Cmd("AT+CREG=1");			//Activates extended URC mode.
  //DV_SIM_AT_Cmd("AT+CGREG=1");
  return 0;
}

/*******************************************************************************
* Function Name  : DV_SIM_Check_Service(void)
* Description    : check sim service provider
* Input          : None
* Output         : None
* Return         : 0 - error
*                  1 - VinaPhone
*                  2 - Viettel
*                  3 - MobiPhone
*                  4 - VietnamMobile
*******************************************************************************/
uint8_t DV_SIM_Check_Service(void)
{
  uint16_t time_out = 60, i = 0;
  
  printf("\r\nCheck sim service provider\n\r");
  
  /* clear receive buffer */
  for (i = 0; i < 400; i++)
  {
    SIM_Buff[i] = ' ';
  }
  
  /* check sim service provider */
  DV_SIM_AT_Cmd("AT+COPS?");
  
  while (user_strcmp(&SIM_Buff[13], "      ") == 0)
  {
    /* check sim service provider */
    DV_SIM_AT_Cmd("AT+COPS?"); 
    HAL_Delay(1000);
    time_out--;
    if (!time_out) return 0;
  }
  
  if ((user_strcmp(&SIM_Buff[12], "VNM and VIETTEL") == 0))
  {
    printf("SIM: Viettel\n\r");
    return Viettel;
  }

  else if ((user_strcmp(&SIM_Buff[12], "VN MOBIFONE") == 0))
  {
    printf("SIM: MobiPhone\n\r");
    return MobiPhone;
  }

  else if ((user_strcmp(&SIM_Buff[12], "VN VINAPHONE") == 0))
  {
    printf("SIM: VinaPhone\n\r");
    return VinaPhone;
  }

  else if ((user_strcmp(&SIM_Buff[12], "MOBIFONE") == 0))
  {
    printf("SIM: MobiPhone\n\r");
    return MobiPhone;
  }
  else 
  {
    return 0;
  }
}

/*******************************************************************************
* Function Name  : DV_SIM_Gprs_On(uint8_t SIM_Service)
* Description    : enable GPRS
* Input          : SIM_Service
* Output         : None
* Return         : None
*******************************************************************************/
uint8_t DV_SIM_Gprs_On(uint8_t SIM_Service)
{
  printf("Turn on GPRS\r\n");
  
  DV_SIM_AT_Cmd("AT");
  DV_SIM_AT_Cmd("AT^SICS=1,conType,GPRS0");
  DV_SIM_AT_Cmd("AT^SICS=1,alphabet,1");
  switch (SIM_Service)
  {
    case VinaPhone:
      DV_SIM_AT_Cmd("AT^SICS=0,user,\"mms\"");
      DV_SIM_AT_Cmd("AT^SICS=0,passwd,\"mms\"");
      DV_SIM_AT_Cmd("AT^SICS=0,apn,\"m3-world\"");
      break;
    case MobiPhone:
      DV_SIM_AT_Cmd("AT^SICS=0,user,\"mms\"");
      DV_SIM_AT_Cmd("AT^SICS=0,passwd,\"mms\"");
      DV_SIM_AT_Cmd("AT^SICS=0,apn,\"m-wap\"");
      break;
    case Viettel:
      DV_SIM_AT_Cmd("AT^SICS=0,user,\"\"");
      DV_SIM_AT_Cmd("AT^SICS=0,passwd,\"\"");
      DV_SIM_AT_Cmd("AT^SICS=0,apn,\"v-internet\"");
      break;
    case VietnamMobile:
      DV_SIM_AT_Cmd("AT^SICS=0,user,\"\"");
      DV_SIM_AT_Cmd("AT^SICS=0,passwd,\"\"");
      DV_SIM_AT_Cmd("AT^SICS=0,apn,\"internet\"");
      break;
    default:
      printf("SIM Error\n\r");
      break;
  }

  DV_SIM_AT_Cmd("AT^SICI=0");
  //DV_SIM_AT_Cmd("AT^SISS?");
  DV_SIM_AT_Cmd("AT^SISS=0,srvType,Socket");
  DV_SIM_AT_Cmd("AT^SISS=0,conId,0");
  DV_SIM_AT_Cmd("AT^SISS=0,alphabet,1");
  //DV_SIM_AT_Cmd("AT^SISS=0,address,\"socktcp://hbqsolution.com:80\"");

  return 1;
}

/*******************************************************************************
 * Function Name  : DV_SIM_Startup(void)
 * Description    : startup module Sim BG2
 * Input          : None
 * Output         : None
 * Return         : - gsm_service: service provider
 *                  - 0: error
 *******************************************************************************/
uint8_t DV_SIM_Startup(void)
{
  uint8_t gsm_service = 0x00;
  uint32_t i;

  /* clear receive buffer */
  for (i = 0; i < 400; i++)
  {
    SIM_Buff[i] = ' ';
  }
  
  /* synchronous module sim */
  if (DV_SIM_AT_Sync() == 0)
  {
    printf("Error..\n\r");
    return 0;
  }

  DV_SIM_AT_Cmd("ATE1");
  DV_SIM_AT_Cmd("ATE1");
  
  /* check sim service provider */
  gsm_service = DV_SIM_Check_Service();

  if (gsm_service==0)
  {
    printf("Error..\n\r");
    return 0;
  }
  
  /* Signal quality */
  DV_SIM_AT_Cmd("AT+CSQ");

  /* turn on GPRS */
  if (DV_SIM_Gprs_On(gsm_service) == 0)
  {
    printf("Error..\n\r");
    return 0;
  }
  
  HAL_Delay(1000);
  return gsm_service;
}

/*******************************************************************************
* Function Name  : DV_SIM_Reset(void)
* Description    : Reset module sim
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint8_t DV_SIM_Reset(void)
{
  uint8_t sim = 0;
  uint16_t i = 0;
  
  /* Clear buff */
  for (i = 0; i < 400; i++)
  {
    SIM_Buff[i] = ' ';
  }
  
  printf("\n\rTurn power on");
  //VSIM_OFF();
  //delay_ms(10);
  //VSIM_ON();
  
  SIM_OFF();
  HAL_Delay(100);
  SIM_ON();
  HAL_Delay(100);
  
  SIM_RST_ON();
  HAL_Delay(15);
  SIM_RST_OFF();
  HAL_Delay(5000);
  
  sim = DV_SIM_Startup();
  if (sim) gsm = 1;
  else gsm = 0;
  
  return sim;
}

/*******************************************************************************
* Function Name  : SIM_Reset(void)
* Description    : Reset module sim
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint8_t SIM_Reset(void)
{
  uint8_t sim = 0;
  //uint16_t i = 0;
  
  /* Clear SIM buffer */
	memset(SIM_Buff, '\0', 400);

  printf("\r\nTurn power on\r\n");
  
  SIM_OFF();
  HAL_Delay(200);
  SIM_ON();
  HAL_Delay(500);
  printf("\r\nSIM_ON\r\n");

  SIM_RST_ON();
  HAL_Delay(100);
  SIM_RST_OFF();
  HAL_Delay(100);
  
  sim = SIM_Startup();
  if (sim) gsm = 1;
  else gsm = 0;
  
  return sim;
}


// Ham goi lenh AT
/*******************************************************************************
* Function Name  : SIM_sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout)
* Description    : Send a command to SIM
* Input          : - ATcommand: this is a AT string command 
									 - expected_answer: expected answer response from GSM-Module
									 - timeout: time wait for answer
* Output         : None
* Return         : - 1: not error - 0: error
*******************************************************************************/
uint8_t SIM_sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout)
{
  uint8_t answer = 0; //, len=0;
	get_n = 0;
	gsm_buff_count = 0;
  //char response[100];
  uint32_t previous; // time;

  //memset(response, '\0', 100);    // Initialize the string - Clean the input buffer
	memset(SIM_Buff, '\0', 1024);
  HAL_Delay(50);
 
	printf("\r\n>GSM: Sending command \r\n<%s>\r\n", ATcommand);
	en_receive_response = 1;
	
	if(HAL_UART_Transmit(&huart1, (uint8_t*)ATcommand, strlen(ATcommand), 1000)!= HAL_OK) // Send the AT command 
  {
		GSM_send_error = 1; answer = 0;
    _Error_Handler(__FILE__, __LINE__);   
  }
	
	previous = HAL_GetTick(); //Get the time when complete sending an at-command
	
	/*DEBUG
	//HAL_UART_Transmit_IT(&hlpuart1, (uint8_t*)ATcommand, len); 
	//printf("start time = %ld\r\n", previous);
	//End DEBUG */

  // this loop waits for the answer
  do
		{			
			if((strstr((const char*)SIM_Buff, (const char*)expected_answer) != NULL ))	
			{
				answer = 1;
				GSM_Transfer_cplt=0;
				break;
			}
			
			if(GSM_Transfer_cplt == 1)
			{				 	
				//strcpy(response,(const char*) SIM_Buff);
				if((strstr((const char*)SIM_Buff, (const char*)expected_answer) != NULL ))	
				{
					answer = 1;
				}
				GSM_Transfer_cplt=0;
			}
		}
  // Waits for the asnwer with time out
  while((answer == 0) && ((HAL_GetTick() - previous) < timeout));  
		
	/*DEBUG
	//printf("Final wait time = %ld\r\n", (HAL_GetTick() - previous)); // Hien thi thoi gian cho	
	printf("GSM_RX_Buffer = <%s>\r\n", GSM_RX_Buffer); // Hien thi buffer da nhan
	//printf("Response = \r\n<%s>\r\n", response); 					 // Hien thi response da nhan	
	printf("\r\nResponse = \r\n< %s >\r\n", SIM_Buff); // Hien thi buffer da nhan
	//End DEBUG*/
	if(answer == 0)
		printf("\r\n>GSM: FAIL\r\n");
	else
		printf("\r\n>GSM: <%s> OK\r\n", SIM_Buff);
  return answer;
}


/*******************************************************************************
* Function Name  : SIM_AT_Sync(void)
* Description    : synchronous baudrate of module sim with MCU
* Input          : None
* Output         : None
* Return         : - 1: not error - 0: error
*******************************************************************************/
uint8_t SIM_AT_Sync(void)
{
  uint8_t count = 0;

  printf("\n\rSend \"AT\" command to synchronous baudrate\n\r");

  while (count < 20)
  {
    /* send "AT" command to synchronous module sim */
    if (SIM_sendATcommand("AT\r\n", "OK", 500) == 0)
		{
			count++;
		}
    else 
		{
			printf("Sync success\r\n");
			return 1;
		}
      
  }
  //SIM_sendATcommand("AT+CREG=1", "OK", 500);			//Activates extended URC mode.
  //SIM_sendATcommand("AT+CGREG=1", "OK", 500);
  return 0;
}

/*******************************************************************************
* Function Name  : SIM_Check_Service(void)
* Description    : check sim service provider
* Input          : None
* Output         : None
* Return         : 0 - error
*                  1 - VinaPhone
*                  2 - Viettel
*                  3 - MobiPhone
*                  4 - VietnamMobile
*******************************************************************************/
uint8_t SIM_Check_Service(void)
{
  uint16_t time_out = 50; //, i = 0;
  
  printf("\r\nCheck sim service provider\n\r");
  
  /* clear receive buffer */
	 memset(SIM_Buff, '\0', 400);

  /* check sim service provider */
  
	SIM_sendATcommand("AT+COPS?\r\n", "OK", 200);
	HAL_Delay(200);
	SIM_sendATcommand("AT+COPS?\r\n", "OK", 200);
	HAL_Delay(200);
	SIM_sendATcommand("AT+COPS?\r\n", "OK", 200);
  
  while (strstr(SIM_Buff, "+COPS: 0,0") == NULL)
  {
    /* check sim service provider */
    SIM_sendATcommand("AT+CSQ\r\n", "OK", 200);
    HAL_Delay(200);
		SIM_sendATcommand("AT+COPS?\r\n", "OK", 200); 
		HAL_Delay(200);
    time_out--;
    if (!time_out) return 0;
  }
  
  if ((strstr(SIM_Buff, "VIETTEL") != NULL))
  {
    printf("\r\nSIM: Viettel\n\r");
    return Viettel;
  }

  else if ((strstr(SIM_Buff, "MOBIFONE") != NULL))
  {
    printf("\r\nSIM: MobiPhone\n\r");
    return MobiPhone;
  }
	
	  else if ((strstr(SIM_Buff, "Vietnamobile") != NULL))
  {
    printf("\r\nSIM: Vietnamobile\n\r");
    return VietnamMobile;
  }

  else if ((strstr(SIM_Buff, "VN VINAPHONE") != NULL))
  {
    printf("\r\nSIM: VinaPhone\n\r");
    return VinaPhone;
  }

  else 
  {
    return 0;
  }
}


/*******************************************************************************
 * Function Name  : SIM_Startup(void)
 * Description    : startup module Sim BG2
 * Input          : None
 * Output         : None
 * Return         : - gsm_service: service provider
 *                  - 0: error
 *******************************************************************************/
uint8_t SIM_Startup(void)
{
  uint8_t gsm_service = 0x00;
  //uint32_t i;

  /* clear receive buffer */
	 memset(SIM_Buff, '\0', 400);
 
  /* synchronous module sim */
  if (SIM_AT_Sync() == 0)
  {
    printf("Error..\n\r");
    return 0;
  }
	HAL_Delay(500);
  SIM_sendATcommand("ATE1\r\n", "OK", 500); //Echo mode off

  /* check sim service provider */
  gsm_service = SIM_Check_Service();

  if (gsm_service==0)
  {
    printf("Error..\n\r");
    return 0;
  }
  HAL_Delay(500);
  /* Signal quality */

	SIM_sendATcommand("AT+CSQ\r\n", "OK", 200);
	
  /* turn on GPRS */
  if (SIM_Gprs_On(gsm_service) == 0)
  {
    printf("GPRS Error..\n\r");
		//SIM_Gprs_On(Viettel);
    return 0;
  }
  
  HAL_Delay(1000);
  return gsm_service;
}


/*******************************************************************************
* Function Name  : SIM_Gprs_On(uint8_t SIM_Service)
* Description    : enable GPRS
* Input          : SIM_Service
* Output         : None
* Return         : None
*******************************************************************************/
uint8_t SIM_Gprs_On(uint8_t SIM_Service)
{
  printf("\r\nTurn on GPRS\r\n");
  
	HAL_Delay(1);
	while(SIM_sendATcommand("AT\r\n", "OK", 200) == 0);
	
	HAL_Delay(1);
	memset(SIM_Buff, '\0', 400);
	SIM_sendATcommand("AT^SICS=1,conType,GPRS0\r\n", "OK", 1000);

	HAL_Delay(1);
	SIM_sendATcommand("AT^SICS=1,alphabet,1\r\n", "OK", 1000);

	HAL_Delay(1);
  switch (SIM_Service)
  {
		
    case VinaPhone:
      
			HAL_Delay(1);
			SIM_sendATcommand("AT^SICS=1,user,\"mms\"\r\n", "OK", 1000);
      
			HAL_Delay(1);
			SIM_sendATcommand("AT^SICS=1,passwd,\"mms\"\r\n", "OK", 200);
      
			HAL_Delay(1);
			SIM_sendATcommand("AT^SICS=1,apn,\"m3-world\"\r\n", "OK", 200);
			HAL_Delay(1);	
      break;
		
    case MobiPhone:
	     
			HAL_Delay(1);
			SIM_sendATcommand("AT^SICS=1,user,\"mms\"\r\n", "OK", 1000);
		
			HAL_Delay(1);
			SIM_sendATcommand("AT^SICS=1,passwd,\"mms\"\r\n", "OK", 1000);
      
			HAL_Delay(1);
			SIM_sendATcommand("AT^SICS=1,apn,\"m-wap\"\r\n", "OK", 1000);
			HAL_Delay(1);
      break;
		
    case Viettel:
       
			SIM_sendATcommand("AT^SICS=1,user,\"\"\r\n", "OK", 200);
       
			SIM_sendATcommand("AT^SICS=1,passwd,\"\"\r\n", "OK", 200);
       
			SIM_sendATcommand("AT^SICS=1,apn,\"v-internet\"\r\n", "OK", 200);
      break;
		
		case VietnamMobile:
       
			SIM_sendATcommand("AT^SICS=1,user,\"vietnamobile\"\r\n", "OK", 200);
       
			SIM_sendATcommand("AT^SICS=1,passwd,\"\"\r\n", "OK", 200);
       
			SIM_sendATcommand("AT^SICS=1,apn,\"internet\"\r\n", "OK", 200);
      break;
		
		
    default:
      printf("SIM Error\n\r");
		
			SIM_sendATcommand("AT^SICS=1,user,\"\"\r\n", "OK", 200);
       
			SIM_sendATcommand("AT^SICS=1,passwd,\"\"\r\n", "OK", 200);
       
			SIM_sendATcommand("AT^SICS=1,apn,\"v-internet\"\r\n", "OK", 200);
      break;
  }

  
	HAL_Delay(1);
	SIM_sendATcommand("AT^SICI=1\r\n", "OK", 1000);

	HAL_Delay(1);
	SIM_sendATcommand("AT^SISS=1,srvType,\"Http\"\r\n", "OK", 1000);

	HAL_Delay(1);
	SIM_sendATcommand("AT^SISS=1,conId,1\r\n", "OK", 1000);
	
	HAL_Delay(1);
	SIM_sendATcommand("AT^SISS=1,hcMethod,0\r\n", "OK", 1000);

	HAL_Delay(1);
	SIM_sendATcommand("AT^SISS=1,alphabet,1\r\n", "OK", 1000);
	HAL_Delay(1);

	printf("GPRS OK...\n\r");
  return 1;
}


/************************* End of File ****************************************/

