/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:44:32 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/19 15:16:46 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	unlink_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/lock");
	sem_unlink("/writer");
	sem_unlink("/all_ready");
	sem_unlink("/full_bellies");
	sem_unlink("/child_finished");
	sem_unlink("/start_cleanup");
	return ;
}

static void	close_semaphores(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->lock);
	sem_close(table->writer);
	sem_close(table->all_ready);
	sem_close(table->full_bellies);
	sem_close(table->child_finished);
	sem_close(table->start_cleanup);
	return ;
}

static void	free_memory(t_table *table)
{
	if (table->pid != NULL)
		free(table->pid);
	if (table != NULL)
		free(table);
	return ;
}

// first checks if a secondary thread was created
// then checks if it's still waiting for semaphores,
// if so, increments semaphores so that the thread can finish and join
// then closes and unlinks semaphores and frees memory
void	free_and_exit(t_table *table, int error)
{
	unsigned int	i;

	i = 0;
	if (table->meals_required > 0)
	{
		if (table->all_full == false)
		{
			while (i < table->philos_total)
			{
				sem_post(table->full_bellies);
				i++;
			}
		}
		pthread_join(table->secondary_monitor, NULL);
	}
	close_semaphores(table);
	unlink_semaphores();
	free_memory(table);
	exit(error);
}

void	child_cleanup(t_table *philo)
{
	pthread_join(philo->monitor, NULL);
	pthread_join(philo->secondary_monitor, NULL);
	close_semaphores(philo);
	free_memory(philo);
	exit(0);
}
