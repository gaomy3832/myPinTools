
export PIN_ROOT ?= $(PINPATH)

all: tools

tools:
	$(MAKE) -C tools --no-print-directory

clean:
	$(MAKE) clean -C tools --no-print-directory

.PHONY: all tools clean
