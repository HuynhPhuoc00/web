/*
 * USART.c
 *
 *  Created on: Jul 17, 2023
 *      Author: Huynh Phuoc
 */
#include"USART.h"

static void Config_GPIO_USART();
static uint8_t USART_GetFlagStatus(USART_RegDef_t *pUARTx,uint32_t FlagName);
// Enable GPIO for I2C
static void Config_GPIO_USART(){
	GPIOA_PCLK_EN;
	GPIO_Handle_t TX_RX;	// PA2, PA3
	TX_RX.pGPIOx = GPIOA;
	TX_RX.GPIO_Pin_Config.GPIO_PinNumber = PIN_NUM_2 | PIN_NUM_3;
	TX_RX.GPIO_Pin_Config.GPIO_PinMode = GPIO_MODER_ALTFM;
	TX_RX.GPIO_Pin_Config.GPIO_PinOPType = GPIO_OTYPER_PP;
	TX_RX.GPIO_Pin_Config.GPIO_PinSpeed = GPIO_OSPEEDR_HIGH;
	TX_RX.GPIO_Pin_Config.GPIO_PinPuPdControl = GPIO_PUPDR_NOPUPD;
	TX_RX.GPIO_Pin_Config.GPIO_PinAltFunMode_Low = GPIO_AFRL_AF7;
	GPIO_Init(&TX_RX);
}

void USART_Init(USART_Handle_t *pUSARTHandle)
{
	//Config GPIO
	Config_GPIO_USART();
	// Enable USART
	USART2_PLCK_EN;

	// Enable USART (TE, RE, UE)
	pUSARTHandle->pUSARTx->CR1 = 0x00;
	pUSARTHandle->pUSARTx->CR1 |= (1<<13);

	pUSARTHandle->pUSARTx->CR1 |= (1<<2);
	pUSARTHandle->pUSARTx->CR1 |= (1<<3);

	//pUSARTHandle->pUSARTx->CR1 |= (M<<12);  // M =0; 8 bit word length

	// Set Baud rate
	uint32_t pclk1 = RCC_GetPCLK1Value();

	if (pUSARTHandle->USART_Config.USART_Baud > 0){
	    uint8_t over8 = (pUSARTHandle->pUSARTx->CR1 >> 15) & 0x1;
	    uint8_t div = over8 ? 8 : 16;

	    double usartdiv = (double)pclk1 / (div * pUSARTHandle->USART_Config.USART_Baud);
	    uint32_t mantissa = (uint32_t)usartdiv;
	    uint32_t fraction = (uint32_t)((usartdiv - mantissa) * ((over8) ? 8 : 16));

	    pUSARTHandle->pUSARTx->BRR = (mantissa << 4) | (fraction & 0xF);
	}
}

void USART_SendChar(USART_RegDef_t *pUARTx, uint8_t data){
	while(!(USART_GetFlagStatus(pUARTx, USART_FLAG_TxE)));
	pUARTx->DR = data;
	while(!(USART_GetFlagStatus(pUARTx, USART_FLAG_TC)));
}

void UART_SendString(USART_RegDef_t *pUARTx, const char *str){
	while(*str){
		USART_SendChar(pUARTx, *str++);
	}
}

void UART_SendInt(USART_RegDef_t *pUARTx, uint32_t num) {
    unsigned char buffer[12];
    sprintf(buffer, "%d", num);
    UART_SendString(pUARTx, buffer);
    UART_SendString(pUARTx, "\r\n");
}


uint8_t UART_ReceiveChar(USART_RegDef_t *pUARTx){
	while(!(USART_GetFlagStatus(pUARTx, USART_FLAG_RXNE)));
	return (uint8_t)pUARTx->DR;
}

static uint8_t USART_GetFlagStatus(USART_RegDef_t *pUARTx,uint32_t FlagName){
    if(pUARTx->SR & FlagName){
        return Flag_Set;
    }
    return Flag_Reset;
}
