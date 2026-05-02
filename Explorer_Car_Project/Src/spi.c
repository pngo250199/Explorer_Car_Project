/*
 * SPI.c
 *
 *  Created on: Apr 5, 2026
 *      Author: Froze
 */
#include "spi.h"
#define SR_TXE 0x1
#define SR_RXNE 0x0
#define SR_BSY 0x7
#define SPI1EN 0x12
#define GPIOBEN 0x02

void SPI_init(void)
{
	//RCC for GPIOA
    RCC->AHB1ENR |= GPIOBEN;
    //RCC for SPI1
   // RCC->APB2ENR |= SPI1EN;

  
    //set PB 1 and 2 for alternate function pins
    GPIOB->MODER &= ~((3U << (1 * 2)) | (3U << (2 * 2)));; //clear bit for PB 1 and 2
    GPIOB->MODER |= ((2U << (1 * 2)) | (2U << (2 * 2))); //set bit for PB 1 and 2


    //set PA9 for output
    GPIOB -> MODER &= ~(3U << (9 * 2));
    GPIOB -> MODER |= (1U << (9*2));


    //bit 0 to 7 using AFR 0
    GPIOB -> AFR[0] &= ~((0xF << (1*4)) | (0xF << (2*4))); // clear AFR for GPIOB 1 and 2
    GPIOB -> AFR[0] |= ((1 << (1*4)) | (2 << (2*4)));  //set AFR for GPIOB 1 and 2

}

void SPI1_config(void)
{
    // 1. Enable clock for SPI1
    RCC->APB2ENR |= SPI1EN; // SPI1EN

    // 2. Configure as MASTER
    SPI1->CR1 |= (1 << 2); // MSTR = 1

    // 3. Set baud rate = fPCLK / 4
    SPI1->CR1 &= ~(7 << 3); // clear BR[5:3]
    SPI1->CR1 |=  (1 << 3); // 001

    // 4. CPOL = 0, CPHA = 0 (Mode 0)
    SPI1->CR1 &= ~(1 << 1); // CPOL = 0
    SPI1->CR1 &= ~(1 << 0); // CPHA = 0

    // 5. Full duplex (2-line)
    SPI1->CR1 &= ~(1 << 15); // BIDIMODE = 0
    SPI1->CR1 &= ~(1 << 10); // RXONLY = 0

    // 6. Software slave management
    SPI1->CR1 |= (1 << 9); // SSM = 1
    SPI1->CR1 |= (1 << 8); // SSI = 1

    // 7. Data frame = 8-bit
    SPI1->CR1 &= ~(1 << 11); // DFF = 0

    // 8. Enable SPI
    SPI1->CR1 |= (1 << 6); // SPE = 1
}

void spi1_receive(uint8_t *data,uint32_t size)
{
	while(size)
	{
		/*Send dummy data*/
		SPI1->DR =0;

		/*Wait for RXNE flag to be set*/
		while(!(SPI1->SR & (SR_RXNE))){}

		/*Read data from data register*/
		*data++ = (SPI1->DR);
		size--;
	}
}


void cs_enable(void)
{
	GPIOA->ODR &=~(1U<<9);

}

/*Pull high to disable*/
void cs_disable(void)
{
	GPIOA->ODR |=(1U<<9);
}
