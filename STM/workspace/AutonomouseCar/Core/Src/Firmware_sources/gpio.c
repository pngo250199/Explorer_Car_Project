#include "gpio.h"

void gpio_init(void)
{
    /* Enable GPIOA peripheral clock */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /*
     * PA2, PA3, PA4, PA5
     * Floating input:
     *
     * MODE = 00
     * CNF  = 01
     *
     * Binary = 0100 = 0x4
     */

    GPIOA->CRL &= ~(0xFU << (2U * 4U));
    GPIOA->CRL |=  (0x4U << (2U * 4U));

    GPIOA->CRL &= ~(0xFU << (3U * 4U));
    GPIOA->CRL |=  (0x4U << (3U * 4U));

    GPIOA->CRL &= ~(0xFU << (4U * 4U));
    GPIOA->CRL |=  (0x4U << (4U * 4U));

    GPIOA->CRL &= ~(0xFU << (5U * 4U));
    GPIOA->CRL |=  (0x4U << (5U * 4U));

    /*
     * PA1
     * General-purpose push-pull output, 2 MHz
     *
     * MODE = 10
     * CNF  = 00
     *
     * Binary = 0010 = 0x2
     */

    GPIOA->CRL &= ~(0xFU << (1U * 4U));
    GPIOA->CRL |=  (0x2U << (1U * 4U));
}