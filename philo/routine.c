/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:27 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/28 15:23:14 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo)
{
	state_writer(philo->table, philo->number, "is thinking");
}

static void	restless_usleep(t_table *table, int time)
{
	while (time > 0 && table->exit == false)
	{
		usleep(1000);
		time -= 1000;
	}
}

static void	take_fork(t_philo *philo, int next_index)
{
	state_writer(philo->table, philo->number, "has taken a fork");
	if (philo->number % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->philo[next_index]->fork);
		state_writer(philo->table, philo->number, "has taken a fork");
		pthread_mutex_lock(&philo->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		state_writer(philo->table, philo->number, "has taken a fork");
		pthread_mutex_lock(&philo->table->philo[next_index]->fork);
	}
	if (philo->table->exit == true)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->table->philo[next_index]->fork);
	}
}

static void	eat_sleep(t_philo *philo, int next_index)
{
	take_fork(philo, next_index);
	state_writer(philo->table, philo->number, "is eating");
	philo->last_meal = timestamp(philo->table);
	restless_usleep(philo->table, philo->table->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->table->philo[next_index]->fork);
	state_writer(philo->table, philo->number, "is sleeping");
	restless_usleep(philo->table, philo->table->time_to_sleep);
}

void	*routine(void *data)
{
	t_philo			*philo;
	unsigned int	next_index;

	philo = (t_philo *)data;
	if (philo->number == philo->table->philos_total)
		next_index = 0;
	else
		next_index = philo->number;
	while (philo->table->ready == false)
		usleep(1);
	while (philo->table->exit == false)
	{
		eat_sleep(philo, next_index);
		think(philo);
	}
	return (NULL);
}
