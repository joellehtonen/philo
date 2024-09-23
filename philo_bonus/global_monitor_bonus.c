/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_monitor_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:54:46 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/23 13:54:06 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all_children(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->philos_total)
	{
		kill(table->pid[i], SIGKILL);
		waitpid(table->pid[i], NULL, 0);
		i++;
	}
	return ;
}

// increases a variable everytime a child increments a corresponding semaphore
// if it reaches the amount the philos, marks that all philos ate enough
// and increments a semaphore to let the main monitor know that time to finish
static void	*belly_full_check(void *data)
{
	unsigned int	eaten_enough;
	t_table			*table;

	table = (t_table *)data;
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

// creates a second monitor thread that only checks if all philos ate enough
static void	create_second_monitor(t_table *table)
{
	if (pthread_create(&table->secondary_monitor, NULL,
			&belly_full_check, table) != 0)
	{
		sem_wait(table->lock);
		printf("Error. Failed to create a secondary monitor thread\n");
		sem_post(table->lock);
		kill_all_children(table);
		free_and_exit(table, 1);
	}
}

/*global monitor that first makes a secondary monitor if needed
then waits for a child process to finish, either by dying or by eating
then kills all the other children and exits*/
void	global_monitor_routine(t_table *table)
{
	if (table->meals_required > 0)
		create_second_monitor(table);
	while (true)
	{
		sem_wait(table->child_finished);
		kill_all_children(table);
		free_and_exit(table, 0);
	}
	return ;
}
