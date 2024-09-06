/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:44:32 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/06 13:50:22 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void close_semaphores(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->lock);
	sem_close(table->writer);
	sem_close(table->hungry_left);
	sem_close(table->start_cleanup);
	sem_close(table->ready_to_die);
	sem_unlink("/forks");
	sem_unlink("/lock");
	sem_unlink("/writer");
	sem_unlink("/hungry_left");
	sem_unlink("/start_cleanup");
	sem_unlink("/ready_to_die");
}

static void	free_memory(t_table *table)
{
	if (table->pid != NULL)
		free(table->pid);
	if (table != NULL)
		free(table);
	return ;
}

void	free_and_exit(t_table *table)
{
	close_semaphores(table);
	free_memory(table);
	exit(0);
}

void	child_cleanup(t_table *philo)
{
	pthread_join(philo->monitor, NULL);
	sem_wait(philo->ready_to_die);
	exit(0);
}
