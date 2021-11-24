#include <stdio.h>
#include <inttypes.h>
#include "../src/ir_viewer.h"

void print_code() {
	uint32_t *code = ir_viewer_getCode();

	for (int i = 0; code && i < 100; i++) {
		if (code[i] == 0) {
			break;
		}

		printf("%3i : %" PRIu32 "\n", i, code[i]);
	}
}

uint32_t tick = 0;

void test1() {
	printf("Test 1\n");

	ir_viewer_gpioAlertCallback(1, 1, tick += 10);
	ir_viewer_gpioAlertCallback(1, 0, tick += 1300);
	ir_viewer_gpioAlertCallback(1, 1, tick += 750);
	ir_viewer_gpioAlertCallback(1, 2, tick += 118000);

	print_code();
}

void test2() {
	printf("Test 2\n");

	ir_viewer_gpioAlertCallback(1, 0, tick += 8000);
	ir_viewer_gpioAlertCallback(1, 1, tick += 1300);
	ir_viewer_gpioAlertCallback(1, 0, tick += 750);
	ir_viewer_gpioAlertCallback(1, 2, tick += 118000);

	print_code();
	print_code();
}


void test3() {
	printf("Test 3\n");

	ir_viewer_gpioAlertCallback(1, 2, tick += 801);
	ir_viewer_gpioAlertCallback(1, 2, tick += 810);
	ir_viewer_gpioAlertCallback(1, 2, tick += 880);

	ir_viewer_gpioAlertCallback(1, 0, tick += 133);
	ir_viewer_gpioAlertCallback(1, 0, tick += 800);
	ir_viewer_gpioAlertCallback(1, 1, tick += 1300);
	ir_viewer_gpioAlertCallback(1, 1, tick += 1300);
	ir_viewer_gpioAlertCallback(1, 0, tick += 750);
	ir_viewer_gpioAlertCallback(1, 2, tick += 118000);

	print_code();
}


int main(int argc, char **argv) {
	printf("Hello GPIO\n");

	ir_viewer_setGpio(1);
	tick = 1000;

	printf("Tick check 1 %" PRIu32 "\n", tick += 1);
	printf("Tick check 10 %" PRIu32 "\n", tick += 10);
	printf("Tick check 100 %" PRIu32 "\n", tick += 100);


	test1();
	test2();
	test3();
}
