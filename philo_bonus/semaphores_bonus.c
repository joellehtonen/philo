/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:02:48 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/10 11:32:17 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_comm_semaphores(t_table *table)
{
	sem_unlink("/full_bellies");
	table->full_bellies = sem_open("/full_bellies",
		O_CREAT | O_EXCL, 0644, 0);
	if (table->full_bellies == SEM_FAILED)
		free_and_exit(table);
	sem_unlink("/start_cleanup");
	table->start_cleanup = sem_open("/start_cleanup",
		O_CREAT | O_EXCL, 0644, 1);
	if (table->start_cleanup == SEM_FAILED)
		free_and_exit(table);
	return ;
}

void	create_lock_semaphores(t_table *table)
{
	sem_unlink("/lock");
	table->lock = sem_open("/lock",
		O_CREAT | O_EXCL, 0644, 1);
	if (table->lock == SEM_FAILED)
		free_and_exit(table);
	sem_unlink("/writer");
	table->writer = sem_open("/writer",
		O_CREAT | O_EXCL, 0644, 1);
	if (table->writer == SEM_FAILED)
		free_and_exit(table);
	sem_unlink("/forks");
	table->forks = sem_open("/forks",
		O_CREAT | O_EXCL, 0644, table->philos_total);
	if (table->forks == SEM_FAILED)
		free_and_exit(table);
	return ;
}

