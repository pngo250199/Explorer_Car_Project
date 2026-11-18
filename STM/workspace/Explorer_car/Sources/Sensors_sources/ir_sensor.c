#include "stm32f1xx.h"
#include "ir_sensor.h"

void ir_sensor_init(void)
{
    /*
     * Enable GPIOB clock.
     */
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    /*
     * PB0:
     *
     * MODE0 = 00 -> Input
     * CNF0  = 10 -> Input with pull-up / pull-down
     *
     * 1000 = 0x8
     */
    GPIOB->CRL &= ~(0xFU << 0);
    GPIOB->CRL |=  (0x8U << 0);

    /*
     * ODR bit = 1 selects pull-up.
     */
    GPIOB->ODR |= (1U << 0);
}


uint8_t ir_obstacle_detected(void)
{
    /*
     * Button / IR signal is active-low.
     *
     * PB0 = 1 -> clear
     * PB0 = 0 -> obstacle
     */
    if ((GPIOB->IDR & (1U << 0)) == 0U)
    {
        return 1U;
    }

    return 0U;
}