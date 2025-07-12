/*
 * dht11.h
 *
 *  Created on: Jun 25, 2025
 *      Author: Administrator
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f411.h"


uint8_t start_dht();
uint8_t CheckResponse();
uint8_t Read_DHT();
uint8_t CheckSum();

#ifdef __cplusplus
}
#endif

#endif /* INC_DHT11_H_ */
