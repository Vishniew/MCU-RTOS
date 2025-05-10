/*
 * stm32f7xx.h
 *
 *  Created on: Dec 31, 2024
 *      Author: packetp
 */

#ifndef INC_STM32F7XX_H_
#define INC_STM32F7XX_H_
#include <stdint.h>
#include <stddef.h>

#define __weak __attribute__((weak));
/*******************************************************************************************************
 * 			START : Processor specific details
 *
 * 		ARM Cortex Mx processor NVIC ISERx register addresses
 ********************************************************************************************************/

#define NVIC_ISER0				((__vo uint32_t *)0xE000E100)
#define NVIC_ISER1				((__vo uint32_t *)0xE000E104)
#define NVIC_ISER2				((__vo uint32_t *)0xE000E108)
#define NVIC_ISER3				((__vo uint32_t *)0xE000E10C)

/*
 * ARM Cortex Mx processor NVIC ICERx register addresses
 */

#define NVIC_ICER0				((__vo uint32_t *)0xE000E180)
#define NVIC_ICER1				((__vo uint32_t *)0xE000E184)
#define NVIC_ICER2				((__vo uint32_t *)0xE000E188)
#define NVIC_ICER3				((__vo uint32_t *)0xE000E18C)


/*
 * ARM Cortex Mx processor NVIC Priority register addresses
 */

#define NVIC_PR_BASE_AADR				((__vo uint32_t *)0xE000E400)

/*
 * ARM Cortex Mx processor no of priority bits implemented
 */

#define NO_PR_BITS_IMPLEMENTED			4

#define __vo volatile





#define FLASH_BASE				0x08000000U		//Base address of Flash memory
#define SRAM1_BASE				0x20000000U		//Base address of SRAM1 memory
#define SRAM2_BASE				0x2003C000U		//Base address of SRAM2 memory
#define SRAM					SRAM1_BASE		//Base address of SRAM memory
#define ROM						0x1FF00000U		//Base address of ROM memory

/*AHBx and APBx Bus peripheral base address*/

#define PERIPH_BASE				0x40000000U
#define APB1PERIPH_BASE			0x40000000U
#define APB2PERIPH_BASE			0x40010000U
#define AHB1PERIPH_BASE			0x40020000U
#define AHB2PERIPH_BASE			0x50000000U

/*Base address of RCC peripheral*/
#define RCC_BASE					(AHB1PERIPH_BASE + 0x3800)


/*Base address for peripherals which are hanging on AHB1 bus*/

#define GPIOA_BASE				(AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASE				(AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASE				(AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASE				(AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASE				(AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASE				(AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASE				(AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASE				(AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASE				(AHB1PERIPH_BASE + 0x2000)


/*Base address for peripherals which are hanging on APB1 bus*/
#define I2C1_BASE				(APB1PERIPH_BASE + 0x5400)
#define I2C2_BASE				(APB1PERIPH_BASE + 0x5800)
#define I2C3_BASE				(APB1PERIPH_BASE + 0x5C00)

#define SPI2_BASE				(APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE				(APB1PERIPH_BASE + 0x3C00)

#define UART4_BASE				(APB1PERIPH_BASE + 0x4C00)
#define UART5_BASE				(APB1PERIPH_BASE + 0x5000)

#define USART2_BASE				(APB1PERIPH_BASE + 0x4400)
#define USART3_BASE				(APB1PERIPH_BASE + 0x4800)


/*Base address for peripherals which are hanging on APB2 bus*/

#define EXTI_BASE				(APB2PERIPH_BASE + 0x3C00)

#define SPI1_BASE				(APB2PERIPH_BASE + 0x3000)
#define SYSCFG_BASE			(APB2PERIPH_BASE + 0x3800)

#define USART1_BASE				(APB2PERIPH_BASE + 0x1000)
#define USART6_BASE				(APB2PERIPH_BASE + 0x1400)


#define TIM2_BASE				(APB1PERIPH_BASE + 0x0000)


