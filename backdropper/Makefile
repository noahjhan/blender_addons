CC = g++
CFLAGS = -std=c++17 -Wall -O2

SRC = ./src/color_reduction.cpp
OBJ = ./bin/color_reduction.o
OUT = ./bin/exec

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

./bin/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f bin/*.o bincolor_reduction/
