CC = gcc
CFLAGS = -g -ITiotimolina -Wall -Wextra -std=c99 -O3 -DNDEBUG
OBJ = color.o dato.o grafo.o main.o orden.o vertice.o

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o main

valgrind: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o main
	valgrind --leak-check=full --show-reachable=yes ./main

clean:
	$(RM) $(OBJ) main