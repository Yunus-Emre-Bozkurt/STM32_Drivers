/*
 * i2c_app.c
 *
 *  Created on: Feb 18, 2024
 *      Author: Agrica
 */

#include "i2c_app.h"



/**
  * @brief  Transmits in master mode an amount of data in blocking mode.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval ret 0 : SUCCESS
  * 		ret 1 : FAIL
  */
int32_t i2cMasterTransmitPoll(void *handle, uint16_t deviceAddress, uint8_t *txBuffer, uint16_t size)
{
	/*
	 * NOTE: I2C_HandleTypeDef structure bu fonksiyon içinde kullanılması gerekse idi
	 * Aşağıdaki type casting işlemi yapılmalı idi. Başka fonksiyona gönderdiğimiz için gerekli olmadı.
	 *
	 * //I2C_HandleTypeDef *tempHandle = (I2C_HandleTypeDef *)handle;
	 */
	int32_t ret = 0;

	if(HAL_OK == HAL_I2C_Master_Transmit(handle, deviceAddress, txBuffer, size, I2C_TIMEOUT))
	{
		ret = 0;
	}
	else
	{
		ret = 1;
	}
	return ret;
}
/*********************************************************************************************/

/**
  * @brief  Receives in master mode an amount of data in blocking mode.
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval ret 0 : SUCCESS
  *			ret 1 : FAIL
  */
int32_t i2cMasterReceivePoll(void *handle ,uint16_t deviceAddress ,uint8_t *rxBuffer,uint16_t size)
{
	int32_t ret = 0;

	if(HAL_OK == HAL_I2C_Master_Receive(handle, deviceAddress, rxBuffer, size, I2C_TIMEOUT))
	{
		ret = 0;
	}
	else
	{
		ret = 1;
	}
	return ret;
}
/*********************************************************************************************/

/**
  * @brief  Write an amount of data in blocking mode to a specific memory address
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  MemAddress Internal memory address
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval ret 0 : SUCCESS
  *			ret 1 : FAIL
  */
int32_t i2cMemWritePoll(void *handle, uint16_t deviceAddress, uint16_t memAddress, uint16_t memAddSize, uint8_t *pData, uint16_t size)
{
	int32_t ret = 0;

	if(HAL_OK == HAL_I2C_Mem_Write(handle, deviceAddress, memAddress, memAddSize, pData, size, I2C_TIMEOUT))
	{
		ret = 0;
	}
	else
	{
		ret = 1;
	}
	return ret;
}
/*********************************************************************************************/

/**
  * @brief  Read an amount of data in blocking mode from a specific memory address
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  MemAddress Internal memory address
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @retval ret 0 : SUCCESS
  *			ret 1 : FAIL
  */
int32_t i2cMemReadPoll(void *handle, uint16_t deviceAddress, uint16_t memAddress, uint16_t memAddSize, uint8_t *pData, uint16_t size)
{
	int32_t ret = 0;

	if(HAL_OK == HAL_I2C_Mem_Read(handle, deviceAddress, memAddress, memAddSize, pData, size, I2C_TIMEOUT))
	{
		ret = 0;
	}
	else
	{
		ret = 1;
	}
	return ret;
}
/*********************************************************************************************/

/**
  * @brief  Checks if target device is ready for communication.
  * @note   This function is used with Memory devices
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  Trials Number of trials
  * @retval TRUE 	=> Device Ready
  * 		FALSE	=> Device Not Ready
  */
bool i2cIsDeviceReady(void *handle, uint16_t deviceAddress, uint32_t trials)
{
	bool ret = false;

	//I2C_HandleTypeDef *tempHandle = (I2C_HandleTypeDef *)handle;

	if(HAL_OK == HAL_I2C_IsDeviceReady(handle, deviceAddress, trials, I2C_TIMEOUT))
	{
		ret = true;
	}
	else
	{
		ret = false;
	}

	return ret;
}
/*********************************************************************************************/