/*Base Address Structure for GPIO */
typedef struct
{
	__vo uint32_t MODER;				/*GPIO port mode register					Address offset 0x00*/
	__vo uint32_t OTYPER;			/*GPIO port output type register			Address offset 0x04*/
	__vo uint32_t SPEEDR;			/*GPIO port output speed register			Address offset 0x08*/
	__vo uint32_t PUPDR;				/*GPIO port pull-up/pull-down register		Address offset 0x0C*/
	__vo uint32_t IDR;				/*GPIO port input data register				Address offset 0x10*/
	__vo uint32_t ODR;				/*GPIO port output data register			Address offset 0x14*/
	__vo uint32_t BSRR;				/*GPIO port bit set/reset register			Address offset 0x18*/
	__vo uint32_t LCKR;				/*GPIO port configuration lock register		Address offset 0x1C*/
	__vo uint32_t AFR[2];				/*GPIO alternate function low & high registers		Address offset 0x20, 0x24*/

}GPIO_RegDef_t;

/*peripheral definitons   (Peripheral base typecasted to xxx_RegDef_t)*/

#define GPIOA					((GPIO_RegDef_t *)GPIOA_BASE)
#define GPIOB					((GPIO_RegDef_t *)GPIOB_BASE)
#define GPIOC					((GPIO_RegDef_t *)GPIOC_BASE)
#define GPIOD					((GPIO_RegDef_t *)GPIOD_BASE)
#define GPIOE					((GPIO_RegDef_t *)GPIOE_BASE)
#define GPIOF					((GPIO_RegDef_t *)GPIOF_BASE)
#define GPIOG					((GPIO_RegDef_t *)GPIOG_BASE)
#define GPIOH					((GPIO_RegDef_t *)GPIOH_BASE)
#define GPIOI					((GPIO_RegDef_t *)GPIOI_BASE)


/*Peripheral Register definition Structure for RCC */
typedef struct
{
	__vo uint32_t CR;				/*RCC clock control register				Address offset 0x00*/
	__vo uint32_t PLLCFGR;			/*RCC PLL configuration register			Address offset 0x04*/
	__vo uint32_t CFGR;			/*RCC clock configuration register				Address offset 0x08*/
	__vo uint32_t CIR;				/*RCC clock interrupt register				Address offset 0x0C*/
	__vo uint32_t AHB1RSTR;				/*RCC AHB1 peripheral reset register	Address offset 0x10*/
	__vo uint32_t AHB2RSTR;				/*RCC AHB2 peripheral reset register			Address offset 0x14*/
	__vo uint32_t AHB3RSTR;				/*RCC AHB3 peripheral reset register		Address offset 0x18*/
		 uint32_t RESERVED0;					/*Reserved : 0x1C*/
	__vo uint32_t APB1RSTR;				/*RCC APB1 peripheral reset register	Address offset 0x20*/
	__vo uint32_t APB2RSTR;				/*RCC APB2 peripheral reset register	Address offset 0x24*/
	 	 uint32_t RESERVED1[2];					/*Reserved : 0x28, 0x2C*/
	__vo uint32_t AHB1ENR;				/*RCC AHB1 peripheral clock register	Address offset 0x30*/
	__vo uint32_t AHB2ENR;				/*RCC AHB2 peripheral clock register	Address offset 0x34*/
	__vo uint32_t AHB3ENR;				/*RCC AHB3 peripheral clock register		Address offset 0x38*/
	 	 uint32_t RESERVED2;					/*Reserved : 0x3C*/

	__vo uint32_t APB1ENR;				/*RCC APB1 peripheral clock register		Address offset 0x40*/
	__vo uint32_t APB2ENR;				/*RCC APB2 peripheral clock register		Address offset 0x44*/
	 uint32_t RESERVED3[2];					/*Reserved : 0x48,0x4C*/

	__vo uint32_t AHB1LPENR;	/*RCC AHB1 peripheral clock enable in low-power mode register	Address offset 0x50*/
	__vo uint32_t AHB2LPENR;	/*RCC AHB2 peripheral clock enable in low-power mode register		Address offset 0x54*/
	__vo uint32_t AHB3LPENR;	/*RCC AHB3 peripheral clock enable in low-power mode register		Address offset 0x58*/
	 uint32_t RESERVED4;				/*Reserved : 0x5C*/

	__vo uint32_t APB1LPENR;	/*RCC APB1 peripheral clock enable in low-power mode register		Address offset 0x60*/
	__vo uint32_t APB2LPENR;	/*RCC APB2 peripheral clock enable in low-power mode register		Address offset 0x64*/
	 uint32_t RESERVED5[2];					/*Reserved : 0x68,0x6C*/

	 __vo uint32_t BDCR;				/*RCC backup domain control register		Address offset 0x70*/
	 __vo uint32_t CSR;					/*RCC clock control & status register		Address offset 0x74*/
	 uint32_t RESERVED6[2];				/*Reserved : 0x78,0x7C*/
	 __vo uint32_t SSCGR;				/*RCC spread spectrum clock generation register		Address offset 0x80*/
	 __vo uint32_t PLLI2SCFGR;			/*RCC PLLI2S configuration register					Address offset 0x84*/
	 __vo uint32_t PLLSAICFGR;			/*RCC PLLSAI configuration register					Address offset 0x88*/
	 __vo uint32_t DCKCFGR1;			/*RCC dedicated clocks configuration register1		Address offset 0x8C*/
	 __vo uint32_t DCKCFGR2;			/*RCC dedicated clocks configuration register2		Address offset 0x90*/



}RCC_RegDef_t;

