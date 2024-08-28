/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:54:30 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/28 11:01:53 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_memory(t_table *table)
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

static void	destroy_mutexes(t_table *table)
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

static void	join_threads(t_table *table)
{
	unsigned int	i;

	if (table == NULL)
		return ;
	i = 0;
	while (i < table->philos_total)
	{
		pthread_join(table->philo[i]->thread, NULL);
		i++;
		printf("joined thread %d\n", i);
	}
	pthread_join(table->observer, NULL);
	printf("joined observer\n");
}

void	free_and_exit(t_table *table)
{
	printf("in free and exit\n");
	join_threads(table);
	printf("after join threads\n");
	destroy_mutexes(table); //if statement needed here?
	printf("after destroying mutexes\n");
	free_memory(table);
	printf("after freeing memory\n");
	return ;
}
