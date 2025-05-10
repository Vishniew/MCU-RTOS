 #include <stdio.h>
#include "stm32f7xx_spi_driver.h"

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);

/*Peripheral clock setup*/

/************************************************************************************
 * @fn					- SPI_PeriClockControl
 *
 * @brief				-	This function enables or disables the peripheral clock for the given SPI
 *
 * param[in]			-	base address of the SPI peripheral
 * param[in]			-	Macros of ENABLE and DISABLE
 * param[in]			-
 * return				-	None
 *
 * Note					-	None
 *
 *
 ************************************************************************************/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
		if(EnorDi == ENABLE)
		{
			if(pSPIx == SPI1)
			{
				SPI1_PCLK_EN();
			}
			else if(pSPIx == SPI2)
			{
				SPI2_PCLK_EN();
			}
			else if(pSPIx == SPI3)
			{
				SPI3_PCLK_EN();
			}

		}
		else
		{
			if(pSPIx == SPI1)
			{
				SPI1_PCLK_DI();
			}
			else if(pSPIx == SPI2)
			{
				SPI2_PCLK_DI();
			}
			else if(pSPIx == SPI3)
			{
				SPI3_PCLK_DI();
			}

		}
}

/************************************************************************************
 * 							Init and DeInit
 ***********************************************************************************/

/************************************************************************************
 * @fn					-SPI_Init
 *
 * @brief				- This program initialises the
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
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	//Enable the peripheral clock
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	//Configuring SPI_CR1 register

	uint32_t tempreg = 0;

	//1.Configure the device mode

	tempreg |= pSPIHandle ->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;

	//2.Configure the bus config

	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//BiDi mode should be cleared
		tempreg &= ~(1<< SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//BiDi mode should be set
		tempreg |= (1<< SPI_CR1_BIDIMODE);


	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		//BiDi mode should be cleared
		tempreg &= ~(1<<SPI_CR1_BIDIMODE);

		//RXONLY should be set
		tempreg |= (1<<SPI_CR1_RXONLY);


	}

	//3.configure the SPI serial clock speed (baud rate)

	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

	//4.configure the DFF

	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_CRCL;

	//5.configure the CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	//6.configure the CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	//7.configure the SSM
	tempreg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;


	pSPIHandle->pSPIx->CR1 = tempreg;
}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();
	}
	else if(pSPIx == SPI2)
	{
		SPI2_REG_RESET();
	}
	else if(pSPIx == SPI3)
	{
		SPI3_REG_RESET();
	}
}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx,uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/*
 * Data send and receive
 */
/************************************************************************************
 * @fn					-SendData
 *
 * @brief				- This program initialises the
 *
 * param[in]			- Base address of SPIx handle
 * param[in]			-Pointer to Transfer buffer
 * param[in]			-Length of data bytes
 * return				-None
 *
 * Note					-	This is Blocking call
 *
 *
 *********************************************************************************/
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len>0)
	{
		//1.Wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG) == FLAG_RESET);

		//2.Check the DFF/CRCL bit in CR1
		if(pSPIx->CR1 & (1<<SPI_CR1_CRCL))
		{
			//16-bit DFF
			//1.Load the data in DR
			pSPIx->DR = *(uint16_t *)pTxBuffer;
			Len--;
			Len--;
			(uint16_t *)pTxBuffer++;
		}
		else
		{
			//8 bit DFF
			pSPIx->DR = *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}
}
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		//1.Wait until RXNE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG)  == FLAG_RESET);
		//2.Check the DFF/CRCL bit in CR1
		if(pSPIx->CR1 & (1<<SPI_CR1_CRCL))
		{
			//16-bit DFF
			//1.Load the data from DR to RxBuffer

			*(uint16_t *)pRxBuffer = pSPIx->DR ;
			Len -= 2;
			pRxBuffer += 2;
		}
		else
		{
			//8 bit DFF
			*pRxBuffer = pSPIx->DR;
			Len--;
			pRxBuffer++;
		}
	}
}


void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDI)
{
	if(EnorDI == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);

	}
}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDI)
{
	if(EnorDI == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);

	}
}


/*
 * IRQ configuration and ISR handling
 */

