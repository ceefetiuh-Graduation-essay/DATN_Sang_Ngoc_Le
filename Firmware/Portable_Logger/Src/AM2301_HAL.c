#include "AM2301_HAL.h"

/**
 * @brief  Set pin as input
 * @param  
 * @retval 
 */
void AM2301_PIN_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = AM2301_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT ;
  HAL_GPIO_Init(AM2301_PORT, &GPIO_InitStruct);  
}

/**
 * @brief  Set pin as output
 * @param  
 * @retval 
 */
void AM2301_PIN_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = AM2301_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(AM2301_PORT, &GPIO_InitStruct);
}

/**
 * @brief  Reads data from sensor
 * @param  *temperature: Pointer to temperature data variable to store data into
		   *humidity: Pointer to humidity data variable to store data into
 * @retval Data valid:
 *            - AM2301_OK: Data valid
 *            - Else: Data not valid
 */
AM2301_Result_t AM2301_Read(int16_t *temperature, uint16_t *humidity)
{
	volatile uint32_t time, check_time_wait_high = 0, check_time_high_0 = 0, check_time_high_1 = 0, check_time_high_3 = 0;
  uint8_t data_buffer[5], i, j;  
	
	/* Pin output */
	AM2301_PIN_OUT();
	/* Set pin low for ~800-1000 us */
	AM2301_PIN_LOW();
	//DWT_Delay_us(900);
	DWT_Delay_us(1000);
	/* Set pin high to ~30 us */
	AM2301_PIN_HIGH();
	DWT_Delay_us(30);
	
	/* Read mode */
	AM2301_PIN_IN();
	
	time = 0;
	/* Wait 20us for acknowledge, low signal */
	while (AM2301_PIN_READ()) 
	{
		if (time > 20) 
		{
			return AM2301_Result_CONNECTION_ERROR;
		}
		/* Increase time */
		time++;
		/* Wait 1 us */
		DWT_Delay_us(1);
	}
	
	time = 0;
	/* Wait high signal, about 80-85us long (measured with logic analyzer) */
	while (!AM2301_PIN_READ()) 
	{
		if (time > 85) 
		{
			return AM2301_Result_WAITHIGH_ERROR;
		}
		/* Increase time */
		time++;
		/* Wait 1 us */
		DWT_Delay_us(1);
	}
	
	time = 0;
	/* Wait low signal, about 80-85us long (measured with logic analyzer) */
	while (AM2301_PIN_READ()) 
	{
		if (time > 85) 
		{
			return AM2301_Result_WAITLOW_ERROR;
		}
		/* Increase time */
		time++;
		/* Wait 1 us */
		DWT_Delay_us(1);
	}
	
	/* Read 5 bytes */
	for (j = 0; j < 5; j++) 
	{
		data_buffer[j] = 0;
		for (i = 8; i > 0; i--) 
		{
			/* We are in low signal now, wait for high signal and measure time */
			time = 0;
			/* Wait high signal, about 57-63us long (measured with logic analyzer) */
			while (AM2301_PIN_READ() == 0) 
			{
				if (time > 75) 
				{
					return AM2301_Result_WAITHIGH_LOOP_ERROR;
				}
				/* Increase time */
				time++;
				/* Wait 1 us */
				DWT_Delay_us(1);
			}
			check_time_wait_high = time;
			
			/* High signal detected, start measure high signal, it can be 26us for 0 or 70us for 1 */
			time = 0;
			/* Wait low signal, between 26 and 70us long (measured with logic analyzer) */
			while (AM2301_PIN_READ() == 1) 
			{
				if (time > 90) 
				{
					return AM2301_Result_WAITLOW_LOOP_ERROR;
				}
				/* Increase time */
				time++;
				/* Wait 1 us */
				DWT_Delay_us(1);
			}
			check_time_high_3 = time;
			if (time > 2 && time < 10) //if (time > 10 && time < 40) 
			{
				/* read 0 */
				check_time_high_0 = time;
			} 
			else //if (time > 10)
			{
				/* read 1 */
				check_time_high_1 = time;
				data_buffer[j] |= 1 << (i - 1);
			}
		}
	}
	//printf("\r\n Time check: %d, %d, %d, %d", check_time_wait_high, check_time_high_0, check_time_high_1, check_time_high_3);
	/* Check for parity */
	if (((data_buffer[0] + data_buffer[1] + data_buffer[2] + data_buffer[3]) & 0xFF) != data_buffer[4]) 
	{
		/* Parity error, data not valid */
		//DEBUG
		//printf("\r\n Data frame: %#x %#x %#x %#x %#x\r\n", data_buffer[0], data_buffer[1], data_buffer[2], data_buffer[3], data_buffer[4]);
		//printf("\r\n Parity: %d, %d", ((data_buffer[0] + data_buffer[1] + data_buffer[2] + data_buffer[3]) & 0xFF), data_buffer[4]);
	
		
		/* Set humidity */
		*humidity = data_buffer[0] << 8 | data_buffer[1];
		/* Negative temperature */
		if (data_buffer[2] & 0x80) 
		{
			*temperature = -((data_buffer[2] & 0x7F) << 8 | data_buffer[3]);
		} 
		else 
		{
			*temperature = (data_buffer[2]) << 8 | data_buffer[3];
		}
		
		//printf("\r\nData: %d, %d", *temperature, *humidity); 
	
		return AM2301_Result_PARITY_ERROR;
		
	}
	

	/* Set humidity */
	*humidity = data_buffer[0] << 8 | data_buffer[1];
	/* Negative temperature */
	if (data_buffer[2] & 0x80) 
	{
		*temperature = -((data_buffer[2] & 0x7F) << 8 | data_buffer[3]);
	} 
	else 
	{
		*temperature = (data_buffer[2]) << 8 | data_buffer[3];
	}
	
	//printf("\r\n Data frame: %#x %#x %#x %#x %#x\r\n", data_buffer[0], data_buffer[1], data_buffer[2], data_buffer[3], data_buffer[4]);
	//printf("\r\n Parity: %d, %d\r\n", ((data_buffer[0] + data_buffer[1] + data_buffer[2] + data_buffer[3]) & 0xFF), data_buffer[4]);
	/* Data OK */
	return AM2301_Result_Ok;
}