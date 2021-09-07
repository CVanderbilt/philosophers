
SRCS	= main.c

SRCS	+= philo_three.c utils1.c utils2.c log.c main_checkers.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo_bonus

CC		= gcc

FLAGS	= -Wall -Wextra -Werror

HEADER	= philo.h




all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $<  -o $(<:.c=.o)