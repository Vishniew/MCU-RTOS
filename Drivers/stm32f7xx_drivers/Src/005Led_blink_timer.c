/*
 * 005Led_blink_timer.c
 *
 *  Created on: Jan 6, 2025
 *      Author: packetp
 */




#include "stm32f7xx.h"
#include "stm32f7xx_gpio_driver.h"

#define HIGH			1
#define BTN_PRESSED 	HIGH





void delay()
{
    for (uint32_t i = 0; i < 250000; i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed, GpioBtn;									//Variables for GPIO_Handle structure

	//This is GPIO LED configuration

	GpioLed.pGPIOx = GPIOI;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOpType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//GPIO_PeriClockControl(GPIOI, ENABLE);

	GPIO_Init(&GpioLed);

	//This is GPIO Button configuration

	GpioLed.pGPIOx = GPIOI;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//GPIO_PeriClockControl(GPIOI, ENABLE);

	GPIO_Init(&GpioBtn);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOI, GPIO_PIN_NO_11) == BTN_PRESSED)
		{
			delay();
			GPIO_ToggleOutputPin(GPIOI, GPIO_PIN_NO_1);

		}

	}
}
