CC       = clang

OPTIMIZE =-O3
CFLAGS   =-Wall -Wextra $(OPTIMIZE) -std=c99
LFLAGS   =-lm

VPATH=src

prime: prime.o eratos.o
	$(CC) -o $@ prime.o eratos.o $(LFLAGS)

eratos.o: eratos.c eratos.h

.PHONY: clear
clean:
	@rm -fv prime *.o