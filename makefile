EXEC		= malloc
SRC_PATH	= srcs
SRC_NAME	= malloc.c
SRC		= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ_PATH	= objs
OBJ_NAME	= $(SRC_NAME:.c=.o)
OBJ		= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
DEPS_PATH	= includes
INCLUDE		= $(addprefix -I,$(DEPS_PATH))
MLXFLAGS	=
FLAGS		= -Werror -Wextra -Wall -std=gnu99 -g -shared
CFLAGS		= $(FLAGS) $(MLXFLAGS)
LDFLAGS		=
CC		= gcc

all: $(OBJ_PATH) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_PATH):
	mkdir $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

clean:
	rm -fv $(OBJ)
	rm -rfv $(OBJ_PATH)
	rm -fv $(EXEC)

re: clean all

.PHONY: clean re
