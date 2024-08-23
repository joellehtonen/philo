/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:27 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/23 16:01:44 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat_sleep(t_table *table, int index, int next_index)
{
	pthread_mutex_lock(&table->philo[index]->fork);
	table->philo[index]->fork_available = false;
	state_writer(table, index, "has taken a fork");
	pthread_mutex_lock(&table->philo[next_index]->fork);
	table->philo[next_index]->fork_available = false;
	state_writer(table, index, "has taken a fork");
	state_writer(table, index, "is eating");
	//table->philo[index]->eating = true;
	usleep(table->time_to_eat);
	//table->philo[index]->eating = false;
	table->philo[index]->last_meal = 0;
	table->philo[index]->meals_eaten++;
	pthread_mutex_unlock(&table->philo[index]->fork);
	table->philo[index]->fork_available = true;
	pthread_mutex_unlock(&table->philo[next_index]->fork);
	table->philo[next_index]->fork_available = true;
	state_writer(table, index, "is sleeping");
	//table->philo[index]->sleeping = true;
	usleep(table->time_to_sleep);
	//table->philo[index]->sleeping = false;
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
		while (table->ready == 1)
		{
			if (table->philo[index]->fork_available == true
				&& table->philo[next_index]->fork_available == true
				&& table->philo[index]->dead == false)
			{
				table->philo[index]->thinking = false;
				eat_sleep(table, index, next_index);
			}
			if (table->philo[index]->thinking == false)
			{
				state_writer(table, index, "is thinking");
				table->philo[index]->thinking = true;
			}
			if (table->exit == true)
				return (NULL);
		}
	}
}
