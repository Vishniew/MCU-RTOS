

#include "stm32f7xx.h"
#include "stm32f7xx_gpio_driver.h"

void delay()
{
	for(uint32_t i=0;i<=500000;i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed;										//Variable for GPIO_Handle structure
	GpioLed.pGPIOx = GPIOI;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOpType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOI, ENABLE);

	GPIO_Init(&GpioLed);

	while(1)
	{
		GPIO_ToggleOutputPin(GPIOI, GPIO_PIN_NO_1);
		delay();
	}
}
