
CPRIMESLIB  = libcprimes.dll
CPRIMESROOT = ../..

NAME = test.exe

LDFLAGS += -L$(CPRIMESROOT) -lcprimes

all: $(NAME)

#Oh god why
OBJS = $(addsuffix .o, $(notdir $(basename $(wildcard src/*.c))))

export

$(NAME): $(CPRIMESLIB)
	@make -C obj $(addprefix -, $(MAKEFLAGS)) $(OBJS)
	@echo ...
	$(CC) -o $@ $(addprefix obj/, $(OBJS)) $(LDFLAGS)

$(CPRIMESLIB): $(CPRIMESROOT)/$(CPRIMESLIB)
	cp $^ $@

$(CPRIMESROOT)/$(CPRIMESLIB):
	cd $(CPRIMESROOT) && make

clean:
	@rm -vf $(NAME) obj/*.o $(CPRIMESLIB)
