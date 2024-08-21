/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:12:19 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/21 16:44:58 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h> //for threads
# include <stdlib.h> //for exit status and malloc
# include <sys/time.h> //for time
# include <stdio.h> //for printing
# include <unistd.h> //for usleep
# define false 0
# define true 1

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	number;
	pthread_mutex_t fork;
	//pthread_mutex_t next_fork;
	unsigned int	fork_available;
	unsigned int	dead;
	size_t 			last_meal;
	unsigned int	meals_eaten;
}	t_philo;

typedef struct	s_table
{
	pthread_t		observer;
	unsigned int	philos_total;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	unsigned int	meals_required;
	t_philo			**philo;
}	t_table;

void	*routine(void *data);
void	*observer_routine(void *data)

#endif