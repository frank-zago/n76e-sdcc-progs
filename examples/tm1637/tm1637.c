/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2024, Frank Zago */

/* Display something on a 4-digit 7-segment display, with a semi-colon
 * in the middle, connected to a Titan Micro TM1387.
 *
 * Connect DIO to pin 16
 *         CLK to pin 17
 */

#include <stdint.h>

#include <libn76e.h>

/* Digits 0 to 9 encoded for each 7-segment display. See for instance
 * https://www.electronicsforu.com/resources/7-segment-display-pinout-understanding. */
const uint8_t digit_segments[] = {
	0b00111111,		/* number 0 */
	0b00000110,
	0b01011011,
	0b01001111,
	0b01100110,
	0b01101101,
	0b01111101,
	0b00000111,
	0b01111111,
	0b01101111,
};

void main(void)
{
	/* Important: sdcc 4.1 gets confused when the fields are not
	 * in the same order as the declaration; it sets them to
	 * 0. */
	struct tm1637 display = {
		.count = 4,	 /* 4 digits */
		.on = 1,
		.brightness = 0, /* lowest brightness */
	};
	uint8_t digit = 0;
	uint8_t i;

	init_n76e();

	while (1) {
		/* Rotate the digits. This will print 0123, 1234, 2345, ... */
		for (i = 0; i < display.count; i++) {
			display.displays[i] = digit_segments[(digit + i) % 10];
		}
		digit++;

		/* The semi-colon separating the 4 digits in the
		 * middle is at position 1. Set it too, alternating
		 * on/off. */
		if (digit & 1)
			display.displays[1] |= 0x80;

		update_tm1637(&display);

		/* Rotate the brightness */
		// display.brightness++;

		/* Blink builtin LED */
		LED_BUILTIN = 0;
		delay(500);
		LED_BUILTIN = 1;
		delay(500);
	}
}
