##
## EPITECH PROJECT, 2021
## makefile
## File description:
## Makefile
##

CC = gcc

SRC	= $(wildcard src/*.c) \
	  $(wildcard src/**/*.c) \

TESTED_SRC= $(filter-out src/main.c \
			$(wildcard src/*.c)) \
			$(wildcard src/**/*.c) \

TESTS_SRC = $(wildcard tests/*.c) \
			$(wildcard tests/**/*.c) \

INCLUDE	= -Iinclude

OBJ	= $(SRC:.c=.o)

CFLAGS = -pthread -g3
TFLAGS = -lcriterion -o ./unit-tests --coverage

CFLAGS += $(INCLUDE)
TFLAGS += $(INCLUDE)

NAME = panoramix

all:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		rm -f $(OBJ)
		rm -f unit-test*
		rm -f vgcore.*
		rm -f *.gc**

tests_run:
			gcc $(TESTED_SRC) $(TESTS_SRC) $(TFLAGS) $(INCLUDE) $(LIB)
			./unit-tests

cov:
			$(CC) $(TESTED_SRC) $(TESTS_SRC) $(LIB) $(TFLAGS)
			./unit-tests
			gcovr .

fclean: clean
		rm -f $(NAME)

re:	fclean all
