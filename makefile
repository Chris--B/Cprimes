
MAIN_LIB  = cprimes.dll
PY_LIBDIR = "C:\Python32\DLLs"
PY_INCDIR = "C:\Python32\include"
GMP_LIB   = gmp-3

TEST_CMD  = python3 -m unittest -v

CFLAGS += -I..\inc -I$(PY_INCDIR)

#Oh god why
OBJS = $(addsuffix .o, $(notdir $(basename $(wildcard src/*.c))))

export 

all: $(MAIN_LIB)

$(MAIN_LIB):
	@make -C bin $(addprefix -, $(MAKEFLAGS)) $(OBJS)
	$(CC) -o $@ -shared $(addprefix bin/, $(OBJS)) -l$(GMP_LIB) -L$(PY_LIBDIR) -lpython3
	strip $@
	$(TEST_CMD)

.PHONY: clean test

test:
	$(TEST_CMD)

clean:
	@rm -fv $(MAIN_LIB)
	@cd bin && rm -fv *.o
	@rm -fv primes.h
