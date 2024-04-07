NAME := philo_bonus
CC := cc
CFLAGS := -Wall -Wextra -Werror
HEADER := main.h
SRCS := actions.c check_safe.c init.c parsing.c processes.c set_safe.c utils.c utils_3.c \
		actions_utils.c clear.c main.c philosophers.c safe.c threads.c utils_2.c
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
