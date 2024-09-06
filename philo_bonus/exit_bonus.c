/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:44:32 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/06 13:12:16 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void close_semaphores(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->lock);
	sem_close(table->writer);
	sem_close(table->hungry_left);
	sem_unlink(table->forks);
	sem_unlink(table->lock);
	sem_unlink(table->writer);
	sem_unlink(table->hungry_left);
}

static void	free_memory(t_table *table)
{
	unsigned int	i;

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
	exit;
}

void	child_cleanup(t_table *philo)
{
	pthread_join(philo->monitor, NULL);
	sem_wait(philo->ready_to_die);
	exit;
}
