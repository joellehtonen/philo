/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:27 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/21 16:38:28 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_sleep(t_table *table, int i)
{
	pthread_mutex_lock;
	pthread_mutex_lock;
	table->philo[i]->fork_available = false;
	printf("%d %d has taken a fork\n", gettimeofday, table->philo[i]);
	table->philo[i + i]->fork_available = false;
	printf("%d %d has taken a fork\n", gettimeofday, table->philo[i]);
	table->philo[i]->eating = true;
	printf("%d %d is eating\n", gettimeofday, table->philo[i]);
	usleep(table->time_to_eat);
	table->philo[i]->last_meal = 0;
	table->philo[i]->meals_eaten++;
	table->philo[i]->fork_available = true;
	table->philo[i + 1]->fork_available = true;
	table->philo[i]->eating = false;
	pthread_mutex_unlock;
	pthread_mutex_lock;
	table->philo[i]->sleeping = true;
	printf("%d %d is sleeping\n", gettimeofday, table->philo[i] );
	usleep(table->time_to_sleep);
	table->philo[i]->sleeping = false;
}


void	*routine(void *data)
{
	t_table *table;
	int		i;

	table = (t_table *)data;
	i = ?;
	while (1)
	{
		if (table->philo[i]->fork_available == true && table->philo[i + 1]->fork_available == true)
			eat_sleep(table, i);
		printf("%d %d is thinking\n", gettimeofday, table->philo[i]);
	}
	if (philo->last_meal > philo->time_to_die)
		philo->dead = true;
	else if (philo->meals_eaten == philo->meals_required)
		return (EXIT_SUCCESS);
}
