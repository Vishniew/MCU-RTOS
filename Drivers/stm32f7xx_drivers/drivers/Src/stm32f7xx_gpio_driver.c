/*
 * stm32f7xx_gpio_driver.c
 *
 *  Created on: Jan 1, 2025
 *      Author: packetp
 */
#include <stdio.h>
#include "stm32f7xx_gpio_driver.h"

/************************************************************************************
 * 							Peripheral clock setup
 ***********************************************************************************/

/************************************************************************************
 * @fn					- GPIO_PeriClockControl
 *
 * @brief				-	This function enables or disables the peripheral clock for the given GPIO port
 *
 * param[in]			-	base address of the GPIO peripheral
 * param[in]			-	Macros of ENABLE and DISABLE
 * param[in]			-
 * return				-	None
 *
 * Note					-	None
 *
 *
 ************************************************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}


	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}
		else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DI();
		}

	}
}

/************************************************************************************
 * 							Init and DeInit
 ***********************************************************************************/

/************************************************************************************
 * @fn					-GPIO_Init
 *
 * @brief				- This program initialises the given GPIO pin
 *
 * param[in]			- Base address of GPIO handle
 * param[in]			-
 * param[in]			-
 * return				-	None
 *
 * Note					-	None
 *
 *
 ************************************************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0; 	//temp register

	//Enable the peripheral clock
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx,ENABLE);

	// 1.Configure the mode of GPIO pin

	if(pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
						/*Non-interrupt part*/

		/*2 bits are dedicated to each pin. Hence shifted by 2*/
		temp = (pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle -> pGPIOx->MODER &= ~(0x3 << (2*pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));	//Clearing

		pGPIOHandle -> pGPIOx->MODER |= temp;		//Setting

	}
	else
	{
		/*
		 * Interrupt mode part
		 */
		if(pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//1. Configure FTSR
			EXTI -> FTSR |= (1 << pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);
			//Clear the corresponding RTSR bit
			EXTI -> RTSR &= ~(1 << pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);

		}
		else if(pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//1. Configure RTSR
			EXTI -> RTSR |= (1 << pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);
			//Clear the corresponding FTSR bit
			EXTI -> FTSR &= ~(1 << pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);

		}
		else if(pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//1.Configure FTSR
			EXTI -> FTSR |= (1 << pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);
			//Configure RTSR
			EXTI -> RTSR |= (1 << pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);

		}
		//2. configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1,temp2;

		temp1 = pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber / 4;
		temp2 = pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber % 4;

		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle -> pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG ->EXTICR[temp1] = portcode << (4 * temp2);





		//3. Enable the EXTI interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	temp = 0;

	// 2.Configure the speed
	temp = (pGPIOHandle -> GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle -> pGPIOx->SPEEDR &= ~(0x3 << (2*pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));	//Clearing

	pGPIOHandle -> pGPIOx->SPEEDR |= temp;	//Setting

	temp = 0;


	// 3.Configure the pupd settings

	temp = (pGPIOHandle -> GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));

	pGPIOHandle -> pGPIOx->PUPDR &= ~(0x3 << (2*pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber));	//Clearing

	pGPIOHandle -> pGPIOx->PUPDR |= temp;	//Setting

	temp = 0;

	// 4.Configure the OPtype

	temp = (pGPIOHandle -> GPIO_PinConfig.GPIO_PinOpType << pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);

	pGPIOHandle -> pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber);	//Clearing

	pGPIOHandle -> pGPIOx->OTYPER |= temp;	//Setting

	temp = 0;

	// 5.Configure the alt functionality

	if(pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint8_t temp1,temp2;

		temp1 = pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle -> GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle -> pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));

		pGPIOHandle -> pGPIOx->AFR[temp1] |= (pGPIOHandle -> GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
	}




}
/************************************************************************************
 * @fn					- GPIO_DeInit
 *
 * @brief				- This program resets the given GPIO port
 *
 * param[in]			-	Base address of GPIO peripheral
 * param[in]			-
 * param[in]			-
 * return				-	None
 *
 * Note					-	None
 *
 *
 ************************************************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
			if(pGPIOx == GPIOA)
			{
				GPIOA_REG_RESET();
			}
			else if(pGPIOx == GPIOB)
			{
				GPIOB_REG_RESET();
			}
			else if(pGPIOx == GPIOC)
			{
				GPIOC_REG_RESET();
			}
			else if(pGPIOx == GPIOD)
			{
				GPIOD_REG_RESET();
			}
			else if(pGPIOx == GPIOE)
			{
				GPIOE_REG_RESET();
			}
			else if(pGPIOx == GPIOF)
			{
				GPIOF_REG_RESET();
			}
			else if(pGPIOx == GPIOG)
			{
				GPIOG_REG_RESET();
			}
			else if(pGPIOx == GPIOH)
			{
				GPIOH_REG_RESET();
			}
			else if(pGPIOx == GPIOI)
			{
				GPIOI_REG_RESET();
			}




}

/************************************************************************************
 * 								Data Read and Write*/
