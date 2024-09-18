NAME	= philo_bonus
CC		= cc
FLAGS	= -Wall -Wextra -Werror -pthread
SOURCES	=	main_bonus.c \
			init_bonus.c \
			routine_bonus.c \
			global_monitor_bonus.c \
			local_monitor_bonus.c \
			exit_bonus.c \
			writer_bonus.c \
			utils_bonus.c \
			semaphores_bonus.c
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