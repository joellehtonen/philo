/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:54:46 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/13 11:58:20 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_all_processes(t_table *table)
{
	unsigned int	i;

	sem_post(table->start_cleanup);
	i = 0;
	while (i < table->philos_total)
	{
		waitpid(table->pid[i], NULL, 0);
		//kill(table->pid[i], SIGTERM);
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
	sem_wait(table->lock);
	table->all_full = true;
	sem_post(table->lock);
	sem_post(table->child_finished);
	return (NULL);
}

// global monitor that intermittenly checks if a child process has died
// first makes a secondary monitor if needed
// kills all processes if a child died or everyone ate enough
void	global_monitor_routine(t_table *table)
{
	pid_t			died;

	died = 0;
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
		sem_wait(table->child_finished);
		kill_all_processes(table);
		free_and_exit(table);
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
		time = timestamp(philo);
		sem_wait(philo->lock);
		if ((time - philo->last_meal) > philo->time_to_die)
		{
			philo->exit = 1;
			sem_post(philo->child_finished);
			state_writer(philo, philo->philo_number, "died");
		}
		sem_post(philo->lock);
		if (philo->meals_required > 0
			&& philo->meals_eaten >= philo->meals_required && signal_sent == 0)
		{
			sem_post(philo->full_bellies);
			signal_sent = 1;
		}
		usleep(10);
		if (philo->exit == 1)
			break ;
	}
	return (NULL);
}
