# This file is part of the project HelangCppMetaImpl.
# Copyright (C) 2022 Timothy Liu
# MIT License

TARGET_DIR ?= target

.PHONY: all
all: $(TARGET_DIR)/test $(TARGET_DIR)/test_array.s

$(TARGET_DIR)/test: $(TARGET_DIR) test.cpp
	$(CXX) -o $@ test.cpp

$(TARGET_DIR)/test_array.s: $(TARGET_DIR) test_array.cpp
	$(CXX) -o $@ -S test_array.cpp

$(TARGET_DIR):
	$(MKDIR) $(TARGET_DIR)

.PHONY: run
run: all
	$(TARGET_DIR)/test

.PHONY: clean
clean:
	-$(RM) -r target
