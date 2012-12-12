
MAIN_PROG = pyprimes.dll
PY_LIBDIR = "C:\Python32\DLLs"
PY_INCDIR = "C:\Python32\include"

CFLAGS += -I..\inc -I$(PY_INCDIR)

#Oh god why
OBJS = $(addsuffix .o, $(notdir $(basename $(wildcard src/*.c))))

export CFLAGS
export CC

all: $(MAIN_PROG) test

$(MAIN_PROG): makefile
	@make -C bin $(addprefix -, $(MAKEFLAGS)) $(OBJS)
	$(CC) -o $@ -shared $(addprefix bin/, $(OBJS)) -lgmp-3 -L$(PY_LIBDIR) -lpython3
	strip $@

.PHONY: clean test

test:
	@python3 -m unittest -v

clean:
	@rm -fv $(MAIN_PROG)
	@cd bin && rm -fv *.o

