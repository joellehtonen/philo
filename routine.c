/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:27 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/21 16:51:12 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_sleep(t_table *table, int i)
{
	pthread_mutex_lock(&table->philo[i]->fork);
	pthread_mutex_lock(&table->philo[i + 1]->fork);
	table->philo[i]->fork_available = false;
	table->philo[i + i]->fork_available = false;
	printf("%d %d has taken a fork\n", gettimeofday, table->philo[i]);
	printf("%d %d has taken a fork\n", gettimeofday, table->philo[i]);
	printf("%d %d is eating\n", gettimeofday, table->philo[i]);
	usleep(table->time_to_eat);
	table->philo[i]->last_meal = 0;
	table->philo[i]->meals_eaten++;
	pthread_mutex_unlock(&table->philo[i]->fork);
	pthread_mutex_unlock(&table->philo[i + 1]->fork);
	table->philo[i]->fork_available = true;
	table->philo[i + 1]->fork_available = true;
	printf("%d %d is sleeping\n", gettimeofday, table->philo[i] );
	usleep(table->time_to_sleep);
}


void	*routine(void *data)
{
	t_table *table;
	int		i;

	table = (t_table *)data;
	i = table->philo;
	while (1)
	{
		if (table->philo[i]->fork_available == true
			&& table->philo[i + 1]->fork_available == true
			&& table->philo[i]->dead == false)
			eat_sleep(table, i);
		printf("%d %d is thinking\n", gettimeofday, table->philo[i]);
		if (table->philo[i]->last_meal > table->time_to_die)
			table->philo[i]->dead = true;
	}
}
