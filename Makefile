NAME = philo

HEADER = philo.h
SRC = philo.c action_v2.c action.c tools.c init_.c 

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
