CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all

all: clean sala_de_espera

sala_de_espera: sala_de_espera.c
	gcc $(CFLAGS) -c Utils.c $(LDFLAGS)
	gcc $(CFLAGS) -c Deque.c $(LDFLAGS)
	gcc $(CFLAGS) -c Paciente.c $(LDFLAGS)
	gcc $(CFLAGS) -c Sala_de_Espera_Handler.c $(LDFLAGS)
	gcc $(CFLAGS) -c sala_de_espera.c $(LDFLAGS)
	gcc $(CFLAGS) -o sala_de_espera sala_de_espera.o Sala_de_Espera_Handler.o Paciente.o Deque.o Utils.o $(LDFLAGS)

clean:
	rm -f sala_de_espera
	rm -f *.o
