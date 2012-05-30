CC       = clang

OPTIMIZE =-O3
CFLAGS   =-Wall -Wextra $(OPTIMIZE) -std=c99 -Iinc
LFLAGS   =-lm

VPATH=src:inc

prime: prime.o eratos.o $(LFLAGS)

eratos.o: eratos.c eratos.h
uint128.o: uint128.c uint128.h

.PHONY: clear
clean:
	@rm -fv prime *.o