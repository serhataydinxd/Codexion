NAME	= codexion
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread


SRCS	= main.c srcs/ft_atoi.c srcs/parse.c srcs/dongle.c srcs/coder.c srcs/time.c srcs/sim.c srcs/routine.c srcs/logging.c srcs/heap.c srcs/request.c
INCS	= includes
OBJS	= $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
