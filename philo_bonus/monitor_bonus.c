/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:54:46 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/10 11:56:19 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all_processes(t_table *table)
{
	unsigned int	i;

	i = 0;
	sem_wait(table->start_cleanup);
	while (i < table->philos_total)
	{
		waitpid(table->pid[i], NULL, 0);
		i++;
	}
	return ;
}

static void	belly_full_check(t_table *table)
{
	unsigned int	eaten_enough;
	
	eaten_enough = 0;
	while (eaten_enough < table->philos_total)
	{
		sem_wait(table->full_bellies);
		eaten_enough++;
	}
	sem_post(table->start_cleanup);
	return ;
}

// global monitor that intermittenly checks if a child process has died
// also checks if hungry semaphore is 0 by trying to decrement it
// if successful (meaning semaphore is above 0), immediately increments it back
// kills all processes if a child has died or unable to decrement the semaphore
void	global_monitor_routine(t_table *table)
{
	pid_t			died;

	if (table->meals_eaten > 0)
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
			//printf("philo died, killing all processes\n");
			kill_all_processes(table);
			return ;
		}
		usleep(10);
	}
	return ;
}

// personal monitor that checks if it's been too long since philo's last meal
// also checks if philo has eaten enough, and decrements semaphore once if so
void	*local_monitor_routine(void *data)
{
	size_t	time;
	int		signal_sent;
	t_table *philo;
	
	philo = (t_table *)data;
	signal_sent = 0;
	while (true)
	{
		time = timestamp(philo);
		if ((time - philo->last_meal) > philo->time_to_die)
		{
			child_cleanup(philo);
			return (NULL);
		}
		if (philo->meals_eaten >= philo->meals_required
			&& signal_sent == 0
			&& philo->meals_required > 0)
		{
			sem_post(philo->full_bellies);
			// int value = 0;
			// sem_getvalue(philo->hungry_left, &value);
			// printf("philo %d is full, the value of semaphore is %d\n", philo->philo_number, value);
			signal_sent = 1;
		}
		if (sem_wait(philo->start_cleanup) == 0)
			sem_post(philo->start_cleanup);
		else
			child_cleanup(philo);
		//usleep(10);
	}
} 
