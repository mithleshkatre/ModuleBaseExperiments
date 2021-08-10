/*
 * DHT11.c
 *
 *  Created on: 09-Aug-2021
 *      Author: katre
 */



#include "DHT11.h"

extern TIM_HandleTypeDef htim3;

#define DHT_Port GPIOA
#define DHP_Pin GPIO_PIN_0;

void usdelay(uint32_t us){
	//__HAL_TIM_SET_COUNTER(htim3,0);
	//while(__HAL_TIM_GET_COUNTER(htim3)< us);
}


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void setPinInput(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

}


void setPinOutput(GPIO_TypeDef *GPIOx, uint16_t GPIO_pin)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

}


/* USER CODE BEGIN 4 */


void DHT11Start(){

	setPinOutput(GPIOA, GPIO_PIN_0);
	HAL_GPIO_WritePin(DHT_Port, GPIO_PIN_0, 0);
	usdelay(18000);  //18 us delay
	HAL_GPIO_WritePin(DHT_Port, GPIO_PIN_0, 1);
	usdelay(20);
	setPinInput(GPIOA, GPIO_PIN_0);

}

uint8_t DHTResponse(){
	uint8_t response=0;
	usdelay(100);
	if(!(HAL_GPIO_ReadPin(DHT_Port, GPIO_PIN_0))){
		usdelay(80);
		if(HAL_GPIO_ReadPin(DHT_Port, GPIO_PIN_0)){
			response =1;
		}
		else{
			response =-1; //255
		}
	}
	while(HAL_GPIO_ReadPin(DHT_Port, GPIO_PIN_0));

	return response;

}

uint8_t DHTRead(){

	uint8_t i,j;
	for(i=0;i<8;i++){
		while(!(HAL_GPIO_ReadPin(DHT_Port, GPIO_PIN_0)));
		usdelay(50);
		if(!(HAL_GPIO_ReadPin(DHT_Port, GPIO_PIN_0))){
			j=~(1<<(7-j));  //write 0
		}
		else{
			j=(1<<(7-j));
		}
		while(HAL_GPIO_ReadPin(DHT_Port, GPIO_PIN_0));
	}
	return j;

}
