CFLAGS += --std-sdcc2x --Werror

# System clock
CFLAGS += -DFSYS=16000000

# Pin used by the on board LED, if any.
CFLAGS += -DLED_BUILTIN=P15

# Data Pin used for the WS2812 LED strip
CFLAGS += -DWS_PIN=P05

# DIO and CLK pins used by the TM1637
CFLAGS += -DTM1637_DIO=P16 -DTM1637_CLK=P17

# Fedora prefixes all sdcc tools with sdcc-.
ifneq (,$(wildcard /usr/bin/sdcc-sdcc))
	export SDCC_PREFIX ?= sdcc-
endif
