/*
 * USART.h
 *
 *  Created on: Jul 17, 2023
 *      Author: Huynh Phuoc
 */

#ifndef INC_USART_H_
#define INC_USART_H_

#include "stm32f411.h"
#include<stdint.h>

#define USART2_BASE_ADDR		0x40004400U

typedef struct
{
	uint8_t USART_Mode;
	uint32_t USART_Baud;
	uint8_t USART_NoOfStopBits;
	uint8_t USART_WordLength;
	uint8_t USART_ParityControl;
	uint8_t USART_HWFlowControl;
}USART_Config_t;

/*
 * Handle structure for USARTx peripheral
 */
typedef struct{
	vo uint32_t SR;
	vo uint32_t DR;
	vo uint32_t BRR;
	vo uint32_t CR1;
	vo uint32_t CR2;
	vo uint32_t CR3;
	vo uint32_t GTPR;
}USART_RegDef_t;

#define USART2		(USART_RegDef_t*)USART2_BASE_ADDR

/*
 * Handle structure for USARTx peripheral
 */
typedef struct
{
	USART_RegDef_t *pUSARTx;
	USART_Config_t   USART_Config;
}USART_Handle_t;

/*
 *@USART_Mode
 *Possible options for USART_Mode
 */
#define USART_MODE_ONLY_TX 0
#define USART_MODE_ONLY_RX 1
#define USART_MODE_TXRX  2

/*
 *@USART_Baud
 *Possible options for USART_Baud
 */
#define USART_STD_BAUD_1200					1200
#define USART_STD_BAUD_2400					400
#define USART_STD_BAUD_9600					9600
#define USART_STD_BAUD_19200 				19200
#define USART_STD_BAUD_38400 				38400
#define USART_STD_BAUD_57600 				57600
#define USART_STD_BAUD_115200 				115200
#define USART_STD_BAUD_230400 				230400
#define USART_STD_BAUD_460800 				460800
#define USART_STD_BAUD_921600 				921600
#define USART_STD_BAUD_2M 					2000000
#define SUART_STD_BAUD_3M 					3000000


/*
 *@USART_ParityControl
 *Possible options for USART_ParityControl
 */
#define USART_PARITY_EN_ODD   2
#define USART_PARITY_EN_EVEN  1
#define USART_PARITY_DISABLE   0

/*
 *@USART_WordLength
 *Possible options for USART_WordLength
 */
#define USART_WORDLEN_8BITS  0
#define USART_WORDLEN_9BITS  1

/*
 *@USART_NoOfStopBits
 *Possible options for USART_NoOfStopBits
 */
#define USART_STOPBITS_1     0
#define USART_STOPBITS_0_5   1
#define USART_STOPBITS_2     2
#define USART_STOPBITS_1_5   3

/*
 *@USART_HWFlowControl
 *Possible options for USART_HWFlowControl
 */
#define USART_HW_FLOW_CTRL_NONE    	0
#define USART_HW_FLOW_CTRL_CTS    	1
#define USART_HW_FLOW_CTRL_RTS    	2
#define USART_HW_FLOW_CTRL_CTS_RTS	3

// Define flag
#define USART_SR_RXNE        5
#define USART_SR_TC          6
#define USART_SR_TxE         7
#define USART_FLAG_RXNE       (1 << USART_SR_RXNE)
#define USART_FLAG_TC         (1 << USART_SR_TC)
#define USART_FLAG_TxE        (1 << USART_SR_TxE)

/******************************************************************************************
 *								APIs supported by this driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/
/*
 * Peripheral Clock setup
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);

/*
 * Init and De-init
 */
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(void);


// Send and Receive
void USART_SendChar(USART_RegDef_t *pUARTx, uint8_t data);
void UART_SendString(USART_RegDef_t *pUARTx, const char *str);
void UART_SendData(USART_RegDef_t *pUARTx, uint8_t *data);
uint8_t UART_ReceiveChar(USART_RegDef_t *pUARTx);
void UART_SendInt(USART_RegDef_t *pUARTx, uint32_t num);

#define USART2_PLCK_EN        (RCC->APB1ENR |= (1<<17))

#endif /* INC_USART_H_ */
