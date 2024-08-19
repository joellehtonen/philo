/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:12:19 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/19 14:59:54 by jlehtone         ###   ########.fr       */
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

typedef struct	s_philo
{
	pthread_t		thread;
	pthread_mutex_t own_fork;
	pthread_mutex_t left_fork;
	int				eating;
	int				sleeping;
	int				dead;
	size_t 			last_meal;
	int				meals_eaten;
	int				philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_required;
	int				fork_available;
}	t_philo;

#endif