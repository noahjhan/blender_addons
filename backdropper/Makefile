CC = g++
CFLAGS = -std=c++17 -Wall -O2

SRC = ./src/color_reduction.cpp
OBJ = ./bin/color_reduction.o
OUT = ./bin/exec

# Default target
all: $(OUT)

# Linking the final executable
$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

# Compiling individual object files
./bin/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f bin/*.o $(OUT)

# Run the compiled executable after cleaning
run: clean $(OUT)
	./$(OUT)
