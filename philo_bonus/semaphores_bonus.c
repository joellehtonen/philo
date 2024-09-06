/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:02:48 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/06 11:35:15 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_semaphores(t_table *table)
{
	sem_unlink("/lock");
	table->lock = sem_open("/lock", O_CREAT | O_EXCL, 0644, 1);
	if (table->lock == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_unlink("/writer");
	table->writer = sem_open("/writer", O_CREAT | O_EXCL, 0644, 1);
	if (table->writer == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_unlink("/forks");
	table->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, table->philos_total);
	if (table->forks == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_unlink("/hungry_philos_left");
	table->hungry_left = sem_open("/hungry_left", O_CREAT | O_EXCL, 0644, table->philos_total);
	if (table->hungry_left == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_unlink("/ready_to_die");
	table->ready_to_die = sem_open("/ready_to_die", O_CREAT | O_EXCL, 0644, table->philos_total);
	if (table->ready_to_die == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_unlink("/start_cleanup");
	table->start_cleanup = sem_open("/start_cleanup", O_CREAT | O_EXCL, 0644, 1);
	if (table->start_cleanup == SEM_FAILED)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

