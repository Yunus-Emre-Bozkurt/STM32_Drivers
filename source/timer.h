/*
 * timer.h
 *
 *  Created on: Feb 1, 2024
 *      Author: Agrica
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "integration.h"

#define NOFTIMER	16	// Useable timer limit

// Typedef's

/**
  * @brief  Timer features definition
  */
//!#pragma pack(push, 1)
typedef struct
{
	uint32_t 			InitialValue;
	uint32_t 			counterUpperLimit;
	bool				resultFlag;
	bool 				controlFlag;
}__attribute__((packed)) timerControl_t;
//!#pragma pack(pop)

//	Function Prototypes
void timerAppInit(void);
void startTimer(uint8_t , uint32_t );
void controlTimer(void);
bool getTimerResultStatus(uint8_t );




#endif /* TIMER_H_ */
