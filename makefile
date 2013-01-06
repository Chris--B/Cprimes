
MAIN_LIB  = libcprimes.dll
GMP_LIB   = gmp-3

TEST_CMD  = python3 tests\python\tests.py

CFLAGS += -I..\inc -O2 -DNDEBUG -DMAKINGDLL
LDFLAGS = -shared -l$(GMP_LIB)

#Oh god why
OBJS = $(addsuffix .o, $(notdir $(basename $(wildcard src/*.c))))

export 

all: build

build: $(MAIN_LIB)

install: build
	@echo Try again later

$(MAIN_LIB):
	@make -C obj $(addprefix -, $(MAKEFLAGS)) $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $(addprefix obj/, $(OBJS))

.PHONY: clean test $(MAIN_LIB) build install

test:
	$(TEST_CMD)

clean:
	@rm -fv $(MAIN_LIB)
	@cd obj && rm -fv *.o
	@rm -fv primes.h
