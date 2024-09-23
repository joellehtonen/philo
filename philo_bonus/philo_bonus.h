/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:23:14 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/23 13:53:37 by jlehtone         ###   ########.fr       */
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
	pthread_t		secondary_monitor;
	sem_t			*forks;
	sem_t			*lock;
	sem_t			*all_ready;
	sem_t			*full_bellies;
	sem_t			*child_finished;
	sem_t			*start_cleanup;
	unsigned int	philos_total;
	unsigned int	philo_number;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	unsigned int	meals_required;
	unsigned int	meals_eaten;
	size_t			last_meal;
	size_t			start_time;
	unsigned int	exit;
	unsigned int	all_full;
	unsigned int	clean;
	unsigned int	signal_sent;
	pid_t			*pid;
}	t_table;

int			init_table(t_table **table, int argc, char **argv);
void		create_lock_semaphores(t_table *table);
void		create_comm_semaphores(t_table *table);
void		*routine(void *data);
void		*local_monitor_routine(void *data);
void		global_monitor_routine(t_table *table);
size_t		timestamp(void);
void		state_writer(t_table *table, int philo, char *str);
void		free_and_exit(t_table *table, int error);
void		child_cleanup(t_table *philo);
void		*check_cleanup(void *data);
void		create_philo_monitor_threads(t_table *philo);
int			check_exit(t_table *philo);
void		restless_usleep(t_table *table, size_t time);
void		meal_check(t_table *philo);
void		time_to_exit(t_table *philo);
void		kill_all_children(t_table *table);
size_t		think_time(t_table *philo);
long long	ft_atoll(const char *str);

#endif