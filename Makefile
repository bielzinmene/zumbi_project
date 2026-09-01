CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic -g
INC = -Iinclude

LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))
TARGET = bin/Jogo

all: directories $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

directories:
	mkdir -p bin obj

clean:
	rm -rf obj $(TARGET)

run: all
	./$(TARGET)

.PHONY: all directories clean run