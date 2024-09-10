/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:54:46 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/10 14:56:49 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all_processes(t_table *table)
{
	unsigned int	i;

	i = 0;
	sem_post(table->start_cleanup);
	while (i < table->philos_total)
	{
		waitpid(table->pid[i], NULL, 0);
		i++;
	}
	return ;
}

static void	*belly_full_check(void *data)
{
	unsigned int	eaten_enough;
	t_table 		*table;

	table = (t_table*)data;
	eaten_enough = 0;
	while (eaten_enough < table->philos_total)
	{
		sem_wait(table->full_bellies);
		eaten_enough++;
	}
	sem_wait(table->writer); //REMOVE
	printf("TIME TO KILL!!!\n"); //REMOVE
	sem_post(table->writer); //REMOVE
	kill_all_processes(table);
	return (NULL);
}

// global monitor that intermittenly checks if a child process has died
// kills all processes if a child has died
void	global_monitor_routine(t_table *table)
{
	pid_t			died;

	if (table->meals_required > 0)
	{
		if (pthread_create(&table->secondary_monitor, NULL, 
			&belly_full_check, table) != 0)
		{
			sem_wait(table->writer);
			printf("Error. Failed to create a secondary monitor thread\n");
			sem_post(table->writer);
			free_and_exit(table);
		}
	}
	while (true)
	{
		died = waitpid(0, NULL, WNOHANG);
		if (died > 0)
		{
			kill_all_processes(table);
			return ;
		}
		usleep(100);
	}
	return ;
}

// personal monitor that checks if it's been too long since philo's last meal
// also checks if philo has eaten enough, and increments semaphore once if so
void	*local_monitor_routine(void *data)
{
	size_t	time;
	int		signal_sent;
	t_table *philo;
	
	philo = (t_table *)data;
	signal_sent = 0;
	while (true)
	{
		philo->exit = 0;
		time = timestamp(philo);
		if ((time - philo->last_meal) > philo->time_to_die)
		{
			sem_wait(philo->lock);
			philo->exit = 1;
			sem_post(philo->lock);
			state_writer(philo, philo->philo_number, "died");
		}
		if (check_exit(philo) == true)
		{
			sem_wait(philo->writer); //REMOVE
			printf("I am in monitor routine! EXIT value is %d for philo %d\n", philo->exit, philo->philo_number); //REMOVE
			sem_post(philo->writer); //REMOVE
			child_cleanup(philo);
		}
		if (philo->meals_required > 0
			&& philo->meals_eaten >= philo->meals_required && signal_sent == 0)
		{
			sem_post(philo->full_bellies);
			signal_sent = 1;
			sem_wait(philo->writer); //REMOVE
			printf("SIGNAL SENT by philo %d\n", philo->philo_number); //REMOVE
			sem_post(philo->writer); //REMOVE
		}
		usleep(100);
	}
} 
