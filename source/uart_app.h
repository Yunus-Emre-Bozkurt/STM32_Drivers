/*
 * uart_app.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Agrica
 */

#ifndef UART_APP_H_
#define UART_APP_H_

#include "integration.h"

#ifdef __USART_H__
#include "usart.h"
#endif



uint8_t uartSendDMA(void *, const uint8_t *, uint8_t);
uint8_t uartReceiveDMA(void *, uint8_t *, uint8_t);

#endif /* UART_APP_H_ */
