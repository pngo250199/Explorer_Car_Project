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
#define GPIOAEN 0x0

void SPI_init(void)
{
	//RCC for GPIOA
    RCC->AHB1ENR |= GPIOAEN;
    //RCC for SPI1
   // RCC->APB2ENR |= SPI1EN;


    //set PA5 6 and 7 for alternate function pins
    GPIOA -> MODER &= ~((1U << 10) | (1U << 12) | (1U << 14)); //clear bit for PA5 6 and 7
    GPIOA -> MODER |= ((1U << 11) | (1U << 13) | (1U << 15)); //set bit for PA5 6 and 7


    //set PA9 for output
    GPIOA -> MODER &= (1U << 19);
    GPIOA -> MODER |= (1U << 18);


    //bit 0 to 7 using AFR 0
    GPIOA -> AFR[0] |= ((1U << 20) | (1U << 22) | (1U << 24) | (1U << 26) | (1U << 28));
    GPIOA -> AFR[0] &= ~((1U << 21) | (1U << 23) | (1U << 25) | (1U << 27) | (1U << 31));

}

void SPI1_config(void)
{
    //RCC for SPI1
    RCC->APB2ENR |= SPI1EN;

    //set clock to fPCLK/4 (frequency Peripheral Clock 0 fPCLK); Divide for 4 for slower speed
    SPI1 -> CR1 |= (1U << 3);
    SPI1 -> CR1 &= ~(1U << 4);
    SPI1 -> CR1 &= ~(1U << 5);

    //set up full duplex
    SPI1 -> CR1 &= ~ (1U << 10);

    //CPOL ( Clock Polarity) *Polarity: tích phân cực
    //CPHA
    //baud rate

}

