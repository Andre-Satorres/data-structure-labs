CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: clean diadeuber

diadeuber: *.c
	gcc $(CFLAGS) *.c -o diadeuber $(LDFLAGS)

clean:
	rm -f diadeuber
	rm -f *.o
