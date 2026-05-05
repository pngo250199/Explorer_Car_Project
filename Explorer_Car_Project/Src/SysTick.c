//#include "stm32f4xx.h"
#include "SysTick.h"

#define CRTL_ENABLE (1U << 0)
#define CTRL_CLOCKSOURCE (1U << 2)
#define CTRL_COUNTERFLAG (1U << 16)

#define BOARD_FREQUENTCY 16000

void systick_delay(uint32_t delay)
{
	SysTick -> LOAD = BOARD_FREQUENTCY -1; //load number of clock per ms
	SysTick -> VAL = 0; //current value is 0
	SysTick -> CTRL = CTRL_CLOCKSOURCE; // clock source (1 is external, 0 is from baord) define above
	SysTick -> CTRL |= CRTL_ENABLE; // enable system tick

	for ( uint32_t i = 0; i < delay; i++)
	{
		while ((SysTick -> CTRL & CTRL_COUNTERFLAG) == 0){}
	}
	SysTick -> CTRL = 0; //disable systick
}