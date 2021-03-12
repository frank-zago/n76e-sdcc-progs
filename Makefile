TOPTARGETS := all clean

SUBDIRS := \
	lib/ \
	examples/blink \
	examples/iap \
	examples/uart \
	examples/ws2812

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)
