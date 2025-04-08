#include "stm32f7xx.h"

// AHB Prescaler Lookup Table (From STM32F7 Reference Manual)
const uint8_t AHB_PreScaler[8] = {2, 4, 8, 16, 64, 128, 256, 512};

// APB Prescaler Lookup Table
const uint8_t APB_PreScaler[4] = {2, 4, 8, 16};

// Function to Get PCLK1 (APB1 Clock) Value
uint32_t RCC_GetPCLK1Value(void)
{
    uint32_t pclk1, SystemClk;
    uint8_t clksrc, temp, ahbp, apb1p;

    // Get System Clock Source (Bits 3:2 of RCC_CFGR)
    clksrc = ((RCC->CFGR >> 2) & 0x3);

    if (clksrc == 0)
    {
        SystemClk = 16000000; // HSI
    }
    else if (clksrc == 1)
    {
        SystemClk = 8000000;  // HSE
    }
    /*else if (clksrc == 2)
    {
        SystemClk = RCC_GetPLLOutputClock(); // PLL (Needs Calculation)
    }*/

    // Get AHB Prescaler (Bits 7:4 of RCC_CFGR)
    temp = ((RCC->CFGR >> 4) & 0xF);
    if (temp < 8)
    {
        ahbp = 1;
    }
    else
    {
        ahbp = AHB_PreScaler[temp - 8]; // Use Lookup Table
    }

    // Get APB1 Prescaler (Bits 12:10 of RCC_CFGR)
    temp = ((RCC->CFGR >> 10) & 0x7);
    if (temp < 4)
    {
        apb1p = 1;
    }
    else
    {
        apb1p = APB_PreScaler[temp - 4]; // Use Lookup Table
    }

    // Compute PCLK1
    pclk1 = (SystemClk / ahbp) / apb1p;

    // If APB1 prescaler > 1, USART clock is doubled
    if (apb1p > 1)
    {
        pclk1 *= 2;
    }

    return pclk1;
}

// Function to Get PCLK2 (APB2 Clock) Value (For USART1, USART6)
uint32_t RCC_GetPCLK2Value(void)
{
    uint32_t pclk2, SystemClk;
    uint8_t clksrc, temp, ahbp, apb2p;

    // Get System Clock Source (Bits 3:2 of RCC_CFGR)
    clksrc = ((RCC->CFGR >> 2) & 0x3);

    if (clksrc == 0)
    {
        SystemClk = 16000000; // HSI
    }
    else if (clksrc == 1)
    {
        SystemClk = 8000000;  // HSE
    }
    /*else if (clksrc == 2)
    {
        SystemClk = RCC_GetPLLOutputClock(); // PLL (Needs Calculation)
    }*/

    // Get AHB Prescaler (Bits 7:4 of RCC_CFGR)
    temp = ((RCC->CFGR >> 4) & 0xF);
    if (temp < 8)
    {
        ahbp = 1;
    }
    else
    {
        ahbp = AHB_PreScaler[temp - 8]; // Use Lookup Table
    }

    // Get APB2 Prescaler (Bits 15:13 of RCC_CFGR)
    temp = ((RCC->CFGR >> 13) & 0x7);
    if (temp < 4)
    {
        apb2p = 1;
    }
    else
    {
        apb2p = APB_PreScaler[temp - 4]; // Use Lookup Table
    }

    // Compute PCLK2
    pclk2 = (SystemClk / ahbp) / apb2p;

    // If APB2 prescaler > 1, USART clock is doubled
    if (apb2p > 1) {
        pclk2 *= 2;
    }

    return pclk2;
}
