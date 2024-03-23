/*
 * integration.h
 *
 *  Created on: Mar 21, 2024
 *      Author: Agrica
 */

#ifndef INTEGRATION_H_
#define INTEGRATION_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"

#include "uart_app.h"
#include "timer.h"
#include "i2c_app.h"

// Param1: variable to be bit checked --- Param2:Index to be bit tested --- Return Value 0 if selected bit is '0', Return Value 1 if selected bit is '1'
#define BIT_VALUE(X, N) (((X)>>(N)) & 0x1)

#ifndef SET_BIT
// Param1: variable to be bit set --- Param2:Index to be bit set
#define SET_BIT(X,N) X |= (0x01 << N)
#endif

// Param1: variable to be bit clear--- Param2:Index to be bit clear
#define CLR_BIT(X,N) X &= ~(0x01 << N)


#endif /* INTEGRATION_H_ */
