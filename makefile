CFLAGS   =-Wall -Wextra -std=c99 -Iinc
LFLAGS   =-lm

VPATH=src:inc

all: 
	@make prime CC=clang CFLAGS+="-g"

debug:
	@make -B prime CC=clang CFLAGS+="-g"

release:
	@make -B prime CC=gcc CFLAGS+="-Ofast -DNDEBUG"

prime: prime.o eratos.o $(LFLAGS)

eratos.o: eratos.c eratos.h
uint128.o: uint128.c uint128.h

.PHONY: clear
clean:
	@rm -fv prime *.o