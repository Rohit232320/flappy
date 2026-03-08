CC = gcc

# Raylib path
RAYLIB_PATH = ../raylib

# Compiler flags with raylib include path
CFLAGS = -Iinclude -I$(RAYLIB_PATH)/include -Wall -Wextra -std=c11 -g

# Linker flags with raylib library path
LIBS = -L$(RAYLIB_PATH)/lib -lraylib -lopengl32 -lgdi32 -lwinmm -lm

# Source files in src/ directory
SRC = src/main.c src/pipe.c src/bird.c src/bg_gnd.c src/score.c

# Object files in obj/ directory
OBJ = $(SRC:src/%.c=obj/%.o)

# Target executable
TARGET = flappybird.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

obj/%.o: src/%.c
	@if not exist obj mkdir obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if exist obj rmdir /S /Q obj
	@if exist $(TARGET) del /Q $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run