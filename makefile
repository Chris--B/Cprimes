
MAIN_LIB  = cprimes.dll

CFLAGS := -I..\inc -O2 -DNDEBUG -DMAKINGDLL -Wall -Wextra

#Oh god why
OBJS = $(addsuffix .o, $(notdir $(basename $(wildcard src/*.c))))

#You may want to change this
PYTHON_DIR = \Python33

export 

all: build
	@echo Build sucessful

build: $(MAIN_LIB)
	@make -C c-tests build

install: build
	cp cprimes.py $(PYTHON_DIR)\Lib\cprimes.py
	cp cprimes.dll \PATH\cprimes.dll

uninstall:
	@rm -fv $(PYTHON_DIR)\Lib\cprimes.py
	@rm -fv \PATH\cprimes.dll

$(MAIN_LIB):
	@make -C obj $(addprefix -, $(MAKEFLAGS)) $(OBJS)
	$(CC) -o $@ -shared $(addprefix obj/, $(OBJS)) -lgmp

clean:
	@rm -fv $(MAIN_LIB)
	@cd obj && rm -fv *.o
	@rm -fv primes.h
	@rm -fvr __pycache__
	@make -C c-tests clean

test: c-test py-test

c-test:
	@echo Running C-unittests
	@make -s -C c-tests build
	@c-tests\run-tests

py-test:
	@echo Running Python-unittests
	@python3 cprimes-tests.py

.PHONY: clean test $(MAIN_LIB) build install test c-test py-test
