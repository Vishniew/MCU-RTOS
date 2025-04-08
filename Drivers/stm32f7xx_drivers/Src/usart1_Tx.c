/*
 * usart1_Tx.c
 *
 *  Created on: Apr 3, 2025
 *      Author: packetp
 */
#include <stdio.h>
#include <string.h>

#include "stm32f7xx.h"

char msg[1024] = "UART Tx testing...\n";
char rxbuf[100];
USART_Handle_t usart1_handle;

void USART1_Init(void)
{
	usart1_handle.pUSARTx = USART1;
	usart1_handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	usart1_handle.USART_Config.HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	usart1_handle.USART_Config.USART_Mode = USART_MODE_TX_ONLY;
	usart1_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	usart1_handle.USART_Config.WordLength = USART_WORDLEN_8BITS;
	usart1_handle.USART_Config.ParityControl = USART_PARITY_DISABLE;
	USART_Init(&usart1_handle);
}

void USART1_GPIOInit(void)
{
	GPIO_Handle_t usart_gpios;

	usart_gpios.pGPIOx = GPIOA;
	usart_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	usart_gpios.GPIO_PinConfig.GPIO_PinOpType = GPIO_OP_TYPE_PP;
	usart_gpios.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	usart_gpios.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	usart_gpios.GPIO_PinConfig.GPIO_PinAltFunMode =7;

	//USART1 TX
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber  = GPIO_PIN_NO_9;
	GPIO_Init(&usart_gpios);

	//USART1 RX
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
	GPIO_Init(&usart_gpios);


}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t GPIOBtn;

	//this is btn gpio configuration
	GPIOBtn.pGPIOx = GPIOI;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOBtn);


}


void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}

int main(void)
{
	GPIO_ButtonInit();
	USART1_GPIOInit();

	USART1_Init();

	USART_PeripheralControl(USART1,ENABLE);

	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRI0);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);

	printf("Before While..\n");
	while(1);



}

void EXTI15_10_IRQHandler(void)
{
	// Check if EXTI interrupt flag is set for GPIO_PIN_NO_11
	if(EXTI->PR & (1 << GPIO_PIN_NO_11))
	{
		printf("Button Pressed! Sending UART Data...\n");

		// Clear EXTI interrupt flag
		GPIO_IRQHandling(GPIO_PIN_NO_11);

		// Send data via USART
		USART_SendData(&usart1_handle, (uint8_t*)msg, strlen(msg));
	}
}

void USART1_IRQHandler(void)
{
	printf("Interrupt Handler...\n");


	    // Send data via USART
	USART_SendData(&usart1_handle, (uint8_t*)msg, strlen(msg));
}
