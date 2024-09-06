/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:23:14 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/06 11:32:02 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <pthread.h> //for threads
# include <stdlib.h> //for exit status and malloc
# include <sys/time.h> //for time
# include <stdio.h> //for printing
# include <unistd.h> //for usleep
# include <string.h> //for memset
# include <limits.h> //for INT_MAX and INT_MIN
# include <stdbool.h> //for true and false
# include <semaphore.h> //for semaphores
# include <signal.h> //for kill
# include <sys/wait.h> //for WNOHANG
# include <fcntl.h> // for O_CREAT and O_EXCL

typedef struct s_table
{
	pthread_t		monitor;
	sem_t			*forks;
	sem_t			*lock;
	sem_t			*writer;
	sem_t			*hungry_left;
	sem_t			*start_cleanup;
	sem_t			*ready_to_die;
	unsigned int	philos_total;
	unsigned int	philo_number;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	unsigned int	meals_required;
	unsigned int	meals_eaten;
	size_t			last_meal;
	size_t			start_time;
	size_t			**pid;
}	t_table;

int		create_semaphores(t_table *table);
void	*routine(void *data);
int		local_monitor_routine(t_table *philo);
void	global_monitor_routine(t_table *table);

#endif