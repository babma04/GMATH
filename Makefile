CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 -Iinclude
LDFLAGS = -lm

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/libgmath.a

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	ar rcs $@ $^
	@echo "--------------------------------------"
	@echo "Successfully built library: $@"
	@echo "--------------------------------------"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	$(CC) $(CFLAGS) tests/test_main.c -L$(BIN_DIR) -lgmath $(LDFLAGS) -o $(BIN_DIR)/test_suite
	@echo "Test suite compiled. Run it with: ./$(BIN_DIR)/test_suite"

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleanup complete."

.PHONY: all clean test