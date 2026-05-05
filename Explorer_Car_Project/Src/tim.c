#include "tim.h"

#define TIM2EN		(1U<<0)
#define CR1_CEN		(1U<<0)
void tim_init(void)
{
    // 1. Enable clock for TIM2
    RCC->APB1ENR |= (1 << 0); // TIM2EN


}