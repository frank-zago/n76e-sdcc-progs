/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright 2021, Frank Zago */

#include <stdint.h>

#include <n76e003.h>

/* Provide TA protection to use some special register. The expression
 * MUST compile to a single instruction. */
#define ta_prot(EXPR) do { TA = 0xaa; TA = 0x55; EXPR; } while(0)

/* MCU initialization. Should be called first by programs. */
void init_n76e(void);

/* Initializes UART0 */
void init_uart0(void);

/* Busy wait for the given amount of milliseconds */
void delay(uint16_t msec);
