#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

#include <stdint.h>

void ir_sensor_init(void);
uint8_t ir_obstacle_detected(void);

#endif