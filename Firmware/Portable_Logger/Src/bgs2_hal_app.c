/**
  ******************************************************************************
  * @file    	bgs2_hal_app.c
  * @author  	Sang Ngoc Le
  * @version 	V2.0
  * @date    	28/2/2018
  * @brief   	This file provides all the functions for BGS2 Appplication    
	*						
  ******************************************************************************
  * @copy
  * COPYRIGHT(c) 2018 NPL-SNL
  */ 
	
/* Includes ------------------------------------------------------------------*/ 
#include "bgs2_hal_app.h"
#include "bgs2_hal_dv.h"
#include "string.h"

/* Private variables ---------------------------------------------------------*/


/* Global variables ----------------------------------------------------------*/
extern char SIM_Buff[1024];
extern uint8_t flag_gsm;
extern uint8_t gsm;

//char http[50]="www.hbqsolution.com";
//char dataFrame[20]="SANG_TEST_G4300";
//char test_string_http[100] = "AT^SISS=1,address,\"socktcp://www.hbqsolution.com:80\"\r\n";
//char test_string_http_2[100] = "GET /DEMO/wd.php?pk=SANG_HELLO HTTP/1.1\r\nHost: www.hbqsolution.com:80\r\n\r\n";
extern uint16_t gsm_buff_count;
extern uint8_t flag_gsm;
extern uint8_t SIM_Rx_data;

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : SIM_Init
* Description    : demo Programmer
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
uint8_t SIM_Init(void)
{
  uint8_t result = 0;
  
  result = SIM_Reset();
  if(result==0)
    printf("Init error\r\n");
  else
    printf("Init Success\r\n");
  
  return result;
}

/*******************************************************************************
* Function Name  : SIM_Check_Account(uint8_t SIM_Service)
* Description    : check money account of SIM
* Input          : SIM_Service: sim service provider
* Output         : None
* Return         : 0 - error; 1 - ok
*******************************************************************************/
uint8_t SIM_Check_Account(uint8_t SIM_Service)
{
  uint16_t time_out = 100;
  SIM_sendATcommand("ATD*101#;\r\n", "+CUSD: ", 3000);
  HAL_Delay(1000);
  
  while (strstr(SIM_Buff, "+CUSD: ") == NULL)
  {
    HAL_Delay(10);
    time_out--;
    if (!time_out) return 0;
  }
  
	printf("\r\n>GSM:  %s \r\n", SIM_Buff);
	
  if (SIM_Service == Viettel)
  {
    time_out = 100;
    SIM_sendATcommand("ATD*102#;\r\n", "OK", 500);
    HAL_Delay(1000);
    while (user_strcmp(&SIM_Buff[0], "+CUSD: ") == 1)
    {
      HAL_Delay(10);
      time_out--;
      if (!time_out) return 0;
    }
  }
  return 1;
}


/*******************************************************************************
* Function Name  : SIM_Send_SMS(char *num, char *sms)
* Description    : demo Programmer
* Input          : - *num: mobile number need sending
                 : - *sms: message content
* Output         : None
* Return         : 0 - error; 1 - ok
*******************************************************************************/
uint8_t SIM_Send_SMS(char *num, char *sms)
{
  uint8_t time_out = 100;
  
  /* set SMS text mode */
  DV_SIM_AT_Cmd("AT+CMGF=1");
  
  /* delete message stored at memory stack 1 */
  DV_SIM_AT_Cmd("AT+CMGD=1");
  
  /* send mobile number */
  DV_SIM_printf((uint8_t*) "AT+CMGS=\"");
  DV_SIM_printf((uint8_t*) num);
  DV_SIM_printf((uint8_t*) "\"\r");
  HAL_Delay(100);
  
  while (user_strcmp(&SIM_Buff[0], ">") == 1)
  {
    HAL_Delay(500);
    time_out--;
    if (!time_out) return 0;
  }
  
  /* send SMS content */
  DV_SIM_printf((uint8_t*) sms);
	HAL_UART_Transmit(&huart1, (uint8_t *)0x1a, 1, 1000);

  /* set timeout */
  time_out = 100;
  
  while (user_strcmp(&SIM_Buff[0], "OK") == 1)
  {
    HAL_Delay(500);
    time_out--;
    if (!time_out || user_strcmp(&SIM_Buff[0], "ERROR") == 0) return 0;
  }
  
  return 1;
}


