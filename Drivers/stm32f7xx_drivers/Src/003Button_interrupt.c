

#include "stm32f7xx.h"
#include "stm32f7xx_gpio_driver.h"

#include <stdio.h>

#define HIGH			1
#define BTN_PRESSED 	HIGH

/*void delay()
{
	for(uint32_t i=0;i<=250000;i++);
}*/


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

	GpioBtn.pGPIOx = GPIOI;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	//GPIO_PeriClockControl(GPIOI, ENABLE);

	GPIO_Init(&GpioBtn);


	//IRQ configurations
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRI0);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);

	while(1);

}

void EXTI15_10_IRQHandler(void)
{
	GPIO_IRQHandling(GPIO_PIN_NO_11);
	GPIO_ToggleOutputPin(GPIOI, GPIO_PIN_NO_1);
	printf("Vishniew\n");
}
