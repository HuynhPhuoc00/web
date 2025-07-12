/*
 * dht11.c
 *
 *  Created on: Jun 25, 2025
 *      Author: Administrator
 */

#include "dht11.h"

GPIO_Handle_t DHT11_Pin;

static void IO_Write(uint8_t RoW);
static void IO_Write(uint8_t RoW){
	GPIOE_PCLK_EN;
	DHT11_Pin.pGPIOx = GPIOE;
	DHT11_Pin.GPIO_Pin_Config.GPIO_PinNumber = GPIO_PIN_NUM_9;
	DHT11_Pin.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_OSPEEDR_LOW;
	DHT11_Pin.GPIO_Pin_Config.GPIO_PinOPType = GPIO_OTYPER_PP;
	DHT11_Pin.GPIO_Pin_Config.GPIO_PinPuPdControl = GPIO_PUPDR_PU;

	if (RoW == Read){
		DHT11_Pin.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODER_INPUT;
	}else{
		DHT11_Pin.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODER_OUTPUT;
	}
	GPIO_Init_Pin(&DHT11_Pin);
}

uint8_t start_dht(void){
	IO_Write(Write);

	// MCU Sends out Start Signal to DHT
	GPIO_WriteToOutPutPin(DHT11_Pin.pGPIOx, 9, Low);
	delay_ms(20);
	GPIO_WriteToOutPutPin(DHT11_Pin.pGPIOx, 9, High);

	IO_Write(Read);

	return CheckResponse();
}

uint8_t CheckResponse(){
	//Check response
	delay_us(40);

	if (!(GPIO_ReadFromInputPin(DHT11_Pin.pGPIOx, 9))){	// Check DHT pin low
		delay_us(80);
		if (!GPIO_ReadFromInputPin(DHT11_Pin.pGPIOx, 9)){	// Check DHT pin high
			return -1;
		}
		while (GPIO_ReadFromInputPin(DHT11_Pin.pGPIOx, 9));	// Wait DHT pin low
	}
	else{
		return -1;
	}
	return 1;
}

uint8_t Read_DHT(){
	uint8_t Data[5];
	uint64_t tmp = 0;

	for (int i = 0; i < 40; i++){
		while (!(GPIO_ReadFromInputPin(DHT11_Pin.pGPIOx, 9)));
		delay_us(30);
		if (GPIO_ReadFromInputPin(DHT11_Pin.pGPIOx, 9)){	// data is 1
			tmp = (tmp << 1) | 0x1;
		}
		else{	// data is 0
			tmp = (tmp << 1) | 0x0;
		}
		while (GPIO_ReadFromInputPin(DHT11_Pin.pGPIOx, 9));
	}

	Data[0] = (tmp >> 32)	& 0xFF;	// Int RH
	Data[1] = (tmp >> 24)	& 0xFF;	// Dec RH
	Data[2] = (tmp >> 16)	& 0xFF;	// Int T
	Data[3] = (tmp >> 8)	& 0xFF;	// Dec T
	Data[4] = tmp			& 0xFF;	// Checksum
	(void)tmp;
	CheckSum(&Data);

	UART_SendInt(USART2, Data[0]);
	UART_SendInt(USART2, Data[1]);
	UART_SendInt(USART2, Data[2]);
	UART_SendInt(USART2, Data[3]);
	UART_SendInt(USART2, Data[4]);

	//End
	while(!GPIO_ReadFromInputPin(DHT11_Pin.pGPIOx, 9));

	return 1;
}

uint8_t CheckSum(uint8_t *data){
	uint32_t Sum = 0;
	for(int i = 0; i < 4; i++){
		Sum += data[i];
	}
	if (Sum != data[4]){UART_SendString(USART2, "Check response success\r\n");
		return -1;
	}
}
