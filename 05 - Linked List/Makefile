CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: clean calculadora

calculadora: calculadora.c
	gcc $(CFLAGS) -c calculist.c $(LDFLAGS)
	gcc $(CFLAGS) -c calculadora.c $(LDFLAGS)
	gcc $(CFLAGS) -o calculadora calculadora.o calculist.o $(LDFLAGS)

clean:
	rm -f calculadora
	rm -f *.o
