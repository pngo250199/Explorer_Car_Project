#include "stm32f1xx.h"
#include "spi.h"

void spi1_init(void)
{
    /* Enable GPIOA and SPI1 clocks */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    /*
     * PA5 = SCK
     * PA7 = MOSI
     *
     * Alternate-function push-pull
     * 10 MHz output
     */

    GPIOA->CRL &= ~((0xFU << (5 * 4)) |
                    (0xFU << (7 * 4)));

    GPIOA->CRL |=  ((0x9U << (5 * 4)) |
                    (0x9U << (7 * 4)));

    /*
     * PA6 = MISO
     * Floating input
     */

    GPIOA->CRL &= ~(0xFU << (6 * 4));
    GPIOA->CRL |=  (0x4U << (6 * 4));

    /*
     * PA4 = software-controlled CS
     * General-purpose push-pull
     */

    GPIOA->CRL &= ~(0xFU << (4 * 4));
    GPIOA->CRL |=  (0x2U << (4 * 4));

    /* CS inactive */
    GPIOA->BSRR = GPIO_BSRR_BS4;

    /* Master */
    SPI1->CR1 |= SPI_CR1_MSTR;

    /* Baud = PCLK2 / 4 */
    SPI1->CR1 &= ~SPI_CR1_BR;
    SPI1->CR1 |= SPI_CR1_BR_0;

    /* Mode 0 */
    SPI1->CR1 &= ~(SPI_CR1_CPOL | SPI_CR1_CPHA);

    /* Software slave management */
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;

    /* Enable SPI */
    SPI1->CR1 |= SPI_CR1_SPE;
}

void spi1_transmit(uint8_t *data, uint32_t size)
{
    while (size)
    {
        while (!(SPI1->SR & SPI_SR_TXE))
        {
        }

        *((volatile uint8_t *)&SPI1->DR) = *data++;

        size--;
    }

    while (!(SPI1->SR & SPI_SR_TXE))
    {
    }

    while (SPI1->SR & SPI_SR_BSY)
    {
    }
}

void spi1_receive(uint8_t *data, uint32_t size)
{
    while (size)
    {
        /* Wait until transmit buffer is empty */
        while (!(SPI1->SR & SPI_SR_TXE))
        {
        }

        /* Dummy byte generates clock */
        *((volatile uint8_t *)&SPI1->DR) = 0xFF;

        /* Wait for received byte */
        while (!(SPI1->SR & SPI_SR_RXNE))
        {
        }

        *data++ = *((volatile uint8_t *)&SPI1->DR);

        size--;
    }

    while (SPI1->SR & SPI_SR_BSY)
    {
    }
}

void cs_enable(void)
{
    GPIOA->BSRR = GPIO_BSRR_BR4;
}

void cs_disable(void)
{
    GPIOA->BSRR = GPIO_BSRR_BS4;
}