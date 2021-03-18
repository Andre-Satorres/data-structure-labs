CFLAGS = -std=c99 -O2 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: clean listas_legais

listas_legais: *.c
	gcc $(CFLAGS) *.c -o listas_legais $(LDFLAGS)

clean:
	rm -f listas_legais
	rm -f *.o
