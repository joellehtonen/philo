NAME	= philo
CC		= cc
FLAGS	= -Wall -Wextra -Werror -pthread
SOURCES	=	main.c \
			init.c \
			routine.c \
			monitor.c \
			exit.c \
			writer.c \
			utils.c
OBJECTS	= $(SOURCES:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re