/*Peripheral Register definition Structure for EXTI*/

typedef struct
{
	__vo uint32_t IMR;				/*Interrupt mask register				Address offset 0x00*/
	__vo uint32_t EMR;			/*Event mask register			Address offset 0x04*/
	__vo uint32_t RTSR;			/*Rising trigger selection register 		Address offset 0x08*/
	__vo uint32_t FTSR;				/*Falling trigger selection register		Address offset 0x0C*/
	__vo uint32_t SWIER;				/*Software interrupt event register			Address offset 0x10*/
	__vo uint32_t PR;				/*Pending register			Address offset 0x14*/

}EXTI_RegDef_t;


/*Peripheral Register definition Structure for SPIx*/

typedef struct
{
	__vo uint32_t CR1;			/*SPI control register 1         Address offset 0x00*/
	__vo uint32_t CR2;			/*SPI control register 2         Address offset 0x04*/
	__vo uint32_t SR;			/*SPI status register        Address offset 0x08*/
	__vo uint32_t DR;			/*SPI data register         Address offset 0x0C*/
	__vo uint32_t CRCPR;			/*SPI CRC polynomial register        Address offset 0x10*/
	__vo uint32_t RXCRCR;			/*SPI Rx CRC register        Address offset 0x14*/
	__vo uint32_t TXCRCR;			/*SPI Tx CRC register        Address offset 0x18*/
	__vo uint32_t I2SCFGR;			/*SPIx_I2S configuration register        Address offset 0x1C*/
	__vo uint32_t I2SPR;			/*SPIx_I2S prescaler register         Address offset 0x20*/

}SPI_RegDef_t;

/*Peripheral Register definition Structure for I2C*/


typedef struct
{
	__vo uint32_t CR1;				/*I2C2 control register 1 */
	__vo uint32_t CR2;				/*I2C2 control register 2 */
	__vo uint32_t OAR1;				/*I2C2 own address 1 register*/
	__vo uint32_t OAR2;				/*I2C2 own address 2 register*/
	__vo uint32_t TIMINGR;			/*I2C2 timing register*/
	__vo uint32_t TIMOUTR;			/*I2C2 time out register*/
	__vo uint32_t ISR;				/*I2C2 interrupt and status register*/
	__vo uint32_t ICR;				/*I2C2 interrupt clear register*/
	__vo uint32_t PECR;				/*I2C2 PEC register*/
	__vo uint32_t RXDR;				/*I2C2 receive data register*/
	__vo uint32_t TXDR;				/*I2C2 transmit data register*/


}I2C_RegDef_t;

/*Peripheral Register definition Structure for USART*/
typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t CR3;
	__vo uint32_t BRR;
	__vo uint32_t GTPR;
	__vo uint32_t RTOR;
	__vo uint32_t RQR;
	__vo uint32_t ISR;
	__vo uint32_t ICR;
	__vo uint32_t RDR;
	__vo uint32_t TDR;

}USART_RegDef_t;

/*Peripheral Register definition Structure for SYSCFG*/

typedef struct
{
	__vo uint32_t MEMRMP;				/*SYSCFG memory remap register				Address offset 0x00*/
	__vo uint32_t PMC;					/*SYSCFG peripheral mode configuration register			Address offset 0x04*/
	__vo uint32_t EXTICR[4];	/*SYSCFG external interrupt configuration register 1,2,3,4 	Address offset 0x08,0x14*/
	uint32_t Reserved1[2];					/*Reserved 0x18,0x1C    */
	__vo uint32_t CMPCR;				/*Compensation cell control register			Address offset 0x20*/
	//uint32_t Reserved2[2];				/*Reserved 0x24,0x28    */
	//__vo uint32_t CFGR;				/*			Address offset 0x2C*/

}SYSCFG_RegDef_t;







