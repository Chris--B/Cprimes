
NAME = doit.exe
INC_DIR = ..\..\inc

CFLAGS += -I $(INC_DIR)
LDFLAGS += -lgmp

#Oh god why
OBJS = $(addsuffix .o, $(notdir $(basename $(wildcard ../../src/*.c))))

all: $(NAME)

vpath %.o ..\..\bin
vpath %.h $(INC_DIR)

$(NAME): AllTests.o CuTest.o test_eratos.o $(OBJS)
	$(CC) $^ -o $@

clean:
	@rm -vf $(NAME) *.o
