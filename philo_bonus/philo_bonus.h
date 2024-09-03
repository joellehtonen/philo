/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:23:14 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/03 15:47:41 by jlehtone         ###   ########.fr       */
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

typedef struct s_table	t_table;

typedef struct s_philo
{
	//pthread_t		thread;
	unsigned int	number;
	//pthread_mutex_t	fork;
	size_t			last_meal;
	unsigned int	meals_eaten;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	//pthread_t		observer;
	sem_t			*forks;
	sem_t			*lock;
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

#endif