/*peripheral definitons   (Peripheral base typecasted to xxx_RegDef_t)*/
#define RCC					((RCC_RegDef_t *)RCC_BASE)
#define EXTI				((EXTI_RegDef_t *)EXTI_BASE)
#define SYSCFG				((SYSCFG_RegDef_t *)SYSCFG_BASE)



#define SPI1				((SPI_RegDef_t *)SPI1_BASE)
#define SPI2				((SPI_RegDef_t *)SPI2_BASE)
#define SPI3				((SPI_RegDef_t *)SPI3_BASE)

#define I2C1				((I2C_RegDef_t *)I2C1_BASE)
#define I2C2				((I2C_RegDef_t *)I2C2_BASE)
#define I2C3				((I2C_RegDef_t *)I2C3_BASE)

#define USART1				((USART_RegDef_t *)USART1_BASE)
#define USART2				((USART_RegDef_t *)USART2_BASE)
#define USART3				((USART_RegDef_t *)USART3_BASE)
#define USART6				((USART_RegDef_t *)USART6_BASE)



#define TIM2				((__vo uint32_t *)TIM2_BASE)

/*Clock enable MACROs for GPIOx peripherals*/
#define GPIOA_PCLK_EN()		(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()		(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()		(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()		(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()		(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()		(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()		(RCC->AHB1ENR |= (1 << 7))
#define GPIOI_PCLK_EN()		(RCC->AHB1ENR |= (1 << 8))

/*Clock enable MACROs for I2Cx peripherals*/

#define I2C1_PCLK_EN()		(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()		(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()		(RCC->APB1ENR |= (1 << 23))

/*Clock enable MACROs for SPIx peripherals*/

#define SPI1_PCLK_EN()		(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()		(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()		(RCC->APB1ENR |= (1 << 15))


/*Clock enable MACROs for USARTx peripherals*/
#define USART1_PCLK_EN()		(RCC->APB2ENR |= (1 << 4))

#define USART2_PCLK_EN()		(RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()		(RCC->APB1ENR |= (1 << 18))




/*Clock enable MACROs for SYSCFG peripherals*/

#define SYSCFG_PCLK_EN()		(RCC->APB2ENR |= (1 << 14))

/*Clock disable MACROs for GPIOx peripherals*/
#define GPIOA_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_PCLK_DI()		(RCC->AHB1ENR &= ~(1 << 8))

/*Clock disable MACROs for I2Cx peripherals*/

#define I2C1_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 23))

/*Clock disable MACROs for SPIx peripherals*/

#define SPI1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 15))


/*Clock disable MACROs for USART peripherals*/
#define USART1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 4))

#define USART2_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 18))




/*Clock disable MACROs for SYSCFG peripherals*/

#define SYSCFG_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 14))

/*
 * MACROS to RESET GPIO peripherals
 */
#define GPIOA_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 0)); (RCC -> AHB1RSTR &= ~(1<<0));} while(0)
#define GPIOB_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 1)); (RCC -> AHB1RSTR &= ~(1<<1));} while(0)
#define GPIOC_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 2)); (RCC -> AHB1RSTR &= ~(1<<2));} while(0)
#define GPIOD_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 3)); (RCC -> AHB1RSTR &= ~(1<<3));} while(0)
#define GPIOE_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 4)); (RCC -> AHB1RSTR &= ~(1<<4));} while(0)
#define GPIOF_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 5)); (RCC -> AHB1RSTR &= ~(1<<5));} while(0)
#define GPIOG_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 6)); (RCC -> AHB1RSTR &= ~(1<<6));} while(0)
#define GPIOH_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 7)); (RCC -> AHB1RSTR &= ~(1<<7));} while(0)
#define GPIOI_REG_RESET()		do{(RCC->AHB1RSTR |= (1 << 8)); (RCC -> AHB1RSTR &= ~(1<<8));} while(0)



/*
 * MACROS to RESET SPI peripherals
 */
