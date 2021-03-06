##
## Florian BACHO, 2018
## simple value iteration
## File description:
## Makefile
##

SRC		=	src/value_iteration.c \
			src/print_values.c

OBJ		=	$(SRC:.c=.o)

CFLAGS		=	-W -Wall -Wextra

CPPFLAGS	=	-I include

NAME		=	value_iteration

all: $(NAME)

debug: CFLAGS += -g3

debug: $(NAME)

run: all
	./$(NAME)

$(NAME): $(OBJ)
	cc -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)
	rm -rf data.dat

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re run
