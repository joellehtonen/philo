/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:27 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/24 11:49:58 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_table *table, int index)
{
	state_writer(table, index, "is thinking");
}

static void	eat_sleep(t_table *table, int index, int next_index)
{
	pthread_mutex_lock(&table->philo[index]->fork);
	state_writer(table, index, "has taken a fork");
	pthread_mutex_lock(&table->philo[next_index]->fork);
	state_writer(table, index, "has taken a fork");
	state_writer(table, index, "is eating");
	usleep(table->time_to_eat);
	table->philo[index]->last_meal = timestamp();
	table->philo[index]->meals_eaten++;
	pthread_mutex_unlock(&table->philo[index]->fork);
	pthread_mutex_unlock(&table->philo[next_index]->fork);
	state_writer(table, index, "is sleeping");
	usleep(table->time_to_sleep);
}


void	*routine(void *data)
{
	t_table 		*table;
	unsigned int	index;
	unsigned int	next_index;

	table = (t_table *)data;
	pthread_mutex_lock(&table->mutex);
	index = table->philo_index;
	table->philo_index++;
	pthread_mutex_unlock(&table->mutex);
	if (index == table->philos_total - 1)
		next_index = 0;
	else
		next_index = index + 1;
	while (true)
	{
	
		eat_sleep(table, index, next_index);
		think(table, index);
		if (table->exit == true)
			return (NULL);
	}
}
