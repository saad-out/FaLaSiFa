NAME := philo
CC := cc
CFLAGS := -Wall -Wextra -Werror -fsanitize=thread
HEADER := main.h
SRCS := actions.c actions_utils.c init.c main.c monitor.c parsing.c safe.c threads.c utils.c \
		philosophers.c clear.c philo.c actions2.c set_safe.c check_safe.c libs.c libs_2.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
