/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:27 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/26 16:11:27 by jlehtone         ###   ########.fr       */
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
		usleep(1);
		time--;
	}
}

static void	take_fork(t_philo *philo, int next_index)
{
	if (philo->table->exit == false)
		state_writer(philo->table, philo->number, "has taken a fork");
	if (philo->number % 2 == 0)
	{
		if (philo->table->exit == false)
			pthread_mutex_lock(&philo->table->philo[next_index]->fork);
		if (philo->table->exit == false)
			state_writer(philo->table, philo->number, "has taken a fork");
		if (philo->table->exit == false)
			pthread_mutex_lock(&philo->fork);
	}
	else
	{
		if (philo->table->exit == false)
			pthread_mutex_lock(&philo->fork);
		if (philo->table->exit == false)
			state_writer(philo->table, philo->number, "has taken a fork");
		if (philo->table->exit == false)
			pthread_mutex_lock(&philo->table->philo[next_index]->fork);
	}
}

static void	eat_sleep(t_philo *philo, int next_index)
{
	take_fork(philo, next_index);
	if (philo->table->exit == false)
		state_writer(philo->table, philo->number, "is eating");
	if (philo->table->exit == false)
		philo->last_meal = timestamp(philo->table);
	if (philo->table->exit == false)
		restless_usleep(philo->table, philo->table->time_to_eat);
	if (philo->table->exit == false)
		philo->meals_eaten++;
	if (philo->table->exit == false)
		pthread_mutex_unlock(&philo->fork);
	if (philo->table->exit == false)
		pthread_mutex_unlock(&philo->table->philo[next_index]->fork);
	if (philo->table->exit == false)
		state_writer(philo->table, philo->number, "is sleeping");
	if (philo->table->exit == false)
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
	philo->last_meal = timestamp(philo->table);
	while (philo->table->ready == false)
		usleep(1);
	while (philo->table->exit == false)
	{
		eat_sleep(philo, next_index);
		think(philo);
	}
	return (NULL);
}
