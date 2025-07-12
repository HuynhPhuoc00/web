/*
 * stm32f411_gpio_driver.h
 *
 *  Created on: Jul 5, 2023
 *      Author: HuynhPhuoc
 */

#ifndef INC_STM32F411_GPIO_DRIVER_H_
#define INC_STM32F411_GPIO_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f411.h"

//GPIO Type
typedef struct{
    uint16_t GPIO_PinNumber;			//
    uint8_t GPIO_PinMode;           //
    uint8_t GPIO_PinSpeed;			// tốc độ truyền dữ liệu trên chân GPIO.
    uint8_t GPIO_PinPuPdControl;	// kiểm soát điện trở kéo lên hoặc kéo xuống trên chân GPIO.
    uint8_t GPIO_PinOPType;			// chế độ hoạt động đầu ra của chân GPIO (ví dụ: push-pull, open-drain, ...).
    uint8_t GPIO_PinAltFunMode_High;		// chế độ hoạt động chức năng thay thế (alternate function) của chân GPIO (nếu có).
    uint8_t GPIO_PinAltFunMode_Low;		// chế độ hoạt động chức năng thay thế (alternate function) của chân GPIO (nếu có).

}GPIO_Pin_Config_t;

typedef struct{
    GPIO_RegDef_t     *pGPIOx;
    GPIO_Pin_Config_t GPIO_Pin_Config;
}GPIO_Handle_t;

// GPIO pin number
#define GPIO_PIN_NUM_0		            0
#define GPIO_PIN_NUM_1		            1
#define GPIO_PIN_NUM_2		            2
#define GPIO_PIN_NUM_3		            3
#define GPIO_PIN_NUM_4		            4
#define GPIO_PIN_NUM_5		            5
#define GPIO_PIN_NUM_6		            6
#define GPIO_PIN_NUM_7		            7
#define GPIO_PIN_NUM_8		            8
#define GPIO_PIN_NUM_9		            9
#define GPIO_PIN_NUM_10		            10
#define GPIO_PIN_NUM_11		            11
#define GPIO_PIN_NUM_12		            12
#define GPIO_PIN_NUM_13		            13
#define GPIO_PIN_NUM_14		            14
#define GPIO_PIN_NUM_15		            15

#define PIN_NUM_0		          (1 << GPIO_PIN_NUM_0)
#define PIN_NUM_1		          (1 << GPIO_PIN_NUM_1)
#define PIN_NUM_2		          (1 << GPIO_PIN_NUM_2)
#define PIN_NUM_3		          (1 << GPIO_PIN_NUM_3)
#define PIN_NUM_4		          (1 << GPIO_PIN_NUM_4)
#define PIN_NUM_5		          (1 << GPIO_PIN_NUM_5)
#define PIN_NUM_6		          (1 << GPIO_PIN_NUM_6)
#define PIN_NUM_7		          (1 << GPIO_PIN_NUM_7)
#define PIN_NUM_8		          (1 << GPIO_PIN_NUM_8)
#define PIN_NUM_9		          (1 << GPIO_PIN_NUM_9)
#define PIN_NUM_10		          (1 << GPIO_PIN_NUM_10)
#define PIN_NUM_11		          (1 << GPIO_PIN_NUM_11)
#define PIN_NUM_12		          (1 << GPIO_PIN_NUM_12)
#define PIN_NUM_13		          (1 << GPIO_PIN_NUM_13)
#define PIN_NUM_14		          (1 << GPIO_PIN_NUM_14)
#define PIN_NUM_15		          (1 << GPIO_PIN_NUM_15)

// GPIO port mode register
#define GPIO_MODER_INPUT                0
#define GPIO_MODER_OUTPUT               1
#define GPIO_MODER_ALTFM                2
#define GPIO_MODER_ANALOG               3

// GPIO port output type register
#define  GPIO_OTYPER_PP                 0
#define  GPIO_OTYPER_OD                 1

// GPIO port output speed register
#define GPIO_OSPEEDR_LOW                0
#define GPIO_OSPEEDR_MEDIUM             1
#define GPIO_OSPEEDR_HIGH               2
#define GPIO_OSPEEDR_VERYHIGH           3

// GPIO port PUPD register
#define GPIO_PUPDR_NOPUPD               0
#define GPIO_PUPDR_PU                   1
#define GPIO_PUPDR_PD                   2
#define GPIO_PUPDR_RESERVED             3

//GPIO port ALT function
#define GPIO_AFRH_AF0               	0
#define GPIO_AFRH_AF1                   1
#define GPIO_AFRH_AF2                   2
#define GPIO_AFRH_AF3             		3
#define GPIO_AFRH_AF4             		4
// ...
#define GPIO_AFRH_AF15            		15

//GPIO port ALT function
#define GPIO_AFRL_AF0               	0
#define GPIO_AFRL_AF1                   1
#define GPIO_AFRL_AF2                   2
#define GPIO_AFRL_AF3             		3
#define GPIO_AFRL_AF4             		4
#define GPIO_AFRL_AF5             		5
// ...
#define GPIO_AFRL_AF7             		7
// ...
#define GPIO_AFRL_AF15            		15
// Configure pin
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDis);

//Init and Denit
void GPIO_Init(GPIO_Handle_t *pGPIOHandel);
void GPIO_Init_Pin(GPIO_Handle_t *pGPIOHandel);
void GPIO_Denit(GPIO_RegDef_t *pGPIOx);

// Data read and write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIO, uint8_t GPIO_PinNumber);
uint16_t GPIO_ReadFromInpurPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutPutPin(GPIO_RegDef_t *pGPIOx, uint8_t GPIO_PinNumber, uint8_t Status);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t GPIO_PinNumber);


#ifdef __cplusplus
}
#endif

#endif /* INC_STM32F411_GPIO_DRIVER_H_ */
