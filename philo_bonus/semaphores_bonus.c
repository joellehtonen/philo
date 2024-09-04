/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:02:48 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/04 14:06:25 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

c
{
	sem_unlink("/lock");
	table->lock = sem_open("/lock", O_CREAT | O_EXCL, 0644, 1);
	if (table->lock == SEM_FAILED)
		return (EXIT_FAILURE);
	sem_unlink("/forks");
	table->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, table->philos_total);
	if (table->forks == SEM_FAILED)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
