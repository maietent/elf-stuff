CC := gcc
SRC := $(wildcard src/*.c)
TARGET_NAME := loader
BUILD_DIR := build
RELEASE_DIR := $(BUILD_DIR)/release
DEBUG_DIR := $(BUILD_DIR)/debug

RELEASE_CFLAGS := -O3 -march=native -std=c11 -Wall -Wextra
DEBUG_CFLAGS := -g -O0 -std=c11 -Wall -Wextra

.PHONY: all release debug clean

all: debug

release: $(RELEASE_DIR)/$(TARGET_NAME)

debug: $(DEBUG_DIR)/$(TARGET_NAME)

$(RELEASE_DIR)/$(TARGET_NAME): $(SRC) | $(RELEASE_DIR)
	$(CC) $(RELEASE_CFLAGS) -o $@ $(SRC)

$(DEBUG_DIR)/$(TARGET_NAME): $(SRC) | $(DEBUG_DIR)
	$(CC) $(DEBUG_CFLAGS) -o $@ $(SRC)

$(RELEASE_DIR) $(DEBUG_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
