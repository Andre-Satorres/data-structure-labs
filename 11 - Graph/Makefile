CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: clean caminho

caminho: caminho.c
	gcc $(CFLAGS) *.c -o caminho $(LDFLAGS)

clean:
	rm -f *.o
	rm -f caminho
