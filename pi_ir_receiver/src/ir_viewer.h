/*
 * ir_viewer.h
 *
 */

#ifndef IR_VIEWER_H_
#define IR_VIEWER_H_

#include <stdint.h>

#define IR_VIEWER_CODE_MAX_LENGTH 512

void ir_viewer_setGpio(int gpio);

void ir_viewer_gpioAlertCallback(int gpio, int level, uint32_t tick);

uint32_t* ir_viewer_getCode();

#endif /* IR_VIEWER_H_ */
