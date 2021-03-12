TOPTARGETS := all clean

SUBDIRS := \
	lib/ \
	examples/blink \
	examples/iap \
	examples/uart

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)
