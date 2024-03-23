/*
 * i2c_app.h
 *
 *  Created on: Feb 18, 2024
 *      Author: Agrica
 */

#ifndef I2C_APP_H_
#define I2C_APP_H_

#ifdef __I2C_H__
#include "i2c.h"
#endif

#include "integration.h"

#define I2C_TIMEOUT		100 	//100 ms polling timeout for whole functions


//	Function Prototypes
int32_t i2cMasterTransmitPoll(void *, uint16_t , uint8_t *, uint16_t );
int32_t i2cMasterReceivePoll(void * ,uint16_t  ,uint8_t *,uint16_t );
int32_t i2cMemWritePoll(void *, uint16_t , uint16_t , uint16_t , uint8_t *, uint16_t );
int32_t i2cMemReadPoll(void *, uint16_t , uint16_t , uint16_t , uint8_t *, uint16_t );
bool i2cIsDeviceReady(void *, uint16_t , uint32_t );

#endif /* I2C_APP_H_ */
