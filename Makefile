NAME	= philo
CC		= cc
FLAGS	= -Wall -Wextra -Werror -pthread
SRC_DIR = philo/
SOURCES	=	$(SRC_DIR)main.c \
			$(SRC_DIR)routine.c \
			$(SRC_DIR)observer.c \
			$(SRC_DIR)writer.c \
			$(SRC_DIR)exit.c \
			$(SRC_DIR)utils.c
OBJECTS	= $(SOURCES:.c=.o)

all: $(NAME)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -rf $(OBJECTS)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re