/*******************************************************************************
* Function Name  : SIM_Sync_Time(uint8_t service_sim)
* Description    : synchronous the time of device with sim service provider
* Input          : service_sim: sim service provider
* Output         : None
* Return         : 0 - error; 1 - success
*******************************************************************************/
uint8_t SIM_Sync_Time(uint8_t service_sim)
{
//  uint8_t time_out = 100, i = 0, tem = 0;
//  tDATETIME Synch_time;
//  
//  DV_SIM_AT_Cmd("AT+CNMI=1,1");
//  
//  switch (service_sim)
//  {
//    case VinaPhone:
//      if (!SIM_Send_SMS("333", "Test")) return 0;
//      break;
//    case Viettel:
//      if (!SIM_Send_SMS("9119", "Test")) return 0;
//      break;
//    case MobiPhone:
//      if (!SIM_Send_SMS("900", "Test")) return 0;
//      break;
//    case VietnaMobile:
//      if (!SIM_Send_SMS("123", "Test")) return 0;
//      break;
//    case BeeLine:
//      if (!SIM_Send_SMS("9119", "Test")) return 0;
//      break;
//  }
//  
//  while (user_strcmp(&SIM_Buff[0], "+CMTI:") == 1)
//  {
//    HAL_Delay(500);
//    time_out--;
//    if (!time_out) return 0;
//  }
//  
//  time_out = 100;
//  flag_gsm = 0;
//  HAL_Delay(10);
//  
//  /* read SMS stored at memory stack 1 */
//  DV_SIM_AT_Cmd("AT+CMGR=1");
//  
//  while (user_strcmp(&SIM_Buff[12], "+CMGR:") == 1)
//  {
//    HAL_Delay(100);
//    time_out--;
//    if (!time_out) return 0;
//  }
//  
//  /* export time synch to terminal console */
//  i = LookingForWord("\",,\"", SIM_Buff);
//  tem = (SIM_Buff[i++] - 48)*10;
//  Synch_time.Year = 2000 + SIM_Buff[i++] - 48 + tem;
//  i++;
//  tem = (SIM_Buff[i++] - 48)*10;
//  Synch_time.Month = SIM_Buff[i++] - 48 + tem;
//  i++;
//  tem = (SIM_Buff[i++] - 48)*10;
//  Synch_time.Day = SIM_Buff[i++] - 48 + tem;
//  i++;
//  tem = (SIM_Buff[i++] - 48)*10;
//  Synch_time.Hour = SIM_Buff[i++] - 48 + tem;
//  i++;
//  tem = (SIM_Buff[i++] - 48)*10;
//  Synch_time.Minutes = SIM_Buff[i++] - 48 + tem;
//  i++;
//  tem = (SIM_Buff[i++] - 48)*10;
//  Synch_time.Second = SIM_Buff[i++] - 48 + tem;
//  
//  printf("\n\rTIME:%0.2d:%0.2d:%0.2d,%0.4d/%0.2d/%0.2d\n\r"\
//         ,Synch_time.Hour, Synch_time.Minutes, Synch_time.Second, Synch_time.Year, Synch_time.Month, Synch_time.Day);

//  //CLD_Set_Calendar(Synch_time);
//  flag_gsm = 1;
//  time_out = 100;
//  
//  /* delete sms */
//  DV_SIM_AT_Cmd("AT+CMGD=1");
//  while (user_strcmp(&SIM_Buff[0], "OK") == 1)
//  {
//    HAL_Delay(500);
//    time_out--;
//    if (!time_out) return 0;
//  }
//  
//  DV_SIM_AT_Cmd("AT+CNMI=0");
  return 1;
}


/*******************************************************************************
* Function Name  : SIM_Signal_Quality(void)
* Description    : check signal quality
* Input          : None
* Output         : 0 -113 dBm or less
                   1 -111 dBm
                   2..30 -109... -53 dBm
                   31 -51 dBm or greater
                   99 not known or not detectable
* Return         : None
* Attention      : None
*******************************************************************************/
uint8_t SIM_Signal_Quality(void)
{
  SIM_sendATcommand("AT+CSQ\r\n", "OK", 500);
  if (SIM_Buff[7] != ',')
    return ((SIM_Buff[6] - 0x30)*10 + (SIM_Buff[7] - 0x30));
  else return (SIM_Buff[6] - 0x30);
}


/*******************************************************************************
* Function Name  : SIM_Http_Request(char *http, char *dataFrame)
* Description    : reques data frame to http address server
* Input          : - *http: address server
*                : - *dataFrame: data
* Output         : None
* Return         : 0 - error; 1 - success
*******************************************************************************/
uint16_t sample_time; // this variable used to set and get times send data to server

