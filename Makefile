TOPTARGETS := all clean

SUBDIRS := \
	lib/ \
	examples/blink \
	examples/bmp280-i2c \
	examples/bmp280-spi \
	examples/iap \
	examples/uart \
	examples/ws2812

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)
