/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:54:30 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/24 10:51:59 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_memory(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->philos_total)
	{
		free(table->philo[i]);
		i++;
	}
	free(table->philo);
	free(table);
}

static void	destroy_mutexes(t_table *table)
{
	unsigned int	i;
	
	i = 0;
	while (i < table->philos_total)
	{
		pthread_mutex_destroy(&table->philo[i]->fork);
		i++;
	}
	pthread_mutex_destroy(&table->mutex);
}

static void	join_threads(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->philos_total)
	{
		pthread_join(table->philo[i]->thread, NULL);
		i++;
	}
	pthread_join(table->observer, NULL);
}

void	free_and_exit(t_table *table, char *message)
{
	if (message != NULL)
	{
		pthread_mutex_lock(&table->mutex);
		printf("%s\n", message);
		pthread_mutex_unlock(&table->mutex);
	}
	join_threads(table);
	destroy_mutexes(table); //is an if statement needed here?
	free_memory(table);
	return ;
}
