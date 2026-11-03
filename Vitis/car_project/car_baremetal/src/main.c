#include <stdint.h>

#define CUSTOM_IP_BASE 0x43C00000U

int main(void)
{
    volatile uint32_t *gpio =
        (volatile uint32_t *)(CUSTOM_IP_BASE + 0x00U);

    while (1)
    {
        *gpio = 0x1;
    }

    return 0;
}