#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include <stdint.h>

void ultrasonic_init(void);
uint32_t ultrasonic_read_cm(void);

#endif