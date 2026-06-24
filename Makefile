# variable
CC = gcc
CFLAGS = -Iincludes
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))

# Rule
build/%.o: src/%.c 
	$(CC) -c $(CFLAGS) $< -o $@

# Recipe
game:$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

run:game
	./game

clean:$(OBJ)
	rm -rf ./build/*


