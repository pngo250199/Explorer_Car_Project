#include "stm32f1xx.h"
#include "SysTick.h"

void systick_delay(uint32_t delay)
{
    /* Number of CPU clocks per millisecond */
    SysTick->LOAD = (SystemCoreClock / 1000U) - 1U;

    /* Clear current counter */
    SysTick->VAL = 0U;

    /* Processor clock + enable SysTick */
    SysTick->CTRL =
        SysTick_CTRL_CLKSOURCE_Msk |
        SysTick_CTRL_ENABLE_Msk;

    for (uint32_t i = 0; i < delay; i++)
    {
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0U)
        {
        }
    }

    SysTick->CTRL = 0U;
}