/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:54:30 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/28 15:32:01 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_memory(t_table *table)
{
	unsigned int	i;

	if (table == NULL)
		return ;
	i = 0;
	while (i < table->philos_total)
	{
		free(table->philo[i]);
		i++;
	}
	free(table->philo);
	free(table);
}

void	destroy_mutexes(t_table *table)
{
	unsigned int	i;
	
	if (table == NULL)
		return ;
	i = 0;
	while (i < table->philos_total)
	{
		pthread_mutex_destroy(&table->philo[i]->fork);
		i++;
	}
	pthread_mutex_destroy(&table->mutex);
}

void	join_threads(t_table *table)
{
	unsigned int	i;

	if (table == NULL)
		return ;
	i = 0;
	while (i < table->philos_total)
	{
		pthread_join(table->philo[i]->thread, NULL);
		i++;
	}
}

void	free_and_exit(t_table *table)
{
	join_threads(table);
	destroy_mutexes(table);
	free_memory(table);
	return ;
}
