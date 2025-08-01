/*
 * stm32f411_gpio_driver.c
 *
 *  Created on: Jul 5, 2023
 *      Author: HuynhPhuoc
 */

#include "stm32f411.h"

// Configure pin
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDis){
    if(EnOrDis){
        if(pGPIOx == GPIOA)      GPIOA_PCLK_EN;
        else if(pGPIOx == GPIOB) GPIOB_PCLK_EN;
        else if(pGPIOx == GPIOC) GPIOC_PCLK_EN;
        else if(pGPIOx == GPIOD) GPIOD_PCLK_EN;
    }
    else{
        if(pGPIOx == GPIOA)      GPIOA_PCLK_DIS;
        else if(pGPIOx == GPIOB) GPIOB_PCLK_DIS;
        else if(pGPIOx == GPIOC) GPIOC_PCLK_DIS;
        else if(pGPIOx == GPIOD) GPIOD_PCLK_DIS;
    }
}

//Init and Denit
void GPIO_Init(GPIO_Handle_t *pGPIOHandel){
	for (int Pin_Number = 0; Pin_Number < GPIO_PIN_15; Pin_Number++){
		if ((pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber >> Pin_Number) & 0x1){
//			 1.Configgure mode GPIO pin
			uint32_t temp = 0;
			if(pGPIOHandel->GPIO_Pin_Config.GPIO_PinMode <= GPIO_MODER_ANALOG){
				temp = pGPIOHandel->GPIO_Pin_Config.GPIO_PinMode << (2* Pin_Number);
				pGPIOHandel->pGPIOx->MODER &= ~(3 << (2* Pin_Number));
				pGPIOHandel->pGPIOx->MODER |= temp;
			}
			else{
				// Interrupt
			}
			temp = 0;
			// 2.Configure speed
			if(pGPIOHandel->GPIO_Pin_Config.GPIO_PinSpeed <= GPIO_OSPEEDR_VERYHIGH){
				temp = pGPIOHandel->GPIO_Pin_Config.GPIO_PinSpeed << (2* Pin_Number);
				pGPIOHandel->pGPIOx->OSPEEDR &= ~(3 << (2* Pin_Number));
				pGPIOHandel->pGPIOx->OSPEEDR |= temp;
			}
			else{
			   // Interrupt
			}
			temp = 0;

			// 3.Configure pupd setting
			if(pGPIOHandel->GPIO_Pin_Config.GPIO_PinPuPdControl <= GPIO_PUPDR_RESERVED){
				temp = pGPIOHandel->GPIO_Pin_Config.GPIO_PinPuPdControl << (2* Pin_Number);
				pGPIOHandel->pGPIOx->PUPDR &= ~(3 << (2* Pin_Number));
				pGPIOHandel->pGPIOx->PUPDR |= temp;
			}
			else{
				// Interrupt
			}
			temp = 0;
			// 4.Configure otype
			if(pGPIOHandel->GPIO_Pin_Config.GPIO_PinOPType <= GPIO_OTYPER_OD){
				temp = pGPIOHandel->GPIO_Pin_Config.GPIO_PinOPType << Pin_Number;
				pGPIOHandel->pGPIOx->OTYPER &= ~(1 << Pin_Number);
				pGPIOHandel->pGPIOx->OTYPER |= temp;
			}
			else{
				// Interrupt
			}
			temp = 0;
			// 5.Configure alt func mode
			if (pGPIOHandel->GPIO_Pin_Config.GPIO_PinAltFunMode_High <= GPIO_AFRH_AF15){
				temp = pGPIOHandel->GPIO_Pin_Config.GPIO_PinAltFunMode_High << (4 * (Pin_Number - 8));
				pGPIOHandel->pGPIOx->AFRH &= ~(4 << (4 * (Pin_Number - 8)));
				pGPIOHandel->pGPIOx->AFRH |= temp;
			}

			temp = 0;
			if (pGPIOHandel->GPIO_Pin_Config.GPIO_PinAltFunMode_Low <= GPIO_AFRL_AF15){
				temp = pGPIOHandel->GPIO_Pin_Config.GPIO_PinAltFunMode_Low << (4 * (Pin_Number));
				pGPIOHandel->pGPIOx->AFRL &= ~(4 << (4 * Pin_Number));
				pGPIOHandel->pGPIOx->AFRL |= temp;
			}
			temp = 0;
		}
	}
}


