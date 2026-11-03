#include "stm32f1xx.h"
#include "tim.h"

void tim3_init(void)
{
    /* Enable TIM3 clock */
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    /*
     * Assuming TIM3 clock = 8 MHz
     *
     * 8 MHz / 8000 = 1 kHz
     * 1 tick = 1 ms
     */

    TIM3->PSC = 8000U - 1U;

    /*
     * Overflow every 1000 ticks
     * = 1000 ms = 1 second
     */

    TIM3->ARR = 1000U - 1U;

    TIM3->CNT = 0U;

    /* Enable timer */
    TIM3->CR1 |= TIM_CR1_CEN;
}