EXEC		= malloc
EXEC_STATIC	= $(addprefix $(EXEC),.a)
EXEC_SHARED	= $(addprefix $(EXEC),.so)
SRC_PATH	= srcs
SRC_NAME	= malloc.c
SRC		= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ_PATH	= objs
OBJ_NAME	= $(SRC_NAME:.c=.o)
OBJ		= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
DEPS_PATH	= includes
INCLUDE		= $(addprefix -I,$(DEPS_PATH))
MLXFLAGS	=
FLAGS		= -c -Werror -Wextra -Wall -std=gnu99 -g
CFLAGS		= $(FLAGS) $(MLXFLAGS)
LDFLAGS		=
CC		= gcc

all: $(OBJ_PATH) $(EXEC_STATIC)

$(EXEC_STATIC): $(OBJ)
	ar rcs $@ $^

$(OBJ_PATH):
	mkdir $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

static: $(OBJ_PATH) $(EXEC_SHARED)

$(EXEC_SHARED): $(OBJ)
	$(CC) -o $(EXEC_SHARED) $^ $(CFLAGS)-shared -fPIC

test:
	gcc -g -Wall -Werror -Wextra tests/test.c malloc.a
	./a.out

clean:
	rm -fv $(OBJ)
	rm -rfv $(OBJ_PATH)
	rm -fv $(EXEC)

re: clean all

.PHONY: clean re
