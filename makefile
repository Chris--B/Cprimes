CPPFLAGS =-Wall -Wextra -Iinc
CFLAGS   =-std=c99
LFLAGS   =-lm

VPATH=src:inc

all: prime tests

debug:
	@make -B prime CC=clang CFLAGS+="-g"

release:
	@make -B prime CC=gcc CFLAGS+="-Ofast -DNDEBUG"

prime: prime.o eratos.o atkin.o
tests: tests.o eratos.o atkin.o

.PHONY: clear
clean:
	@rm -fv prime *.o *.exe