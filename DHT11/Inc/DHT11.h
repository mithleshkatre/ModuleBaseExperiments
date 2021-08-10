/*
 * DHT11.h
 *
 *  Created on: 09-Aug-2021
 *      Author: katre
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "stm32f4xx.h"

#include  "stm32f4xx_hal_tim.h"

void setPinInput(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin);
void setPinOutput(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin);
void DHT11Start();

uint8_t DHTResponse();
uint8_t DHTRead();

#endif /* INC_DHT11_H_ */
