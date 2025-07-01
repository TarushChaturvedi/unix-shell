CC = gcc
CFLAGS = -O2 -s -Wall -Werror -Isrc
SRC_DIR = src
BUILD_DIR = bin
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET = shell

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BUILD_DIR)/$@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
