#include <stdint.h>
#include "stm32f1xx.h"
#include "uart.h"

#define USART2_PCLK     8000000U
#define UART_BAUDRATE   115200U

void uart_init(void)
{
    /*
     * GPIOA clock enable
     */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /*
     * USART2 clock enable
     */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    /*
     * PA2 = USART2_TX
     *
     * CNF2  = 10 : Alternate function push-pull
     * MODE2 = 11 : Output, 50 MHz
     *
     * CRL bits 11:8 = 1011 = 0xB
     */
    GPIOA->CRL &= ~(0xFU << 8);
    GPIOA->CRL |=  (0xBU << 8);

    /*
     * PA3 = USART2_RX
     *
     * CNF3  = 01 : Floating input
     * MODE3 = 00 : Input
     *
     * CRL bits 15:12 = 0100 = 0x4
     */
    GPIOA->CRL &= ~(0xFU << 12);
    GPIOA->CRL |=  (0x4U << 12);

    /*
     * Baud rate
     *
     * Assuming USART2 peripheral clock = 8 MHz:
     *
     * 8,000,000 / 115,200 = 69.44
     *
     * BRR = 0x45
     */
    USART2->BRR = 0x45U;

    /*
     * Enable TX, RX and USART
     */
    USART2->CR1 |= USART_CR1_TE;
    USART2->CR1 |= USART_CR1_RE;
    USART2->CR1 |= USART_CR1_UE;
}


void uart_transmit(char data)
{
    /*
     * Wait until transmit data register is empty.
     */
    while (!(USART2->SR & USART_SR_TXE))
    {
    }

    USART2->DR = (uint8_t)data;
}


char uart_receive(void)
{
    /*
     * Wait until receive register has data.
     */
    while (!(USART2->SR & USART_SR_RXNE))
    {
    }

    return (char)(USART2->DR & 0xFFU);
}


void uart_print(const char *str)
{
    while (*str != '\0')
    {
        uart_transmit(*str);
        str++;
    }
}