CC = g++
CFLAGS = -std=c++17 -Wall -O2

SRC = ./src/color_reduction.cpp
OBJ = ./bin/color_reduction.o
OUT = ./bin/exec

# Ensure the bin directory exists
BIN_DIR = ./bin
OBJ_DIR = ./bin

# Default target
all: clean $(OUT)

# Remove the output file before building
$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

# Compiling individual object files
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(OUT)

# Run the compiled executable after cleaning
.PHONY: run
run: clean $(OUT)
	./$(OUT)
