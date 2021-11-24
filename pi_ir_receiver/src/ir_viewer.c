/*
 * ir_viewer.c
 *
 *  Created on: 11 Feb 2019
 *
 *  A callback method, compatible with gpioSetAlertFunc (see <pigpio.h>)
 */
#include "ir_viewer.h"

#define IR_VIEWER_CODE_BUF_SIZE 128

typedef struct {
	int gpio;
	uint32_t max_gap;
	int lastCodeIndex;

	int codeCounter;
	int codeBufCounter;
	uint32_t *gap;
	int lastLevel;
	uint32_t lastTick;

	uint32_t codeBuf[IR_VIEWER_CODE_BUF_SIZE][IR_VIEWER_CODE_MAX_LENGTH];
} ir_viewer_data_t;


ir_viewer_data_t ir_viewer_data;

void ir_viewer_setGpio(int gpio) {
	ir_viewer_data_t *me = &ir_viewer_data;

	me->gpio = gpio;
	me->codeCounter = 0;
	me->codeBufCounter = 0;
	me->gap = 0;
	me->lastCodeIndex = 0;
	me->max_gap = 30000;
}


/*
The callback is passed the GPIO, the new level, and the tick.

. .
Parameter   Value    Meaning

GPIO        0-31     The GPIO which has changed state

level       0-2      0 = change to low (a falling edge)
                     1 = change to high (a rising edge)
                     2 = no level change (a watchdog timeout)

tick        32 bit   The number of microseconds since boot
                     WARNING: this wraps around from
                     4294967295 to 0 roughly every 72 minutes
*/
void ir_viewer_gpioAlertCallback(int gpio, int level, uint32_t tick) {
	ir_viewer_data_t *me = &ir_viewer_data;

	if (gpio != me->gpio) {
		// Ignore signals from another input
		return;
	}

	// not initialized yet
	if (me->gap == 0) {

		// ignore timeouts (no level change)
		if (level == 2) {
			return;
		}

		me->gap = me->codeBuf[me->codeBufCounter];
		*me->gap = 0;
		me->codeCounter = 0;
		me->lastLevel = level;
		me->lastTick = tick;
		return;
	}

	uint32_t gap = 0;

	if (me->lastTick > tick) {
		gap = 1000; // FIXME implement overflow handling: tick + 4294967295 - me->lastTick;
	} else {
		gap = tick - me->lastTick;
	}

	me->lastTick = tick;
	*me->gap += gap;

	if (*me->gap > me->max_gap) {
		// end of code recognition
		*me->gap = 0;
		me->gap = 0;

		// move to next buffer (start)
		me->codeBufCounter ++;
		if (me->codeBufCounter >= IR_VIEWER_CODE_BUF_SIZE) {
			me->codeBufCounter = 0;
		}
		return;
	}

	// no level changes: stop by timeout
	if (level == 2 || level == me->lastLevel) {
		return;
	}

	// initialized and level has changed
	me->lastLevel = level;
	// move to next code point
	me->gap ++;
	me->codeCounter ++;

	if (me->codeCounter >= IR_VIEWER_CODE_MAX_LENGTH) {
		me->gap = 0;
	}
}

/*
 * Returns null if no code is available.
 *
 * Otherwise a pointer to null terminated sequence of tick gaps.
 */
uint32_t* ir_viewer_getCode() {
	ir_viewer_data_t *me = &ir_viewer_data;

	if (me->lastCodeIndex == me->codeBufCounter) {
		return 0;
	}
	uint32_t *code = me->codeBuf[me->lastCodeIndex];
	me->lastCodeIndex ++;
	if (me->lastCodeIndex >= IR_VIEWER_CODE_BUF_SIZE) {
		me->lastCodeIndex = 0;
	}
	return code;
}