#define SPI1_REG_RESET()		do{(RCC->APB2ENR |= (1 << 12));(RCC->APB2ENR &= ~(1 << 12));} while(0)
#define SPI2_REG_RESET()		do{(RCC->APB1ENR |= (1 << 13));(RCC->APB2ENR &= ~(1 << 13));} while(0)
#define SPI3_REG_RESET()		do{(RCC->APB1ENR |= (1 << 14));(RCC->APB2ENR &= ~(1 << 14));} while(0)

/*
 * MACROS to RESET SPI peripherals
 */

#define USART1_REG_RESET()		do{(RCC->APB2ENR |= (1 << 4));(RCC->APB2ENR &= ~(1 << 4));} while(0)
#define USART2_REG_RESET()		do{(RCC->APB2ENR |= (1 << 17));(RCC->APB2ENR &= ~(1 << 17));} while(0)
#define USART3_REG_RESET()		do{(RCC->APB2ENR |= (1 << 18));(RCC->APB2ENR &= ~(1 << 18));} while(0)







/*
 * Base address to code of given GPIOx
 */

#define GPIO_BASEADDR_TO_CODE(x)		((x == GPIOA) ? 0:\
										(x == GPIOB) ? 1:\
										(x == GPIOC) ? 2:\
										(x == GPIOD) ? 3:\
										(x == GPIOE) ? 4:\
										(x == GPIOF) ? 5:\
										(x == GPIOG) ? 6:\
										(x == GPIOH) ? 7:\
										(x == GPIOI) ? 8:0)


/*
 * IRQ numbers
 */

#define IRQ_NO_EXTI0			6
#define IRQ_NO_EXTI1			7
#define IRQ_NO_EXTI2			8
#define IRQ_NO_EXTI3			9
#define IRQ_NO_EXTI4			10
#define IRQ_NO_EXTI9_5			23
#define IRQ_NO_EXTI15_10		40

#define IRQ_NO_USART1			37
#define IRQ_NO_USART2			38
#define IRQ_NO_USART3			39

/*
 * IRQ numbers for SPIx
 */

#define IRQ_NO_SPI1			35
#define IRQ_NO_SPI2			36
#define IRQ_NO_SPI3			51






/*
 * MACROS for all the priority levels
 */

#define NVIC_IRQ_PRI0			0
#define NVIC_IRQ_PRI1			1
#define NVIC_IRQ_PRI2			2
#define NVIC_IRQ_PRI3			3
#define NVIC_IRQ_PRI4			4
#define NVIC_IRQ_PRI5			5
#define NVIC_IRQ_PRI6			6
#define NVIC_IRQ_PRI7			7
#define NVIC_IRQ_PRI8			8
#define NVIC_IRQ_PRI9			9
#define NVIC_IRQ_PRI10			10
#define NVIC_IRQ_PRI11			11
#define NVIC_IRQ_PRI12			12
#define NVIC_IRQ_PRI13			13
#define NVIC_IRQ_PRI14			14
#define NVIC_IRQ_PRI15			15


/*
 * Some generic Macros
 */

#define ENABLE				1
#define DISABLE				0

#define SET					1
#define RESET				0

#define GPIO_PIN_SET		1
#define GPIO_PIN_RESET		0

#define FLAG_RESET			RESET
#define FLAG_SET			SET

/***************************************************************************************************************
 * *************************Bit position definitons of SPI peripheral*****************************************
 *****************************************************************************************************************/


/*
 * CR1
 */
#define SPI_CR1_CPHA		0
#define SPI_CR1_CPOL		1
#define SPI_CR1_MSTR		2
#define SPI_CR1_BR			3
#define SPI_CR1_SPE			6
#define SPI_CR1_LSBFIRST	7
#define SPI_CR1_SSI			8
#define SPI_CR1_SSM			9
#define SPI_CR1_RXONLY		10
#define SPI_CR1_CRCL		11
#define SPI_CR1_CRCNEXT		12
#define SPI_CR1_CRCEN		13
#define SPI_CR1_BIDIOE		14
#define SPI_CR1_BIDIMODE	15

/*
 * CR2
 */

#define SPI_CR2_RXDMAEN		0
#define SPI_CR2_TXDMAEN		1
#define SPI_CR2_SSOE		2
#define SPI_CR2_NSSP		3
#define SPI_CR2_FRF			4
#define SPI_CR2_EERIE		5
#define SPI_CR2_RXNEIE		6
#define SPI_CR2_TXEIE		7
#define SPI_CR2_DS			8
#define SPI_CR2_FRXTH		12
#define SPI_CR2_LDMA_RX		13
#define SPI_CR2_LDMA_TX		14

