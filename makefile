
MAIN_LIB  = libcprimes.dll
GMP_LIB   = gmp-3

CFLAGS += -I..\inc -O2 -DNDEBUG -DMAKINGDLL
LDFLAGS = -shared -l$(GMP_LIB)

#Oh god why
OBJS = $(addsuffix .o, $(notdir $(basename $(wildcard src/*.c))))

export 

all: build

build: $(MAIN_LIB)
	@make -C tests/c build

install: build
	@echo Try again later

$(MAIN_LIB):
	@make -C obj $(addprefix -, $(MAKEFLAGS)) $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $(addprefix obj/, $(OBJS))

clean:
	@rm -fv $(MAIN_LIB)
	@cd obj && rm -fv *.o
	@rm -fv primes.h
	@rm -fvr __pycache__
	@make -C tests/c clean

test: c-test py-test

c-test:
	@echo Running C-unittests
	@make -s -C tests/c build
	@tests/c/run

py-test:
	@echo Running Python-unittests
	@python3 tests/python/tests.py

.PHONY: clean test $(MAIN_LIB) build install test c-test py-test