uint8_t SIM_Http_Request(char *http, char *dataFrame, uint16_t port)
{
  uint16_t http_length = 0, data_length = 0, total_length = 0;
  const char tcp_add[29] = "AT^SISS=1,address,\"socktcp://"; 
	
  char AT_Cmd_send_frame[15], port_final[10], tcp_str[100];
	char upload_frame[100];
  uint16_t time_out = 5000, point = 0, start = 0;

	printf("TCP Init...\r\n");
	/* clear buffer */
	memset(SIM_Buff, '\0', 400);
	
  /* Set phone full functionally */
	SIM_sendATcommand("AT+CREG?\r\n", "OK", 1000);
	SIM_sendATcommand("AT+CFUN=1\r\n", "OK", 1000);
	SIM_sendATcommand("AT^SISS=1,srvType,Socket\r\n", "OK", 1000);
	SIM_sendATcommand("AT^SISO?\r\n", "OK", 1000);
	HAL_Delay(500);
	SIM_sendATcommand("AT^SISI?\r\n", "OK", 1000);
	HAL_Delay(500);
	SIM_sendATcommand("AT^SICI?\r\n", "OK", 1000);
	HAL_Delay(500);
	SIM_sendATcommand("AT^SISC=1\r\n", "OK", 200);
	HAL_Delay(500);
	memset(SIM_Buff, '\0', 400);
  HAL_Delay(50);
	
	/* 1 send tcp address, http server, port */
//	printf("test string: %s\r\n", test_string_http);
//	HAL_UART_Transmit_IT(&hlpuart1, (uint8_t*)test_string_http, strlen(test_string_http));
//	HAL_Delay(1000);
//	printf("\r\nBuffer = \r\n<%s>\r\n", SIM_Buff);
//	HAL_Delay(1000);

	/* 2 send tcp address, http server, port */
  sprintf(port_final, ":%d\"\r\n", port);
	snprintf(tcp_str, sizeof(tcp_str), "%s%s%s\r\n", tcp_add, http, port_final);
	printf("String = %s\r\n", tcp_str);	
	HAL_UART_Transmit_IT(&huart1, (uint8_t*)tcp_str, strlen(tcp_str));
	HAL_UART_Transmit_IT(&huart1, (uint8_t*)("\r\n"), strlen(("\r\n")));
	
  HAL_Delay(500);
  time_out = 1000;
	HAL_Delay(1000);

  while (strstr(SIM_Buff, "OK") == NULL)
  {
    HAL_Delay(100);
    time_out--;
    if (!time_out)
		{
			printf("time_out...\r\n");
			printf("ALL_Buffer: \r\n<%s>\r\n", SIM_Buff);
			return 0;
		}			
    if(strstr(SIM_Buff, "ERROR") != NULL) 
		{
			printf("Init ERROR\r\n");
			printf("ALL_Buffer: \r\n<%s>\r\n", SIM_Buff);
			return 0;
		}
			
  };	
	
	HAL_Delay(100);
	printf("Init OK\r\n");
	printf("ALL_Buffer: \r\n<%s>\r\n", SIM_Buff);
	
	SIM_sendATcommand("AT^SISS=1,conId,0\r\n", "OK", 1000);
	/* clear buffer */
	memset(SIM_Buff, '\0', 400);
  HAL_Delay(1500);

  /* connecting to GPRS */
  printf("\nGPRS Connecting..\n\r");
  while (SIM_sendATcommand("AT^SISO=1\r\n", "^SISW: 1, 1", 10000) == 0)   // open service
  {
    printf("\nGPRS Not ready...\n\r");
    HAL_Delay(100);         
		SIM_sendATcommand("AT^SISC=1\r\n", "OK", 200);  // close service if fail to open
    return 0;
  }
  HAL_Delay(100);
  

	sprintf(port_final, ":%d", port);
	snprintf(upload_frame, sizeof(upload_frame), "GET /DEMO/wd.php?pk=%s HTTP/1.1\r\nHost: %s%s\r\n\r\n", dataFrame, http, port_final);

	total_length = strlen(upload_frame);
	HAL_Delay(50);
	/* clear buffer */
	memset(SIM_Buff, '\0', 400);
  HAL_Delay(50);
	
  sprintf(AT_Cmd_send_frame, "AT^SISW=1,%d\r\n", total_length);

	HAL_UART_Transmit(&huart1, (uint8_t*)AT_Cmd_send_frame, strlen(AT_Cmd_send_frame),0xffff);
  time_out = 2000;
  while (strstr(SIM_Buff, "^SISW:") == NULL)//strcmp(&SIM_Buff[0], "^SISW: 0,") != 0)
  {
    HAL_Delay(1);
    time_out--;
    if (!time_out) return 0;
  }
	HAL_Delay(1000);
	printf("Buffer: \r\n<%s>\r\n", SIM_Buff);
		HAL_Delay(1000);
	/* clear buffer */
	memset(SIM_Buff, '\0', 400);
  HAL_Delay(100);
	printf("sending test string: %s\r\n", upload_frame);
	HAL_UART_Transmit(&huart1, (uint8_t*)upload_frame, strlen(upload_frame),0xffff);
	HAL_Delay(10000);
	printf("Buffer: \r\n<%s>\r\n", SIM_Buff);
	HAL_Delay(2000);
	while (strstr(SIM_Buff, "^SISR: 1") == NULL) //(user_strcmp(&SIM_Buff[0], "^SISR: 0") != 0)
  {
		HAL_UART_Transmit(&huart1, (uint8_t*)("\r\n"), strlen(("\r\n")), 500);
    HAL_Delay(10);
    time_out--;
    if (!time_out) return 0;
  }

	SIM_sendATcommand("AT^SISC=1\r\n", "OK", 200);	//Internet Service Close
	printf("\nHTTP request succeed, closing connection!\n\r");
	HAL_Delay(500);
  //if (sample_time > 15) DV_SIM_AT_Cmd("AT+CFUN=9,0");
  return 1;
}

