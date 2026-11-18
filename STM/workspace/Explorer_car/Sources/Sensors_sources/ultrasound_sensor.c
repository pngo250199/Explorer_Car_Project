#include "stm32f1xx.h"
#include "ultrasound_sensor.h"

static void delay_us(uint32_t us)
{
    TIM2->CNT = 0;

    while (TIM2->CNT < us)
    {
    }
}

void ultrasonic_init(void)
{
    /*
     * Enable GPIOB
     */
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    /*
     * Enable TIM2
     */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /*
     * PB1 = TRIG
     *
     * General purpose push-pull output
     * 2 MHz
     *
     * MODE1 = 10
     * CNF1  = 00
     *
     * PB1 = CRL bits 7:4
     */
    GPIOB->CRL &= ~(0xFU << 4);
    GPIOB->CRL |=  (0x2U << 4);

    /*
     * PB10 = ECHO
     *
     * Floating input
     *
     * MODE10 = 00
     * CNF10  = 01
     *
     * PB10 = CRH bits 11:8
     */
    GPIOB->CRH &= ~(0xFU << 8);
    GPIOB->CRH |=  (0x4U << 8);

    /*
     * Initial TRIG = LOW
     */
    GPIOB->BRR = (1U << 1);

    /*
     * TIM2:
     *
     * Assuming timer clock = 8 MHz.
     *
     * Divide by 8:
     * 8 MHz / 8 = 1 MHz
     *
     * 1 count = 1 microsecond.
     */
    TIM2->PSC = 7U;

    TIM2->ARR = 0xFFFFU;

    TIM2->CNT = 0U;

    TIM2->CR1 |= TIM_CR1_CEN;
}

uint32_t ultrasonic_read_cm(void)
{
    uint32_t echo_time;
    uint32_t timeout;

    /*
     * Make sure TRIG starts LOW.
     */
    GPIOB->BRR = (1U << 1);
    delay_us(2U);

    /*
     * Send 10 us trigger pulse.
     */
    GPIOB->BSRR = (1U << 1);
    delay_us(10U);
    GPIOB->BRR = (1U << 1);

    /*
     * Wait for ECHO to go HIGH.
     * Timeout after about 30 ms.
     */
    TIM2->CNT = 0U;

    while (!(GPIOB->IDR & (1U << 10)))
    {
        if (TIM2->CNT >= 30000U)
        {
            return 0U;
        }
    }

    /*
     * Measure ECHO HIGH time.
     */
    TIM2->CNT = 0U;

    while (GPIOB->IDR & (1U << 10))
    {
        if (TIM2->CNT >= 30000U)
        {
            return 0U;
        }
    }

    echo_time = TIM2->CNT;

    return echo_time / 58U;
}