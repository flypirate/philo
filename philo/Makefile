
NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

SRC = parsing.c philo.c routine.c aux.c watcher.c routine_utils.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

all: $(NAME)

re: fclean all

.PHONY: clean fclean re all
