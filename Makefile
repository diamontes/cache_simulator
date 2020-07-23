CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Werror -D_XOPEN_SOURCE=700

.PHONY: all clean cache_simulator

all: cache_simulator

clean:
	rm -f *.o cache_simulator

cache_simulator: main.o
	$(CC) $(CFLAGS) -o cache_simulator main.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c
