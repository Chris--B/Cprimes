CPPFLAGS =-Wall -Wextra -Iinc
CFLAGS   =-O3
LFLAGS   =-lm

VPATH=src:inc

all: prime tests

prime: prime.o eratos.o
tests: tests.o eratos.o benchmark.o

.PHONY: clear
clean:
	@rm -fv *.o
	@rm -fv prime.exe tests.exe