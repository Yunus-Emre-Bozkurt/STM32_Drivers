/*
 * timer.c
 *
 *  Created on: Feb 1, 2024
 *      Author: Agrica
 */

#include "timer.h"

//Private Function Prototypes
static void systickinit(void);
static void disableSystickInterrupt(void);
static void enableSystickInterrupt(void);
static uint32_t getSystickCount(void);

//Variables
timerControl_t timerControlArr[NOFTIMER] = {};

/*	startTimer
 *
 * Brief: Initialize the systick module with core clock config clock frequency
 *
 * Return: NONE
 *
 */
void timerAppInit(void)
{
	systickinit();
}

/*	startTimer
 *
 * Brief: İstenilen 'ms' değerinde timer başlatır
 *
 * Param1: NOFTIMER'a kadar olan index değerini seçer.
 * Param2: Kurulan timer'ın sayaç üst limit değeridir.
 *
 * Return: NONE
 *
 * NOTE: startTimer() fonksiyonu her çağırıldığında ilgili index'in Initial değerini günceller.
 * 		Fonksiyon döngü içerisinde sürekli kullanılırsa Initial değer sürekli güncelleneceği için
 * 		üstLimite hiçbir zaman ulaşılamayacaktır.
 */
void startTimer(uint8_t index, uint32_t upperLimit)
{
	timerControlArr[index].InitialValue = getSystickCount();
	timerControlArr[index].controlFlag = true;
	timerControlArr[index].resultFlag = false;
	timerControlArr[index].counterUpperLimit = upperLimit;
}
/*********************************************************************************************/

/*	controlTimer
 *
 * Brief: Kurulan timerların üst limite ulaşıp ulaşmadığını kontrol eder. Üst Limite ulaşan Timer varsa
 * 		kontrolünü sonlandırır ve result flag'ını HIGH ayarlar.
 *
 * Return: NONE
 */
void controlTimer(void)
{
	uint32_t elapsedTime = 0;

	for(int i = 0; i<NOFTIMER; i++)
	{
		if(timerControlArr[i].controlFlag == true)		//kontrol flag'a bakılır
		{
			elapsedTime = (getSystickCount() - timerControlArr[i].InitialValue);
			if(timerControlArr[i].counterUpperLimit <= elapsedTime)		//istenen süre dolmuşsa
			{
				timerControlArr[i].resultFlag = true;		//Süre dolma flag'ı set edilir.
				timerControlArr[i].controlFlag = false;		//Tekrar kontrol edilmemesi için kontrol flag'ı false çekilir
			}
		}
	}
}
/*********************************************************************************************/

/*	getTimerResultStatus
 *
 * Brief: Timer'ın dolma durumunu kontrol eder
 *
 * Param1: Sonucu öğrenilmek istenen timer index'i
 *
 * Return: sayacın dolma durumunu 'bool' tipinde döndürür
 * 		TRUE 	=> Timer Dolmuştur
 * 		FALSE	=> Timer Dolmamıştır
 */
bool getTimerResultStatus(uint8_t index)
{
	bool res = false;

	if(timerControlArr[index].resultFlag == true)
	{
		res = true;
	}
	else
	{
		res = false;
	}

	return res;
}


/** !!!!!!!!!!!!!!!!!!!!!!!!!
 * 		IMPORTANT NOTE
 *  !!!!!!!!!!!!!!!!!!!!!!!!!
 *
 * If you want to use configSystickTimer() function, You have to declare into your application main.c file "void SysTick_Handler (void)"
 * function to increment tick value in ISR callback function !!
 *
 * If void SysTick_Handler (void) predefined by IDE, disable the generated function and write own function
 * with same name.
 */

/*
 * @note Check Example Application as HAL_Delay() function
 *
 * */

/**
  * @brief Initiliaze the SysTick Timer with 1 ms time base. Interrupt priority setting '0'
  * @note  Initiliazing step done automatically while setting up HAL_INIT and SystemClockConfig phase
  *
  * @retval None
  */
void systickinit(void)
{
	HAL_InitTick(0);
}
/*********************************************************************************************/

/**
  * @brief Suspend Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once disableSystickInterrupt()
  *       is called, the SysTick interrupt will be disabled and so Tick increment
  *       is suspended.
  * @retval None
  */
void disableSystickInterrupt(void)
{
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}
/*********************************************************************************************/

/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once enableSystickInterrupt()
  *       is called, the SysTick interrupt will be enabled and so Tick increment
  *       is resumed.
  * @retval None
  */
void enableSystickInterrupt(void)
{
	SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk;
}
/*********************************************************************************************/

/**
  * @brief Provides a tick value in millisecond.
  *
  * @retval tick value
  */
uint32_t getSystickCount(void)
{
	return HAL_GetTick();
}
/*********************************************************************************************/


