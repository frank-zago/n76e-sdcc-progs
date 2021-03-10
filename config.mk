CFLAGS += --std-sdcc2x --Werror

# System clock
CFLAGS += -DFSYS=16000000

# Pin used by the on board LED, if any.
CFLAGS += -DLED_BUILTIN=P15
