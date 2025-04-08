/*
 * 006Led_blink.c
 *
 *  Created on: Jan 6, 2025
 *      Author: packetp
 */


#include<stdio.h>
#include "stm32f7xx.h"
#include "stm32f7xx_gpio_driver.h"

#define HIGH			1
#define BTN_PRESSED 	HIGH

#define BLINK_1SEC		1000000
#define BLINK_4SEC		4000000
#define BLINK_8SEC		8000000

uint8_t interval_index = 0;
uint32_t delay_time = BLINK_1SEC;

void delay(uint32_t time)
{
    for (uint32_t i = 0; i < time; i++);
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
			delay(150);

			interval_index +=1;
            if(interval_index == 0)
            	delay_time = BLINK_1SEC;
			else if(interval_index == 1)
			    delay_time = BLINK_4SEC;
			else if(interval_index == 2)
			    delay_time = BLINK_8SEC;
			else if(interval_index == 3)
				interval_index = 0;
		}
		GPIO_ToggleOutputPin(GPIOI, GPIO_PIN_NO_1);
		delay(delay_time);


	}
}