void GPIO_Init_Pin(GPIO_Handle_t *pGPIOHandel){	// Exactly Timer config
	uint32_t temp = 0;
	if(pGPIOHandel->GPIO_Pin_Config.GPIO_PinMode <= GPIO_MODER_ANALOG){
		temp = pGPIOHandel->GPIO_Pin_Config.GPIO_PinMode << (2* pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber);
		pGPIOHandel->pGPIOx->MODER &= ~(3 << (2* pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber));
		pGPIOHandel->pGPIOx->MODER |= temp;
	}
	else{
		// Interrupt
	}
	temp = 0;
	// 2.Configure speed
	if(pGPIOHandel->GPIO_Pin_Config.GPIO_PinSpeed <= GPIO_OSPEEDR_VERYHIGH){
		temp = pGPIOHandel->GPIO_Pin_Config.GPIO_PinSpeed << (2* pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber);
		pGPIOHandel->pGPIOx->OSPEEDR &= ~(3 << (2* pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber));
		pGPIOHandel->pGPIOx->OSPEEDR |= temp;
	}
	else{
	   // Interrupt
	}
	temp = 0;

	// 3.Configure pupd setting
	if(pGPIOHandel->GPIO_Pin_Config.GPIO_PinPuPdControl <= GPIO_PUPDR_RESERVED){
		temp = pGPIOHandel->GPIO_Pin_Config.GPIO_PinPuPdControl << (2* pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber);
		pGPIOHandel->pGPIOx->PUPDR &= ~(3 << (2* pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber));
		pGPIOHandel->pGPIOx->PUPDR |= temp;
	}
	else{
		// Interrupt
	}
	temp = 0;
	// 4.Configure otype
	if(pGPIOHandel->GPIO_Pin_Config.GPIO_PinOPType <= GPIO_OTYPER_OD){
		temp = pGPIOHandel->GPIO_Pin_Config.GPIO_PinOPType << pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber;
		pGPIOHandel->pGPIOx->OTYPER &= ~(1 << pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber);
		pGPIOHandel->pGPIOx->OTYPER |= temp;
	}
	else{
		// Interrupt
	}
	temp = 0;
	// 5.Configure alt func mode
	if (pGPIOHandel->GPIO_Pin_Config.GPIO_PinAltFunMode_High <= GPIO_AFRH_AF15){
		temp = pGPIOHandel->GPIO_Pin_Config.GPIO_PinAltFunMode_High << (4 * (pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber - 8));
		pGPIOHandel->pGPIOx->AFRH &= ~(4 << (4 * (pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber - 8)));
		pGPIOHandel->pGPIOx->AFRH |= temp;
	}

	temp = 0;
	if (pGPIOHandel->GPIO_Pin_Config.GPIO_PinAltFunMode_Low <= GPIO_AFRL_AF15){
		temp = pGPIOHandel->GPIO_Pin_Config.GPIO_PinAltFunMode_Low << (4 * (pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber));
		pGPIOHandel->pGPIOx->AFRL &= ~(4 << (4 * pGPIOHandel->GPIO_Pin_Config.GPIO_PinNumber));
		pGPIOHandel->pGPIOx->AFRL |= temp;
	}
	temp = 0;
}

void GPIO_Denit(GPIO_RegDef_t *pGPIOx){
    if(pGPIOx == GPIOA) GPIOA_REG_RST();
    else if(pGPIOx == GPIOB) GPIOB_REG_RST();
    else if(pGPIOx == GPIOC) GPIOC_REG_RST();
    else if(pGPIOx == GPIOD) GPIOC_REG_RST();
}

// Data read and write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIO, uint8_t GPIO_PinNumber){
    uint8_t value;
    value = (uint8_t)((pGPIO->IDR >> GPIO_PinNumber) & 0x00000001);
    return value;
}

uint16_t GPIO_ReadFromInpurPort(GPIO_RegDef_t *pGPIOx){
    uint16_t value;
    value = (uint16_t)(pGPIOx->IDR);
    return value;
}

void GPIO_WriteToOutPutPin(GPIO_RegDef_t *pGPIOx, uint8_t GPIO_PinNumber, uint8_t Status){
    if(Status == GPIO_PIN_SET){
        pGPIOx->ODR |= (1 << GPIO_PinNumber);
    }
    else{
        pGPIOx->ODR &= ~(1 << GPIO_PinNumber);
    }
}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value){
    pGPIOx->ODR = Value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t GPIO_PinNumber){
    pGPIOx->ODR ^= (1<<GPIO_PinNumber);
}