/************************************************************************************
 * @fn					- GPIO_ReadFromInputPin
 *
 * @brief				- this function reads data from input pin
 *
 * param[in]			- Base address of given GPIO port
 * param[in]			- GPIOx Pin number
 * param[in]			-
 * return				-	0 or 1
 *
 * Note					-	None
 *
 *
 ************************************************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)((pGPIOx -> IDR >> PinNumber) & 0x00000001);
	return value;
}

/************************************************************************************
 * @fn					-GPIO_ReadFromInputPort
 *
 * @brief				-This function reads data from input port
 *
 * param[in]			-Base address of given GPIO port
 * param[in]			-
 * param[in]			-
 * return				-	1 or 0
 *
 * Note					-	None
 *
 *
 ************************************************************************************/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx -> IDR;
	return value;
}


/************************************************************************************
 * @fn					-GPIO_WriteToOutputPin
 *
 * @brief				-This function writes data to GPIO output pin
 *
 * param[in]			-Base address of given GPIO port
 * param[in]			-GPIO pin number
 * param[in]			-value to be written
 * return				-	None
 *
 * Note					-	None
 *
 *
 ************************************************************************************/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value)
{
	if(value == GPIO_PIN_SET)
	{
		//write 1 to the output data register at the bit field corresponding to pin
		pGPIOx -> ODR |= (1 << PinNumber);
	}
	else
	{
		//write 0
		pGPIOx -> ODR &= ~(1 << PinNumber);

	}
}


/************************************************************************************
 * @fn					-GPIO_WriteToOutputPort
 *
 * @brief				-This function writes data to GPIO output port
 *
 * param[in]			-Base address of given GPIO port
 * param[in]			-value to be written
 * param[in]			-
 * return				-	None
 *
 * Note					-	None
 *
 *
 ************************************************************************************/
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
	pGPIOx -> ODR = value;
}

/************************************************************************************
 * @fn					-GPIO_ToggleOutputPin
 *
 * @brief				-This function toggles the Outpin value
 *
 * param[in]			-Base address of GPIO peripheral
 * param[in]			-
 * param[in]			-
 * return				-	None
 *
 * Note					-	None
 *
 *
 ************************************************************************************/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1<<PinNumber);
}

/***********************************************************************************
 * 							*IRQ Configuration and Interrupt handling*/
/************************************************************************************
 * @fn					-GPIO_IRQInterruptConfig
 *
 * @brief				-This function confugures the Interrupt related settings for a GPIO pin
 *
 * param[in]			-IRQ number
 * param[in]			- Macros of ENABLE or DISABLE
 * return				-	None
 *
 * Note					-	None
 *
 *
 ************************************************************************************/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber < 32)
		{
			//Program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber < 64) //32 to 63
		{
			//Program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));

		}
		else if(IRQNumber < 96) //64 to 95
		{
			//Program ISER2 register
			*NVIC_ISER2 |= (1 << (IRQNumber % 32));

		}
	}
	else
	{
		if(IRQNumber < 32)
		{
			//Program ISER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);

		}
		else if(IRQNumber < 64) //32 to 63
		{
			//Program ISER1 register
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));

		}
		else if(IRQNumber < 96) //64 to 95
		{
			//Program ISER2 register
			*NVIC_ICER2 |= (1 << (IRQNumber % 32));

		}
	}

}

/************************************************************************************
 * @fn					-GPIO_IRQPriorityConfig
 *
 * @brief				- This functions sets the priority for the peripheral

 *
 * param[in]			- IRQ Number
 *
 * param[in]			- Priority
 * param[in]			-
 * return				-	None
 *
 * Note					-	None
 *
 *
 ************************************************************************************/

/*void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t Priority)
{
	//finding the IPRx register
	uint8_t iprx = IRQNumber/4;
	uint8_t iprx_section = IRQNumber%4;

	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_AADR + (4*iprx)) |= (Priority << shift_amount);
}*/
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t Priority)
{
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

    // Proper casting to a pointer before dereferencing
    volatile uint32_t *ipr_reg = (volatile uint32_t *)(NVIC_PR_BASE_AADR + (4 * iprx));

    *ipr_reg &= ~(0xF << shift_amount);   // Clear bits before setting new priority
    // Print the value before modification
    	printf("Before Writing: Addr = %p, Value = 0x%08X\n", ipr_reg, *ipr_reg);

    	// Apply priority
    	*ipr_reg |= (Priority << shift_amount);
    	*ipr_reg = 0xFF;
    	printf("Manually Written: Addr = %p, Value = 0x%08X\n", ipr_reg, *ipr_reg);

    	// Print the value after modification
    	printf("After Writing: Addr = %p, Value = 0x%08X\n", ipr_reg, *ipr_reg);
}


/************************************************************************************
 * @fn					-
 *
 * @brief				-
 *
 * param[in]			-
 * param[in]			-
 * param[in]			-
 * return				-	None
 *
 * Note					-	None
 *
 *
 ************************************************************************************/
void GPIO_IRQHandling(uint8_t PinNumber)
{
	//clear the EXTI PR register corresponding to pin number
	if(EXTI -> PR & (1<<PinNumber))
	{
		EXTI -> PR |= (1<<PinNumber);
	}
}
