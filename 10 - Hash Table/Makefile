CFLAGS = -std=c99 -Wall -Werror -O2 -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: clean corretor

corretor: corretor.c
	gcc $(CFLAGS) *.c -o corretor $(LDFLAGS)

clean:
	rm -f corretor
	rm -f *.o
