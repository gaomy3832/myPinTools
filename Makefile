
PIN_ROOT ?= $(PINPATH)

all: tools

tools:
	$(MAKE) -C tools --no-print-directory PIN_ROOT=$(PIN_ROOT)

clean:
	$(MAKE) clean -C tools --no-print-directory PIN_ROOT=$(PIN_ROOT)

.PHONY: all tools clean
