/*
 * stm32f7xx_usart_driver.c
 *
 *  Created on: Apr 2, 2025
 *      Author: packetp
 */
#include <stdio.h>
#include "stm32f7xx_usart_driver.h"

/*********************************************************************
 * @fn      		  - USART_SetBaudRate
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */

void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pUSARTx->CR1 |= (1 << USART_CR1_UE);
	}
	else
	{
		pUSARTx->CR1 &= ~(1 << USART_CR1_UE);
	}
}


void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{
    uint32_t PCLKx, USARTDIV, M_part, F_part;
    uint32_t tempreg = 0;

    if (pUSARTx == USART1 || pUSARTx == USART6)
    {
        PCLKx = RCC_GetPCLK2Value(); // APB2 Clock
    }
    else
    {
        PCLKx = RCC_GetPCLK1Value(); // APB1 Clock
    }

    if (pUSARTx->CR1 & (1 << USART_CR1_OVER8)) // Oversampling by 8
    {
        USARTDIV = ((PCLKx * 2) + (BaudRate / 2)) / BaudRate;
    }
    else // Oversampling by 16
    {
        USARTDIV = (PCLKx + (BaudRate / 2)) / BaudRate;
    }

    M_part = USARTDIV / 16;
    F_part = USARTDIV % 16;

    if (pUSARTx->CR1 & (1 << USART_CR1_OVER8)) // Oversampling by 8
    {
        F_part &= 0x07;  // 3-bit fraction
    }
    else // Oversampling by 16
    {
        F_part &= 0x0F;  // 4-bit fraction
    }

    tempreg = (M_part << 4) | F_part;


    pUSARTx->BRR = tempreg;


}




void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pUSARTx == USART1)
		{
			USART1_PCLK_EN();
		}
		else if(pUSARTx == USART2)
		{
			USART2_PCLK_EN();
		}
		else if(pUSARTx == USART1)
		{
			USART3_PCLK_EN();
		}
	}

	else
	{
		if(pUSARTx == USART1)
		{
			USART1_PCLK_DI();
		}
		else if(pUSARTx == USART2)
		{
			USART2_PCLK_DI();
		}
		else if(pUSARTx == USART1)
		{
			USART3_PCLK_DI();
		}
	}
}

void USART_Init(USART_Handle_t *pUSARTHandle)
{

	//Temporary variable
	uint32_t tempreg=0;

/******************************** Configuration of CR1******************************************/

	//Implement the code to enable the Clock for given USART peripheral
	 USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

	//Enable USART Tx and Rx engines according to the USART_Mode configuration item
	if ( pUSARTHandle->USART_Config.USART_Mode == USART_MODE_RX_ONLY)
	{
		//Implement the code to enable the Receiver bit field
		tempreg|= (1 << USART_CR1_RE);
	}else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TX_ONLY)
	{
		//Implement the code to enable the Transmitter bit field
		tempreg |= ( 1 << USART_CR1_TE);

	}else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TX_RX)
	{
		//Implement the code to enable the both Transmitter and Receiver bit fields
		tempreg |= ( ( 1 << USART_CR1_TE) | ( 1 << USART_CR1_RE) );
	}
	printf("1.tempreg: %ld\n",tempreg);
    //Implement the code to configure the Word length configuration item
	tempreg &= ~((1 << USART_CR1_M0) | (1 << USART_CR1_M1));
	printf("2.tempreg: %ld\n",tempreg);

	if(pUSARTHandle->USART_Config.WordLength == USART_WORDLEN_9BITS)
	{
		tempreg |= (1 << USART_CR1_M0);
	}
	else if(pUSARTHandle->USART_Config.WordLength == USART_WORDLEN_7BITS)
	{
		tempreg |= (1 << USART_CR1_M1);
	}

    //Configuration of parity control bit fields
	if ( pUSARTHandle->USART_Config.ParityControl == USART_PARITY_EN_EVEN)
	{
		//Implement the code to enale the parity control
		tempreg |= ( 1 << USART_CR1_PCE);

		//Implement the code to enable EVEN parity
		//Not required because by default EVEN parity will be selected once you enable the parity control

	}else if (pUSARTHandle->USART_Config.ParityControl == USART_PARITY_EN_ODD )
	{
		//Implement the code to enable the parity control
	    tempreg |= ( 1 << USART_CR1_PCE);

	    //Implement the code to enable ODD parity
	    tempreg |= ( 1 << USART_CR1_PS);

	}

   //Program the CR1 register
	pUSARTHandle->pUSARTx->CR1 = tempreg;

/******************************** Configuration of CR2******************************************/

	tempreg=0;

	//Implement the code to configure the number of stop bits inserted during USART frame transmission
	tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;



	tempreg=0;

	//Configuration of USART hardware flow control
	if ( pUSARTHandle->USART_Config.HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		//Implement the code to enable CTS flow control
		tempreg |= ( 1 << USART_CR3_CTSE);


	}else if (pUSARTHandle->USART_Config.HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		//Implement the code to enable RTS flow control
		tempreg |= ( 1 << USART_CR3_RTSE);

	}else if (pUSARTHandle->USART_Config.HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		//Implement the code to enable both CTS and RTS Flow control
		tempreg |= ( 1 << USART_CR3_CTSE) | ( 1 << USART_CR3_RTSE);
	}


	pUSARTHandle->pUSARTx->CR3 = tempreg;