/*
 * Status register
 */

#define SPI_SR_RXNE		0
#define SPI_SR_TXE		1
#define SPI_SR_CHSIDE	2
#define SPI_SR_UDR		3
#define SPI_SR_CRCERR	4
#define SPI_SR_MODF		5
#define SPI_SR_OVR		6
#define SPI_SR_BSY		7
#define SPI_SR_FRE		8
#define SPI_SR_FRLVL	9
#define SPI_SR_FTLVL	11



/***************************************************************************************************************
 * *************************Bit position definitons of I2C peripheral*****************************************
 *****************************************************************************************************************/


/*
 * I2C CR1
 */

#define I2C_CR1_PE		0
#define I2C_CR1_TXIE	1
#define I2C_CR1_RXIE	2
#define I2C_CR1_ADDRIE	3
#define I2C_CR1_NACKIE	4
#define I2C_CR1_STOPIE	5
#define I2C_CR1_TCIE	6
#define I2C_CR1_ERRIE	7
#define I2C_CR1_TXDMAEN	14
#define I2C_CR1_RXDMAEN	15
#define I2C_CR1_SBC		16
#define I2C_CR1_NOSTRETCH	17

/*
 * I2C CR2
 */

#define I2C_CR2_RD_WRN		10
#define I2C_CR2_ADD10		11
#define I2C_CR2_HEAD10R		12
#define I2C_CR2_START		13
#define I2C_CR2_STOP		14
#define I2C_CR2_NACK		15
#define I2C_CR2_RELOAD		24
#define I2C_CR2_AUTOEND		25
#define I2C_CR2_PECBYTE		26


/*
 * I2C SR
 */
#define I2C_SR_TXE			0
#define I2C_SR_TXIS			1
#define I2C_SR_RXNE			2
#define I2C_SR_ADDR			3
#define I2C_SR_NACKF		4
#define I2C_SR_STOPF		5
#define I2C_SR_TC			6
#define I2C_SR_TCR			7
#define I2C_SR_BERR			8
#define I2C_SR_ARLO			9
#define I2C_SR_OVR			10
#define I2C_SR_PECERR		11
#define I2C_SR_TIMEOUT		12
#define I2C_SR_ALERT		13
#define I2C_SR_BUSY		15
#define I2C_SR_DIR		16

/***************************************************************************************************************
 * *************************Bit position definitons of SPI peripheral*****************************************
 *****************************************************************************************************************/

/*
 * USART_CR1
 */

#define USART_CR1_UE		0
#define USART_CR1_RE		2
#define USART_CR1_TE		3
#define USART_CR1_IDLEIE	4
#define USART_CR1_RXNEIE	5
#define USART_CR1_TCIE		6
#define USART_CR1_TXEIE		7
#define USART_CR1_PEIE		8
#define USART_CR1_PS		9
#define USART_CR1_PCE		10
#define USART_CR1_WAKE		11
#define USART_CR1_M0		12
#define USART_CR1_MME		13
#define USART_CR1_CMIE		14
#define USART_CR1_OVER8		15
#define USART_CR1_DEDT		16
#define USART_CR1_DEAT		21
#define USART_CR1_RTOIE		26
#define USART_CR1_EOBIE		27
#define USART_CR1_M1		28


/*
 * USART_CR2
 */

#define USART_CR2_STOP 		12

/*
 * USART_CR3
 */

#define USART_CR3_RTSE		8
#define USART_CR3_CTSE		9

/*
 * USART_BRR
 */

#define USART_BRR_BRR		0

/*
 * USART_ISR
 */

#define USART_ISR_PE		0
#define USART_ISR_FE		1
#define USART_ISR_ORE		3
#define USART_ISR_IDLE		4
#define USART_ISR_RXNE		5
#define USART_ISR_TC		6
#define USART_ISR_TXE		7

/*
 * USART_ICR
 */

#define USART_ICR_TCCF		6



#include "stm32f7xx_gpio_driver.h"
#include "stm32f7xx_spi_driver.h"
#include "stm32f7xx_i2c_driver.h"
#include "stm32f7xx_usart_driver.h"
#include "stm32f7xx_rcc_driver.h"

#endif
