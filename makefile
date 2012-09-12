CPPFLAGS =-Wall -Wextra -Iinc
CFLAGS   =-std=c99
LFLAGS   =-lm

VPATH=src:inc

all: prime test

debug:
	@make -B prime CC=clang CFLAGS+="-g"

release:
	@make -B prime CC=gcc CFLAGS+="-Ofast -DNDEBUG"

prime: prime.o eratos.o atkin.o
test: test.o eratos.o atkin.o

.PHONY: clear
clean:
	@rm -fv prime *.o *.exe