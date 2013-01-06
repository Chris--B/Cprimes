
CPRIMESROOT = ../..

NAME = run.exe

LDFLAGS += -L$(CPRIMESROOT) -lcprimes

all: build

build: $(NAME)

#Oh god why
OBJS = $(addsuffix .o, $(notdir $(basename $(wildcard src/*.c))))

export

$(NAME):
	@make -C obj $(addprefix -, $(MAKEFLAGS)) $(OBJS)
	@echo ...
	$(CC) -o $@ $(addprefix obj/, $(OBJS)) $(LDFLAGS)

clean:
	@rm -vf $(NAME) obj/*.o

.PHONY: clean $(NAME)
