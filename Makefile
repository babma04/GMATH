CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude
LDFLAGS = -lm

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
LIB = $(BIN_DIR)/libgmath.a

# Test Files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%, $(TEST_SOURCES))

# Default Rule: Build the static library
all: $(LIB)

# Create the Static Library (Archiving object files)
$(LIB): $(OBJECTS) | $(BIN_DIR)
	ar rcs $@ $^

# Compile Source Files to Object Files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build All Tests
# Each .c file in tests/ becomes its own executable in bin/
test: $(LIB) $(TEST_BINS)

$(BIN_DIR)/%: $(TEST_DIR)/%.c $(LIB) | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -L$(BIN_DIR) -lgmath $(LDFLAGS) -o $@

# Directory Creation
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Cleanup
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all test clean