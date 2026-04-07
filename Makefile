##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile
##

NAME    = mysh
NAME_TEST = unit_tests

SRC_CORE = \
	$(wildcard src/core/*.c) \
	$(wildcard src/core/init/*.c) \
	$(wildcard src/core/context/*.c)

SRC_BUILTINS = \
	$(wildcard src/builtins/env/*.c) \
	$(wildcard src/builtins/fs/*.c)

SRC_EXEC_DISPATCH = $(wildcard src/execution/dispatch/*.c)
SRC_EXEC_EXTERNAL = $(wildcard src/execution/external/*.c)
SRC_EXEC_PIPELINE = $(wildcard src/execution/pipeline/*.c)
SRC_EXEC_REDIR = $(wildcard src/execution/redirection/*.c)

SRC_ENV = \
	$(wildcard src/environment/path/*.c) \
	$(wildcard src/environment/query/*.c)

SRC_PARSING = $(wildcard src/parsing/redirection/*.c)

SRC_UTILS = \
	$(wildcard src/utils/io/*.c) \
	$(wildcard src/utils/strings/*.c) \
	$(wildcard src/utils/validation/*.c)

SRC_MEMORY = $(wildcard src/memory/free/*.c)

SRC     = \
	$(SRC_CORE) \
	$(SRC_BUILTINS) \
	$(SRC_EXEC_DISPATCH) \
	$(SRC_EXEC_EXTERNAL) \
	$(SRC_EXEC_PIPELINE) \
	$(SRC_EXEC_REDIR) \
	$(SRC_ENV) \
	$(SRC_PARSING) \
	$(SRC_UTILS) \
	$(SRC_MEMORY)

SRC2    = $(filter-out src/core/main.c,$(SRC))

OBJ     = $(SRC:.c=.o)

CC      = epiclang

CFLAGS  = -Iinclude

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

unit_tests: fclean
	clang -o $(NAME_TEST) $(SRC2) tests/*.c --coverage -lcriterion -Iinclude

tests_run: unit_tests
	./$(NAME_TEST)
	gcovr --gcov-executable "llvm-cov-20 gcov" --exclude tests/

cover: tests_run
	gcovr --gcov-executable "llvm-cov-20 gcov" --exclude tests/ --branches

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_TEST)

re: fclean all