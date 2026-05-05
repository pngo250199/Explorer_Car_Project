#include "tim.h"

#define TIM3EN		(1U<<1)
#define CR1_CEN		(1U<<0)
void tim_init(void)
{
    // 1. Enable clock for TIM3
    RCC->APB1ENR |= (1 << 1); // TIM3EN

    TIM3->PSC = 7200 - 1; // Prescaler for 1ms tick (assuming 16 MHz clock)
    TIM3->ARR = 1000 - 1;  // Auto-reload for
    TIM3->CR1 |= CR1_CEN; // Enable timer
    TIM3->CNT = 0; 
    TIM3->CR1 |= CR1_CEN;

}