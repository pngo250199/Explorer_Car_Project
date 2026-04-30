#include "stm32f4xx.h"
#include "gpio.h"
#define GPIOAEN	(1U <<2)


void gpio_init(void)
{

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC ->AHB2ENR |= RCC_APB1ENR_TIM2EN;

	//PA2, PA3, PA4, PA5 as input
    GPIOA -> MODER &= (0x3 << ( 2 *2));
    GPIOA -> MODER |= (0x2 << ( 2 *2));
    
    GPIOA -> MODER &= (0x3 << ( 3 *2));
    GPIOA -> MODER |= (0x2 << ( 3 *2));

    GPIOA -> MODER &= (0x3 << ( 4 *2));
    GPIOA -> MODER |= (0x2 << ( 4 *2));

    GPIOA -> MODER &= (0x3 << ( 5 *2));
    GPIOA -> MODER |= (0x2 << ( 5 *2));

    //PA1 as PWM output
    GPIOA -> MODER &= (0x3 << ( 1 *2));
    GPIOA -> MODER |= (0x2 << ( 1 *2));
}

