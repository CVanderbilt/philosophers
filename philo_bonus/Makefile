NAME=philo_three

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

LDFLAGS=-L.

LDLIBS=-lft

SRC=main.c philo_three.c utils1.c utils2.c

OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) -rf $(NAME) $(NAME).dSYM

re: fclean all

.PHONY: clean fclean all bonus