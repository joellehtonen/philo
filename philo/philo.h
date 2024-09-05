/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:23:41 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/05 11:49:06 by jlehtone         ###   ########.fr       */
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
# include <limits.h> //for INT_MAX and INT_MIN
# include <stdbool.h> //for true and false

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	number;
	pthread_mutex_t	fork;
	unsigned int	next_fork;
	size_t			last_meal;
	unsigned int	meals_eaten;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	writer;
	unsigned int	philos_total;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	unsigned int	meals_required;
	unsigned int	exit;
	unsigned int	ready;
	size_t			start_time;
	t_philo			**philo;
}	t_table;

int		init_table(t_table **table, int argc, char **argv);
void	*routine(void *data);
void	monitor_routine(t_table *table);
void	welfare_check(t_table *table, int number);
void	state_writer(t_table *table, int philo, char *str);
size_t	timestamp(t_table *table);
void	free_and_exit(t_table *table);
int		ft_atoi(const char *str);
void	restless_usleep(t_table *table, int time);
int		check_exit(t_table *table);
int		check_ready(t_table *table);

#endif