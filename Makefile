# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 -Iinclude
LDFLAGS = -lm

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Files
# This finds all .c files in src/ and creates a list of corresponding .o files in obj/
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/libgmath.a

# Default Rule
all: $(TARGET)

# Create the Static Library (.a file)
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	ar rcs $@ $^
	@echo "Library built: $@"

# Compile Source Files to Object Files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Rule: Removes build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned up build files."

# Test Rule: Compiles a test program if you have one in tests/
test: $(TARGET)
	$(CC) $(CFLAGS) tests/test_main.c -L$(BIN_DIR) -lgmath $(LDFLAGS) -o $(BIN_DIR)/test_suite
	@echo "Test suite built in $(BIN_DIR)/"

.PHONY: all clean test
