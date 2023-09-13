CFLAGS=-std=gnu11 -O2 -Wall -Wextra -Wpedantic

.PHONY: all clean

all: main

main: IO.c
	gcc $(CFLAGS) -o main IO.c

clean:
	rm -f main

