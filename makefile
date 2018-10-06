.PHONY: all clean init test

all: build/Makefile
	@$(MAKE) --no-print-directory -Cbuild all

clean:
	@rm -rfv build

init:
	@mkdir -pv build
	@cd build && cmake ..

test: all
	@$(MAKE) --no-print-directory -Cbuild test

build/Makefile:
	@$(MAKE) init
