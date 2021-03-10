N76E-SDCC-PROGS - A free small BSP for Nuvoton N76E003
======================================================

The aim is to provide some sort of Arduino-like BSP for that MCU.

This is currently a toy project.

Tested on the following development board, which is flashed with an
LDROM bootloader:

  https://www.electrodragon.com/product/n76e003-mini-development-board/


Pre-requisites
--------------

  sdcc
  make
  nvtispflash for ISP support (https://github.com/frank-zago/nvtispflash)


Build
-----

To build the library and examples:
  make

To clean the tree:
  make clean

The examples can be flashed in ISP mode. For instance:
  cd example/blink
  make isp


Examples
--------

- blink: blink the builtin LED


Licensing
---------

This project, with the exception of n76e003.h, is released under the
GPL-v3 or later license. See LICENSE file. n76e003.h has its own license.

The header file, n76e003.h, is coming from

  https://github.com/erincandescent/libn76

Also see https://spdx.dev/ for the SPDX license tags.
