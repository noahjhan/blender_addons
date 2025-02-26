CC = g++
CFLAGS = -std=c++17 -Wall -O2

SRC = ./src/k_means.cpp
OBJ = ./bin/k_means.o
OUT = ./bin/exec

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

./bin/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f bin/*.o bink_means/
