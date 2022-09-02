# This file is part of the project HelangCppMetaImpl.
# Copyright (C) 2022 Timothy Liu
# MIT License

export CXXFLAGS ?= -O3 -Wall -Wpedantic -Wextra -std=c++17
export INCLUDE_DIR = -I"$(realpath .)/include"
export CXX += $(CXXFLAGS) $(INCLUDE_DIR)
export MKDIR ?= mkdir -p
export MAKE ?= make

all:
	@echo "Nothing should be built."
	@echo "Please run \`make example\` to build examples"
	@echo "or run \`make run\` to run examples"

.PHONY: example
example:
	$(MAKE) -C example

run: example
	$(MAKE) -C example run

.PHONY: clean
clean:
	$(MAKE) -C example clean
