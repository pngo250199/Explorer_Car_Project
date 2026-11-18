#include <stdint.h>

#include "stm32f1xx.h"
#include "uart.h"
#include "ultrasound_sensor.h"
#include "ir_sensor.h"

static void uart_print_uint(uint32_t value)
{
    char buffer[11];
    int index = 0;

    if (value == 0U)
    {
        uart_transmit('0');
        return;
    }

    while (value > 0U)
    {
        buffer[index] = '0' + (value % 10U);
        value /= 10U;
        index++;
    }

    while (index > 0)
    {
        index--;
        uart_transmit(buffer[index]);
    }
}

int main(void)
{
    uint32_t distance;
    uint32_t obstacle;
    uart_init();

    ultrasonic_init();
    ir_sensor_init();
    uart_print("ULTRASONIC TEST\r\n");

    while (1)
    {
        distance = ultrasonic_read_cm();

        uart_print("Distance: ");
        uart_print_uint(distance);
        uart_print(" cm\r\n");

        obstacle = ir_obstacle_detected();
        uart_print("IR Obstacle Detected: ");
        uart_print_uint(obstacle);
        uart_print("\r\n");
        /*
         * Temporary delay between measurements
         */
        for (volatile uint32_t i = 0; i < 500000U; i++)
        {
            __NOP();
        }


    }
}