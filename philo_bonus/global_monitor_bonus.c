/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_monitor_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:54:46 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/19 17:16:38 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// increments a semaphore to let other children exit
// then waits their pids as confirmation
void	wait_children_to_exit(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->philos_total)
	{
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
	time_to_exit(table);
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
		time_to_exit(table);
		child_cleanup(table);
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
		wait_children_to_exit(table);
		free_and_exit(table, 0);
	}
	return ;
}
