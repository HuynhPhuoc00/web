/*
 * stm32f411_I2C.h
 *
 *  Created on: Jul 6, 2023
 *      Author: HuynhPhuoc
 */


#ifndef INC_STM32F411_I2C_H_
#define INC_STM32F411_I2C_H_

#include "stm32f411.h"
#include "lcd.h"

#define I2C1_BASE_ADD           0x40005400U
#define I2C2_BASE_ADD           0x40005800U
#define I2C3_BASE_ADD           0x40005C00U

// I2C Struct

typedef struct{
    vo uint32_t CR1;
    vo uint32_t CR2;
    vo uint32_t OAR1;
    vo uint32_t OAR2;
    vo uint32_t DR;
    vo uint32_t SR1;
    vo uint32_t SR2;
    vo uint32_t CCR;
    vo uint32_t TRISE;
    vo uint32_t FLTR;
}I2C_RegDef_t;

#define I2C1                ((I2C_RegDef_t*)I2C1_BASE_ADD)
#define I2C2                ((I2C_RegDef_t*)I2C1_BASE_ADD)
#define I2C3                ((I2C_RegDef_t*)I2C1_BASE_ADD)

// Clock En APB1
#define I2C1_PLCK_EN        (RCC->APB1ENR |= (1<<21))
#define I2C2_PLCK_EN        (RCC->APB1ENR |= (1<<22))
#define I2C3_PLCK_EN        (RCC->APB1ENR |= (1<<23))

#define I2C1_PLCK_DIS       (RCC->APB1ENR &= ~(1<<21))
#define I2C2_PLCK_DIS       (RCC->APB1ENR &= ~(1<<22))
#define I2C3_PLCK_DIS       (RCC->APB1ENR &= ~(1<<23))


// Bit position definitions of I2C peripheral

// I2C Control register 1
#define I2C_CR1_PE          1
#define I2C_CR1_NO_STR      7
#define I2C_CR1_START       8
#define I2C_CR1_STOP        9
#define I2C_CR1_ACK         10
#define I2C_CR1_SWRST       15

// I2C Control register 2
#define I2C_CR2_FREQ        0
#define I2C_CR2_ITERREN     8
#define I2C_CR2_ITEVTEN     9
#define I2C_CR2_ITBUFEN     10

// I2C Own address register 1
#define I2C_OAR1_ADD0       0
#define I2C_OAR1_ADD7       1
#define I2C_OAR1_ADD        8
#define I2C_OAR1_ADDMODE    15

// I2C Status register 1
#define I2C_SR1_SB          0
#define I2C_SR1_ADDR        1
#define I2C_SR1_BTF         2
#define I2C_SR1_ADD10       3
#define I2C_SR1_STOPF       4
#define I2C_SR1_RxNE        6
#define I2C_SR1_TxE         7
#define I2C_SR1_BERR        8
#define I2C_SR1_ARLO        9
#define I2C_SR1_AF          10
#define I2C_SR1_OVR         11
#define I2C_SR1_TIME_OUT    14

// I2C Status register 2
#define I2C_SR2_MSL         0
#define I2C_SR2_BUSY        1
#define I2C_SR2_TRA         2
#define I2C_SR2_DUALF       7

//I2C Clock Cotnrol register
#define I2C_CCR_CCR         0
#define I2C_CCR_DUTY        14
#define I2C_CCR_FS          15

// Configure structure for I2Cx peripheral
typedef struct{
    uint32_t I2C_SCLSpeed;
    uint8_t  I2C_DeviceAddr;
    uint8_t  I2C_AckControl;
    uint16_t I2C_FMDutyCyCle;
    uint32_t TimeOut;
}I2C_Congif_t;

// Handle structure for I2Cx peripheral
typedef struct{
    I2C_RegDef_t *pI2Cx;
    I2C_Congif_t I2C_Congif;
}I2C_Handle_t;


typedef enum {
    I2C_ERR_NONE     = 0x00,
    I2C_ERR_ADDR     = 0x01,
    I2C_ERR_TXE      = 0x02,
    I2C_ERR_BTF      = 0x04,
    I2C_ERR_ACKFAIL  = 0x08,
    I2C_ERR_ARLO     = 0x10,
    I2C_ERR_BUS      = 0x20
} I2C_ErrorFlags;

typedef struct {
    uint8_t errorFlags;
} I2C_Error_t;

// I2C SCL Speed Control
#define I2C_SCL_SPEED_SM    100000		// Normal mode
#define I2C_SCL_SPEED_FM4K  400000		// Fast mode
#define I2C_SCL_SPEED_FM2K  200000

// I2C Ack Control
#define I2C_ACK_EN          1
#define I2C_ACK_DIS         0

//I2C FM Duty CyCle
#define I2C_FMDUTY_2        0
#define I2C_FMDUTY_16_9     1

// Define flag 
#define I2C_FLAG_SB         (1 << I2C_SR1_SB)
#define I2C_FLAG_TxE        (1 << I2C_SR1_TxE)
#define I2C_FLAG_RxNE       (1 << I2C_SR1_RxNE)
#define I2C_FLAG_OVR        (1 << I2C_SR1_OVR)
#define I2C_FLAG_AF         (1 << I2C_SR1_AF)
#define I2C_FLAG_ARLO       (1 << I2C_SR1_ARLO)
#define I2C_FLAG_BERR       (1 << I2C_SR1_BERR)
#define I2C_FLAG_STOPF      (1 << I2C_SR1_STOPF)
#define I2C_FLAG_ADD10      (1 << I2C_SR1_ADD10)
#define I2C_FLAG_BTF        (1 << I2C_SR1_BTF)
#define I2C_FLAG_ADDR       (1 << I2C_SR1_ADDR)

#define I2C_FLAG_BUSY       (1 << I2C_SR2_BUSY)


// Peripheral Clock setup
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDis);

// Init and DeInit
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(void);

void I2C_Start(I2C_RegDef_t *pI2Cx);
I2C_Error_t I2C_Address(I2C_Handle_t *I2C_Handle);
void I2C_Stop(I2C_RegDef_t *pI2Cx);
// Data Send and Receive
void I2C_MasterSend_Data(I2C_RegDef_t *pI2Cx, uint8_t data);
I2C_Error_t I2C_MasterSend_Multi_Data(I2C_Handle_t *I2C_Handle, uint8_t *pTxbuffer, uint32_t len);
void I2C_MasterRead_Data(I2C_RegDef_t *pI2Cx, uint8_t Address, uint8_t *buffer, uint8_t size);
// IRQ Configuration and ISR hadling
void I2C_IRQInterruptConfig(void);
void I2C_IRQInterruptConfig(void);

// Other Peripheral Control APIs
void I2C_PeripheralControl(void);
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx,uint32_t FlagName);

// Application Callback
void I2C_ApplicationEventCallBack(void);

#ifdef I2C_Debug
// Other func test
void I2C_Debug();
#endif //I2C_Debug

#endif /* INC_STM32F411_I2C_H_ */
