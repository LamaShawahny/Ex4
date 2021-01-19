CC = gcc -Wall -g

all: frequency
frequency: main.o
	$(CC) -o frequency main.o
frequency.o: main.c
	$(CC) -c main.c
.PHONY: all clean
clean:
	rm -f *.o main