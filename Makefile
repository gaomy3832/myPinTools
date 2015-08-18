
export PIN_ROOT ?= $(PINPATH)

all: tools

src:
	$(MAKE) -C src --no-print-directory

tools: src
	$(MAKE) -C tools --no-print-directory

clean:
	$(MAKE) clean -C src --no-print-directory
	$(MAKE) clean -C tools --no-print-directory

.PHONY: all src tools clean
