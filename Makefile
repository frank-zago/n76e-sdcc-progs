TOPTARGETS := all clean

SUBDIRS := \
	lib/ \
	examples/blink \
	examples/uart

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)