void SPI_IRQInterruptConfig(uint8_t IRQNumber,  uint8_t EnorDi)
{
		if(EnorDi == ENABLE)
		{
			if(IRQNumber < 32)
			{
				//Program ISER0 register
				*NVIC_ISER0 |= (1 << IRQNumber);
			}
			else if(31 < IRQNumber && IRQNumber < 64) //32 to 63
			{
				//Program ISER1 register
				*NVIC_ISER1 |= (1 << (IRQNumber % 32));

			}
			else if(63 < IRQNumber && IRQNumber < 96) //64 to 95
			{
				//Program ISER2 register
				*NVIC_ISER2 |= (1 << (IRQNumber % 64));

			}
		}
		else
		{
			if(IRQNumber < 32)
			{
				//Program ISER0 register
				*NVIC_ICER0 &= ~(1 << IRQNumber);

			}
			else if(31 < IRQNumber && IRQNumber < 64) //32 to 63
			{
				//Program ISER1 register
				*NVIC_ICER1 &= ~(1 << (IRQNumber % 32));

			}
			else if(63 < IRQNumber && IRQNumber < 96) //64 to 95
			{
				//Program ISER2 register
				*NVIC_ICER2 &= ~(1 << (IRQNumber % 64));

			}
		}


}
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t Priority)
{
	//finding the IPRx register
		uint8_t iprx = IRQNumber/4;
		uint8_t iprx_section = IRQNumber%4;

		uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
		*(NVIC_PR_BASE_AADR + (4*iprx)) |= (IRQNumber << shift_amount);
}
void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
	uint8_t temp1, temp2;

	//1. Check for TXE
	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_TXE);

	temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_TXEIE);

	if(temp1 && temp2)			//Interrupt is due to setting of TXE
	{
		//Handle TXE
		spi_txe_interrupt_handle(pHandle);

	}

	//1. Check for RXNE
	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_RXNE);

	temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE);

	if(temp1 && temp2)			//Interrupt is due to setting of RXNE
	{
		//Handle RXNE
		spi_rxne_interrupt_handle(pHandle);

	}


	//1. Check for OVR
	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_OVR);

	temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_EERIE);

	if(temp1 && temp2)			//Interrupt is due to setting of RXNE
	{
		//Handle OVR Error
		spi_ovr_err_interrupt_handle(pHandle);

	}


}


uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pTxBuffer, uint32_t Len)
{

	uint8_t state = pSPIHandle->TxState;

	if(state != SPI_BUSY_IN_TX)
	{
		//1. Save the Tx buffer address and Len information in some global variables

		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLen = Len;

		/*2. Mark the SPI state as busy in transmission so that no other code can take over the same SPI peripheral
		 * until the transimission is over
		 */

		pSPIHandle->TxState = SPI_BUSY_IN_TX;

		//3. Enable the TXEIE(CR2) control bit to get an interrupt whenever TXE flag is set in SR(status register)

		pSPIHandle->pSPIx->CR2 |= (1<<SPI_CR2_TXEIE);
	}

	return state;


}
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t state = pSPIHandle->RxState;

	if(state != SPI_BUSY_IN_RX)
	{
		//1. Save the Tx buffer address and Len information in some global variables

		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLen = Len;

		/*2. Mark the SPI state as busy in transmission so that no other code can take over the same SPI peripheral
		 * until the transimission is over
		 */

		pSPIHandle->RxState = SPI_BUSY_IN_RX;

		//3. Enable the TXEIE(CR2) control bit to get an interrupt whenever TXE flag is set in SR(status register)

		pSPIHandle->pSPIx->CR2 |= (1<<SPI_CR2_RXNEIE);
	}

	return state;
}


//Some helper function implementations

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
			//2.Check the DFF/CRCL bit in CR1
			if(pSPIHandle->pSPIx->CR1 & (1<<SPI_CR1_CRCL))
			{
				//16-bit DFF
				//1.Load the data in DR
				pSPIHandle->pSPIx->DR = *((uint16_t *)pSPIHandle->pTxBuffer);
				pSPIHandle->TxLen--;
				pSPIHandle->TxLen--;
				(uint16_t *)pSPIHandle->pTxBuffer++;
			}
			else
			{
				//8 bit DFF
				pSPIHandle->pSPIx->DR = *pSPIHandle->pTxBuffer;
				pSPIHandle->TxLen--;
				pSPIHandle->pTxBuffer++;
			}

			if(!pSPIHandle->TxLen)
			{
				//TxLen is zero , so close the spi transmission and inform the application that Tx is over.
				//This prevents interrupts from setting up of TXE flag

				SPI_CloseTransmission(pSPIHandle);

				SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_TX_CMPLT);
			}
}
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	//2.Check the DFF/CRCL bit in CR1
	if(pSPIHandle->pSPIx->CR1 & (1<<SPI_CR1_CRCL))
	{
		//16-bit DFF
		//1.Load the data in DR
		*((uint16_t *)pSPIHandle->pRxBuffer) = (uint16_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen -= 2;
		pSPIHandle->pRxBuffer--;
		pSPIHandle->pRxBuffer--;

	}
	else
	{
		//8 bit DFF
		*(pSPIHandle->pRxBuffer) = (uint8_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		pSPIHandle->pRxBuffer--;

	}

	if(!pSPIHandle->RxLen)
	{
		//TxLen is zero , so close the spi transmission and inform the application that Tx is over.
		//Turn off RXNEIE
		//This prevents interrupts from setting up of TXE flag

		SPI_CloseReception(pSPIHandle);

		SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_RX_CMPLT);
	}
}
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp;
	//1. clear the ovr flag
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;

	}
	(void)temp;
	//2. Inform the application
	SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_OVR_ERR);


}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);
	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->TxLen = 0;
	pSPIHandle->TxState = SPI_READY;

}
void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxLen = 0;
	pSPIHandle->RxState = SPI_READY;

}

void SPI_CLEAROVRFLAG(SPI_RegDef_t *pSPIx)
{
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;
}

__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEV)
{
    (void)pSPIHandle;
    (void)AppEV;
    // Weak implementation: application may override this function.
}


