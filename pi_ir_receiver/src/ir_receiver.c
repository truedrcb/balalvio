#include <stdio.h>
#include <inttypes.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "pigpio.h"
#include "ir_viewer.h"


#define DEFAULT_IR_PIN 6

#define OUTSIDE_CODE 0
#define INSIDE_CODE  1

#define MIN_MESSAGE_GAP 3000
#define MAX_MESSAGE_END 3000

#define MAX_TRANSITIONS 500

/*
   using the FNV-1a hash
   from http://isthe.com/chongo/tech/comp/fnv/#FNV-param
*/

#define FNV_PRIME_32 16777619
#define FNV_BASIS_32 2166136261U

static volatile uint32_t ir_hash = 0;

typedef struct
{
   int state;
   int count;
   int level;
   uint16_t micros[MAX_TRANSITIONS];
} decode_t;

/* forward declarations */

void     gpioAlertDecodeCallback(int gpio, int level, uint32_t tick);
uint32_t getDecodeHash(decode_t * decode);
void     updateDecodeState(decode_t * decode, int level, uint32_t micros);

void printTimeStamp()
{
    time_t timer;
    char buffer[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    puts(buffer);
}


int main(int argc, char * argv[])
{
int ir_pin = DEFAULT_IR_PIN;

if (argc > 1) {
	printf("Setting input GPIO pin to %s\n", argv[1]);
	ir_pin = atoi(argv[1]);
}

printf("Initializing.\n");

if (gpioInitialise()<0) {
      return 1 ;
   }

   /* IR pin as input */

   gpioSetMode(ir_pin, PI_INPUT);

   /* 5ms max gap after last pulse */

   gpioSetWatchdog(ir_pin, 5);

   /* monitor IR level changes */

//   gpioSetAlertFunc(IR_PIN, gpioAlertDecodeCallback);

   ir_viewer_setGpio(ir_pin);
   gpioSetAlertFunc(ir_pin, ir_viewer_gpioAlertCallback);

   printf("Initialized for GPIO%i.\n", ir_pin);

   while (1) {
//      if (ir_hash)
//      {
//         /* non-zero means new decode */
//         printf("ir code is %u\n", ir_hash);
//         ir_hash = 0;
//      }
		uint32_t *code = ir_viewer_getCode();

		if (code) {
			printf("\n\n\n");
			printTimeStamp();
			printf("Code received\n");
			for (int i = 0; i < 1000; i++) {
				if (code[i] == 0) {
					break;
				}

				printf("%3i : %" PRIu32 "\n", i, code[i]);
			}

			printf("Comma separated:\n");

			for (int i = 0, ii = 0; i < 1000; i++, ii++) {
				if (code[i] == 0) {
					break;
				}

				printf("%" PRIu32 ", ", code[i]);
				if (ii >= 15) {
					ii = 0;
					printf("\n");
				}
			}
		}

      gpioDelay(100000); /* check remote 10 times per second */
   }

   gpioTerminate();
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
void gpioAlertDecodeCallback(int gpio, int level, uint32_t tick)
{
   static int inited = 0;

   static decode_t activeHigh, activeLow;

   static uint32_t lastTick;

   uint32_t diffTick;

   if (!inited)
   {
      inited = 1;

      activeHigh.state = OUTSIDE_CODE; activeHigh.level = PI_LOW;
      activeLow.state  = OUTSIDE_CODE; activeLow.level  = PI_HIGH;

      lastTick = tick;
      return;
   }

   diffTick = tick - lastTick;

   if (level != PI_TIMEOUT) lastTick = tick;

   updateDecodeState(&activeHigh, level, diffTick);
   updateDecodeState(&activeLow, level, diffTick);
}

void updateDecodeState(decode_t * decode, int level, uint32_t micros)
{
   /*
      We are dealing with active high as well as active low
      remotes.  Abstract the common functionality.
   */

   if (decode->state == OUTSIDE_CODE)
   {
      if (level == decode->level)
      {
         if (micros > MIN_MESSAGE_GAP)
         {
            decode->state = INSIDE_CODE;
            decode->count = 0;
         }
      }
   }
   else
   {
      if (micros > MAX_MESSAGE_END)
      {
         /* end of message */

         /* ignore if last code not consumed */

         if (!ir_hash) ir_hash = getDecodeHash(decode);

         decode->state = OUTSIDE_CODE;
      }
      else
      {
         if (decode->count < (MAX_TRANSITIONS-1))
         {
            if (level != PI_TIMEOUT)
               decode->micros[decode->count++] = micros;
         }
      }
   }
}

int compareForDecodeHash(unsigned int oldval, unsigned int newval)
{
   if      (newval < (oldval * 0.75)) {return 1;}
   else if (oldval < (newval * 0.75)) {return 2;}
   else                               {return 4;}
}

uint32_t getDecodeHash(decode_t * decode)
{
   /* use FNV-1a */

   uint32_t hash;
   int i, value;

   if (decode->count < 6) {return 0;}

   hash = FNV_BASIS_32;

   for (i=0; i<(decode->count-2); i++)
   {
      value = compareForDecodeHash(decode->micros[i], decode->micros[i+2]);

      hash = hash ^ value;
      hash = (hash * FNV_PRIME_32);
   }

   return hash;
}
