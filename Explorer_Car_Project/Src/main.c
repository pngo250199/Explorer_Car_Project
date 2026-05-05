#include "gpio.h"
#include "spi.h"
#include "tim.h"
#include "SysTick.h"
#include <stdint.h>

int main(void){
    gpio_init();

    while(1)
    {
        gpio_init();
        spi_init();
        tim_init();
    }

}