/******************************** Configuration of BRR(Baudrate register)******************************************/

	//Implement the code to configure the baud rate
	//We will cover this in the lecture. No action required here
	USART_SetBaudRate(pUSARTHandle->pUSARTx,pUSARTHandle->USART_Config.USART_Baud);
}


void USART_DeInit(USART_RegDef_t *pUSARTx)
{
	if(pUSARTx == USART1)
	{
		USART1_REG_RESET();
	}
	else if(pUSARTx == USART2)
	{
		USART2_REG_RESET();
	}
	else if(pUSARTx == USART3)
	{
		USART3_REG_RESET();
	}
}


uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t FlagName)
{
    if(pUSARTx->ISR & FlagName)
    {
    	return FLAG_SET;
    }

   return FLAG_RESET;
}

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
    uint16_t *pdata;

    // Ensure TC flag is cleared before starting transmission
    //pUSARTHandle->pUSARTx->ICR = (1 << USART_ICR_TCCF);

    printf("%c\n",*pTxBuffer);
    // Loop over until "Len" number of bytes are transferred
    for (uint32_t i = 0; i < Len; i++)
    {
        //printf("Waiting for TXE...\n");

        // Wait until TXE flag is set
        while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_TXE_FLAG));

        //printf("TXE set!\n");

        // Check the USART_WordLength for 9BIT or 8BIT frame
        if (pUSARTHandle->USART_Config.WordLength == USART_WORDLEN_9BITS)
        {
            pdata = (uint16_t *)pTxBuffer;
            pUSARTHandle->pUSARTx->TDR = (*pdata & (uint16_t)0x01FF);

            // Check for USART_ParityControl
            if (pUSARTHandle->USART_Config.ParityControl == USART_PARITY_DISABLE)
            {
                // No parity: 9 bits of user data sent
                pTxBuffer += 2;
            }
            else
            {
                // Parity used: 8 bits of user data sent
                pTxBuffer += 1;
            }
        }
        else
        {
            // 8-bit data transfer
            pUSARTHandle->pUSARTx->TDR = (*pTxBuffer & (uint8_t)0xFF);

            // Increment buffer pointer
            pTxBuffer++;
        }

        //printf("End of loop...\n");
    }

    //Wait for TC flag after last byte is sent
    //printf("Waiting for TC...\n");
    while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_TC_FLAG));
    printf("TC set!\n");

    // Clear TC flag
    pUSARTHandle->pUSARTx->ICR = (1 << USART_ICR_TCCF);
}


/*********************************************************************
 * @fn      		  - USART_ReceiveData
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */

void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until RXNE flag is set in the SR
		while(!(USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_RXNE_FLAG)));

		//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
		if(pUSARTHandle->USART_Config.WordLength == USART_WORDLEN_9BITS)
		{
			//We are going to receive 9bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used. so, all 9bits will be of user data

				//read only first 9 bits. so, mask the DR with 0x01FF
				*((uint16_t*) pRxBuffer) = (pUSARTHandle->pUSARTx->RDR  & (uint16_t)0x01FF);

				//Now increment the pRxBuffer two times
				pRxBuffer++;
				pRxBuffer++;
			}
			else
			{
				//Parity is used, so, 8bits will be of user data and 1 bit is parity
				 *pRxBuffer = (pUSARTHandle->pUSARTx->RDR  & (uint8_t)0xFF);

				 //Increment the pRxBuffer
				pRxBuffer++;
			}
		}
		else
		{
			//We are going to receive 8bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used , so all 8bits will be of user data

				//read 8 bits from DR
				 *pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->RDR & (uint8_t)0xFF);
			}

			else
			{
				//Parity is used, so , 7 bits will be of user data and 1 bit is parity

				//read only 7 bits , hence mask the DR with 0X7F
				 *pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->RDR & (uint8_t)0x7F);

			}

			//increment the pRxBuffer
			pRxBuffer++;
		}
	}

}

/*********************************************************************
 * @fn      		  - USART_SendDataWithIT
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Resolve all the TODOs

 */
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t txstate = pUSARTHandle->TxBusyState;

	if(txstate != USART_BUSY_IN_TX)
	{
		pUSARTHandle->TxLen = Len;
		pUSARTHandle->pTxBuffer = pTxBuffer;
		pUSARTHandle->TxBusyState = USART_BUSY_IN_TX;

		//Implement the code to enable interrupt for TXE
		pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_TXEIE);


		//Implement the code to enable interrupt for TC
		pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_TCIE);


	}

	return txstate;

}


/*********************************************************************
 * @fn      		  - USART_ReceiveDataIT
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Resolve all the TODOs

 */
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t rxstate = pUSARTHandle->RxBusyState;

	if(rxstate != USART_BUSY_IN_RX)
	{
		pUSARTHandle->RxLen = Len;
		pUSARTHandle->pRxBuffer = pRxBuffer;
		pUSARTHandle->RxBusyState = USART_BUSY_IN_RX;

		//Implement the code to enable interrupt for RXNE
		pUSARTHandle->pUSARTx->CR1 |= (1 << USART_CR1_RXNEIE);

	}

	return rxstate;

}

