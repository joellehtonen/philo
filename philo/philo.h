/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:23:41 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/24 11:45:14 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h> //for threads
# include <stdlib.h> //for exit status and malloc
# include <sys/time.h> //for time
# include <stdio.h> //for printing
# include <unistd.h> //for usleep
# include <string.h> //for memset
# include <limits.h> //for INT_MAX
# include <stdbool.h> //for true and false

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	number;
	pthread_mutex_t fork;
	//unsigned int	fork_available;
	//unsigned int	thinking;
	//unsigned int	sleeping;
	//unsigned int	eating;
	unsigned int	dead;
	size_t 			last_meal;
	unsigned int	meals_eaten;
}	t_philo;

typedef struct	s_table
{
	pthread_t		observer;
	pthread_mutex_t	mutex;
	unsigned int	philos_total;
	unsigned int	philo_index;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	unsigned int	meals_required;
	unsigned int	exit;
	unsigned int	ready;
	size_t			start_time;
	t_philo			**philo;
}	t_table;

void		*routine(void *data);
void		*observer_routine(void *data);
void		state_writer(t_table *table, int philo, char *str);
size_t		timestamp(void);
void		free_and_exit(t_table *table, char *message);
int			ft_atoi(const char *str);

#endif