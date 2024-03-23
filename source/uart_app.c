/*
 * uart_app.c
 *
 *  Created on: Jan 30, 2024
 *      Author: Agrica
 */
#include "uart_app.h"


/*	uartSendDMA
 *
 * Brief: Herhangi bir uart için Transfer Complete Flag'ı kontrol edilerek DMA ile transmit sağlanır.
 *
 * Param1: Generated typedef olan void * tipinde UART peripheral structure adresi
 * Param2: Gönderilmek istenen data adresi
 * Param3: Gönderilmek istenen data uzunluğu HINT--sizeof() fonksiyonu kullanılması önerilir.
 *
 * Return: ret 0 : SUCCESS
 * 		   ret 1 : FAIL
 *
 * NOTE: huart->Instance->SR kontrolü her STM32 ürünü için geçerli değildir.
 * 		 farklı bir işlemciye geçilmesi durumunda sadece HAL_UART_Transmit_DMA() fonksiyonu kullanılmalıdır.
 */
uint8_t uartSendDMA(void *handle, const uint8_t *bufferPtr, uint8_t size)
{
	int32_t ret = 0;

	UART_HandleTypeDef *huart = (void *)handle;	//Cast void pointer to UART_HandleTypeDef type. Void pointer used for generic driver purposes

	//Check whether transmission complete or not
	if(__HAL_UART_GET_FLAG(huart,UART_FLAG_TC))
	{
		//if transmission completed, clear transmission complete flag (TC)
		__HAL_UART_CLEAR_FLAG(huart,UART_FLAG_TC);
		//To send new data configure the transmission state	--Mandatory!
		huart->gState = HAL_UART_STATE_READY;

		if(HAL_OK == HAL_UART_Transmit_DMA(handle, bufferPtr, size))	//Transmit new data
		{
			ret = 0;
		}
		else
		{
			ret = 1;
		}
	}

	//	//!UART'ın Transfer Complete Flag'ı kontrol edilir eğer iletim tamamlanmış ise yeni mesaj gönderilir.
	//	if((huart->Instance->SR) & (1<<6))
	//	{
	//		huart->Instance->SR &= (0<<6);	//Clear TC flag
	//		huart->gState = HAL_UART_STATE_READY;
	//
	//		if(HAL_OK == HAL_UART_Transmit_DMA(handle, bufferPtr, size))	//Transmit esnasında hata kontrolü yapılır
	//		{
	//			ret = 0;
	//		}
	//		else
	//		{
	//			ret = 1;
	//		}
	//	}

	return ret;
}
/*********************************************************************************************/

/*	uartReceiveDMA
 *
 * Brief: Herhangi bir uart için Receive Complete Flag'ı kontrol edilerek DMA ile receive sağlanır.
 *
 * Param1: Generated typedef olan void * tipinde UART peripheral structure adresi
 * Param2: Alınan verileri kaydetmek istenen adres
 * Param3: Alınmak istenen data uzunluğu HINT--sizeof() fonksiyonu kullanılması önerilir.
 *
 * Return: ret 0 : SUCCESS
 * 		   ret 1 : FAIL
 *
 * NOTE: huart->Instance->SR kontrolü her STM32 ürünü için geçerli değildir.
 * 		farklı bir işlemciye geçilmesi durumunda sadece HAL_UART_Transmit_DMA() fonksiyonu kullanılmalıdır.
 *
 * NOTE2: huart->Instance->SR koşulunda veri tam zamanında alınamadığı testlerde görülmüştür.
 * 		sadece HAL_UART_Receive_DMA() fonksiyonu kullanılması düşünülebilir.
 */
uint8_t uartReceiveDMA(void *handle, uint8_t *bufferPtr, uint8_t size)
{
	//	if ((huart->Instance->SR) & (1<<5)) //! UART'ın Receive Complete Flag'ı kontrol edilir eğer alım tamamlanmış ise  mesaj okunur.
	//	{
	//		//! Data Ready to read. Receive Complete Flag
	//		//! Read Received data from UART Data Register(DR)
	//		HAL_UART_Receive_DMA(huart, bufferPtr, size);
	//	}

	//UART_HandleTypeDef *huart = (void *)handle;	//generic tasarlanan handle gerekli olan handle tipine cast edilir.
	int32_t ret = 0;

		if(HAL_OK == HAL_UART_Receive_DMA(handle, bufferPtr, size))
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

