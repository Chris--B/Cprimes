CFLAGS   =-Wall -Wextra -std=c99 -Iinc -Wno-unused-parameter
LFLAGS   =-lm

VPATH=src:inc

all: prime test

debug:
	@make -B prime CC=clang CFLAGS+="-g"

release:
	@make -B prime CC=gcc CFLAGS+="-Ofast -DNDEBUG"

prime: prime.o eratos.o atkin.o $(LFLAGS)
test: test.o eratos.o atkin.o $(LFLAGS)

eratos.o: eratos.c eratos.h
uint128.o: uint128.c uint128.h
atkin.o: atkin.c atkin.h

.PHONY: clear
clean:
	@rm -fv prime *.o