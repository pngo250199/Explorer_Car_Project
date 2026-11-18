#include <stdint.h>
#include "stm32f1xx.h"
#include "uart1.h"

void uart1_init(void)
{
    /*
     * GPIOA and USART1 are both on APB2
     */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    /*
     * PA9 = USART1_TX
     *
     * PA9 is in GPIOA->CRH.
     * PA9 uses bits 7:4.
     *
     * CNF9  = 10 -> Alternate function push-pull
     * MODE9 = 11 -> Output 50 MHz
     *
     * 1011 = 0xB
     */
    GPIOA->CRH &= ~(0xFU << 4);
    GPIOA->CRH |=  (0xBU << 4);

    /*
     * PA10 = USART1_RX
     *
     * PA10 uses CRH bits 11:8.
     *
     * CNF10  = 01 -> Floating input
     * MODE10 = 00 -> Input
     *
     * 0100 = 0x4
     */
    GPIOA->CRH &= ~(0xFU << 8);
    GPIOA->CRH |=  (0x4U << 8);

    /*
     * Assuming PCLK2 = 8 MHz
     * Baud = 115200
     */
    USART1->BRR = 0x45U;

    /*
     * Enable TX, RX and USART
     */
    USART1->CR1 =
        USART_CR1_TE |
        USART_CR1_RE |
        USART_CR1_UE;
}

void uart1_transmit(char data)
{
    while (!(USART1->SR & USART_SR_TXE))
    {
    }

    USART1->DR = (uint8_t)data;
}

char uart1_receive(void)
{
    while (!(USART1->SR & USART_SR_RXNE))
    {
    }

    return (char)(USART1->DR & 0xFFU);
}

void uart1_print(const char *str)
{
    while (*str)
    {
        uart1_transmit(*str++);
    }
}