/*******************************************************************************
* Function Name  : modem_send_http_request(char *http, char *dataFrame)
* Description    : reques data frame to http address server
* Input          : - *http: address server
*                : - *dataFrame: data
* Output         : None
* Return         : 0 - error; 1 - success
*******************************************************************************/

uint8_t modem_send_http_request(char *http, char *dataFrame)
{
  uint16_t http_length = 0, data_length = 0, total_length = 0;
  const char http_add[29] = "AT^SISS=1,address,\"http://"; 
	
  char AT_Cmd_send_frame[15], http_str[150];
	char upload_frame[150];
  uint16_t time_out = 5000, point = 0, start = 0;

	printf("HTTP Init...\r\n");
	/* clear buffer */
	memset(SIM_Buff, '\0', 400);
	
  /* Set modem full functionally */
	SIM_sendATcommand("AT+CREG?\r\n", "OK", 1000);
	SIM_sendATcommand("AT+CFUN=1\r\n", "OK", 1000);
	SIM_sendATcommand("AT^SISS=1,\"srvType\",\"Http\"\r\n", "OK", 2000);
	SIM_sendATcommand("AT^SISS=1,\"conId\",1\r\n", "OK", 2000);
	SIM_sendATcommand("AT^SISS=1,hcMethod,0\r\n", "OK", 2000);
	
	SIM_sendATcommand("AT^SISO?\r\n", "OK", 1000);
	SIM_sendATcommand("AT^SISI?\r\n", "OK", 1000);
	SIM_sendATcommand("AT^SICI?\r\n", "OK", 1000);
	
	memset(SIM_Buff, '\0', 400);
  HAL_Delay(50);
	
	/* Set address and data frame  */
	snprintf(http_str, sizeof(http_str), "%s%s%s\"\r\n", http_add, http, dataFrame);
	SIM_sendATcommand(http_str, "OK", 2000);	

  time_out = 1000;
	HAL_Delay(500);

  while(strstr(SIM_Buff, "OK") == NULL)
  {
    HAL_Delay(100);
    time_out--;
    if (!time_out)
		{
			printf("time_out...\r\n");
			printf("ALL_Buffer: \r\n<%s>\r\n", SIM_Buff);
			return 0;
		}			
    if(strstr(SIM_Buff, "ERROR") != NULL) 
		{
			printf("ERROR...\r\n");
			printf("ALL_Buffer: \r\n<%s>\r\n", SIM_Buff);
			return 0;
		}		
  }	
	
	HAL_Delay(100);
	printf("OK\r\n");
	//printf("ALL_Buffer: \r\n<%s>\r\n", SIM_Buff);
	
	SIM_sendATcommand("AT^SISS?\r\n", "OK", 1000);
	
	/* clear buffer */
	memset(SIM_Buff, '\0', 400);
  HAL_Delay(500);

  /* Connecting to GPRS */
  printf("\nGPRS Connecting..\n\r");
  while (SIM_sendATcommand("AT^SISO=1\r\n", "OK", 10000) == 0)   // open service
  {
    printf("\nGPRS Not ready...\n\r");
    HAL_Delay(100);         
		SIM_sendATcommand("AT^SISC=1\r\n", "OK", 200);  // close service if fail to open
    return 0;
  }
  HAL_Delay(1000);
	SIM_sendATcommand("AT^SISR=1,500\r\n", "Data-ACK", 1000);
	HAL_Delay(500);
	time_out = 1000;
  while (strstr(SIM_Buff, "Data-ACK") == NULL)  //HTTP/1.1 200 OK
  {
		SIM_sendATcommand("AT^SISR=1,500\r\n", "Data-ACK", 1000);
    HAL_Delay(1);
    time_out--;
    if (!time_out) return 0;
  }
	
	//printf("\r\nBuffer: \r\n<%s>\r\n", SIM_Buff);
	HAL_Delay(500);
	
	/* clear buffer */
	memset(SIM_Buff, '\0', 400);

	SIM_sendATcommand("AT^SISC=1\r\n", "OK", 200);	//Close Service 
	printf("\nHTTP request succeed, closing connection!\n\r");
	HAL_Delay(500);
  return 1;
}

/************************* End of File ****************************************/

