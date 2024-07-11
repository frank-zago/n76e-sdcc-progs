/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2024, Frank Zago */

/* Support for the TM1637 LED  driver. Keyboard not supported. */

#include <libn76e.h>

#define CMD_SET_DATA 0b01000000
#define CMD_SET_DISP 0b10000000
#define CMD_SET_ADDR 0b11000000

/* Pins to use for communication */
#define DIO TM1637_DIO
#define CLK TM1637_CLK

/* Wait about 100us between each bits. It could be too slow, but do we
 * care? */
static void wait(void)
{
	const uint16_t tick_per_100us = FSYS / 12 / 1000 / 10;
	const uint16_t start = ~tick_per_100us;

	/* Clock is Fsys / 12 */
	SET_FIELD(CKCON, T0M, 0);

	/* Set timer 0 in mode 1 */
	SET_FIELD(TMOD, T0M, 1);

	THL0 = start;

	TR0 = 1;

	while (TF0 == 0);

	TR0 = 0;
	TF0 = 0;
}

static void start(void)
{
	CLK = 1;
	DIO = 1;
	wait();
	DIO = 0;
	wait();
}

static void stop(void)
{
	CLK = 0;
	DIO = 0;
	wait();
	CLK = 1;
	wait();
}

/* Write a byte of data. */
static void write_data(uint8_t data)
{
	uint8_t i;

	/* Write all 8 bits */
	for (i = 0; i < 8; i++) {
		CLK = 0;
		DIO = data & 1;
		wait();
		CLK = 1;
		wait();

		data >>= 1;
	}

	/* Wait for ack */
	CLK = 0;
	while (DIO == 1);
	wait();
	CLK = 1;
	wait();
}

/* The application sets the few variables in display, then calls this
 * function as needed to update the state of the TM1637. */
void update_tm1637(const struct tm1637 *display)
{
	uint8_t i;

	CLK = 1;
	DIO = 1;
	wait();

	/* This command sets:
	 *   - write data to display register
	 *   - automatic address adding (ie. auto increment mode)
	 *   - normal mode
	 */
	start();
	write_data(CMD_SET_DATA | 0b0000);
	stop();

	/* Set first address at position 0. */
	start();
	write_data(CMD_SET_ADDR | 0b000);

	/* Configure each digit */
	for (i = 0; i < display->count; i++)
		write_data(display->displays[i]);

	stop();

	/* Activate display */
	start();
	write_data(CMD_SET_DISP | (display->on << 3) | display->brightness);
	stop();
}
