/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:44:32 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/10 12:02:13 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void close_semaphores(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->lock);
	sem_close(table->writer);
	sem_close(table->full_bellies);
	sem_close(table->start_cleanup);
	sem_unlink("/forks");
	sem_unlink("/lock");
	sem_unlink("/writer");
	sem_unlink("/full_bellies");
	sem_unlink("/start_cleanup");
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
	if (table->meals_required > 0)
		pthread_join(table->secondary_monitor, NULL);
	close_semaphores(table);
	free_memory(table);
	exit(0);
}

void	child_cleanup(t_table *philo)
{
	pthread_join(philo->monitor, NULL);
	pthread_join(philo->secondary_monitor, NULL);
	exit(0);
}

void	check_cleanup(t_table *philo)
{
	sem_wait(philo->start_cleanup);
	philo->exit = 1;
}
