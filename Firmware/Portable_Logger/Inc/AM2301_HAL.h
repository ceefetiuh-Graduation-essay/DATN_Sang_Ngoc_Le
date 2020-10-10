/**
 * @author  Sang Le
 * @version v1.0
 * @ide     Keil uVision
 * @brief   HAL library for AM2301 (DHT21) temperature and humidity sensor
 *	
*/


//#ifndef TM_AM2301_H
#define TM_AM2301_H 100

#include "stm32l1xx_hal.h"
#include "gpio.h"
#include "dwt_stm32_delay.h"

/**
 * @brief  Default data pin, overwrite it in defines.h file 
 */
//#ifndef AM2301_PIN

#define AM2301_PORT				TEMP_GPIO_Port
#define AM2301_PIN				TEMP_Pin

//#endif

#define AM2301_PIN_LOW()    HAL_GPIO_WritePin(AM2301_PORT, AM2301_PIN, GPIO_PIN_RESET) 
#define AM2301_PIN_HIGH()    HAL_GPIO_WritePin(AM2301_PORT, AM2301_PIN, GPIO_PIN_SET)
#define AM2301_PIN_READ()    HAL_GPIO_ReadPin(AM2301_PORT, AM2301_PIN)
/**
 * Enumerations
 *
 * There are several different possible results.
 * If AM2301_OK is returned from read function then you have valid data.
 */
typedef enum {
	AM2301_Result_Ok = 0x00,           /*!< Everything OK */
	AM2301_Result_Error,               /*!< An error occurred */
	AM2301_Result_CONNECTION_ERROR,    /*!< Device is not connected */
	AM2301_Result_WAITHIGH_ERROR,      /*!< Wait high pulse timeout */
	AM2301_Result_WAITLOW_ERROR,       /*!< Wait low pulse timeout */
	AM2301_Result_WAITHIGH_LOOP_ERROR, /*!< Loop error for high pulse */
 	AM2301_Result_WAITLOW_LOOP_ERROR,  /*!< Loop error for low pulse */
	AM2301_Result_PARITY_ERROR         /*!< Data read fail */
} AM2301_Result_t;

/**
 * @brief  Set pin as input
 * @param  
 * @retval 
 */
void AM2301_PIN_IN(void);

/**
 * @brief  Set pin as output
 * @param  
 * @retval 
 */
void AM2301_PIN_OUT(void);

/**
 * @brief  Reads data from sensor
 * @param  *temperature: Pointer to temperature data variable to store data into
					 *humidity: Pointer to humidity data variable to store data into
 * @retval Data valid:
 *            - AM2301_OK: Data valid
 *            - Else: Data not valid
 */
AM2301_Result_t AM2301_Read(int16_t *temperature, uint16_t *humidity);