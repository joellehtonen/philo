/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:27 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/24 14:47:14 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	think(t_table *table, int index)
// {
// 	state_writer(table, index, "is thinking");
// }

// static void	eat_sleep(t_table *table, int index, int next_index)
// {
// 	pthread_mutex_lock(&table->philo[index]->fork);
// 	state_writer(table, index, "has taken a fork");
// 	pthread_mutex_lock(&table->philo[next_index]->fork);
// 	state_writer(table, index, "has taken a fork");
// 	state_writer(table, index, "is eating");
// 	table->philo[index]->last_meal = timestamp();
// 	usleep(table->time_to_eat);
// 	table->philo[index]->meals_eaten++;
// 	pthread_mutex_unlock(&table->philo[index]->fork);
// 	pthread_mutex_unlock(&table->philo[next_index]->fork);
// 	state_writer(table, index, "is sleeping");
// 	usleep(table->time_to_sleep);
// }

// void	*routine(void *data)
// {
// 	t_table 		*table;
// 	unsigned int	index;
// 	unsigned int	next_index;

// 	table = (t_table *)data;
// 	pthread_mutex_lock(&table->mutex);
// 	index = table->philo_index + 1;
// 	table->philo_index++;
// 	pthread_mutex_unlock(&table->mutex);
// 	if (index == table->philos_total - 1)
// 		next_index = 0;
// 	else
// 		next_index = index + 1;
// 	if (table->philo[index]->number % 2 == 0)
// 		think(table, index);
// 	while (table->exit == false)
// 	{
// 		eat_sleep(table, index, next_index);
// 		think(table, index);
// 	}
// 	return (NULL);
// }

static void	think(t_philo *philo)
{
	state_writer(philo->table, philo->number, "is thinking");
}

static void	eat_sleep(t_philo *philo, int next_index)
{
	pthread_mutex_lock(&philo->fork);
	state_writer(philo->table, philo->number, "has taken a fork");
	pthread_mutex_lock(&philo->table->philo[next_index]->fork);
	state_writer(philo->table, philo->number, "has taken a fork");
	state_writer(philo->table, philo->number, "is eating");
	philo->last_meal = timestamp();
	usleep(philo->table->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->table->philo[next_index]->fork);
	state_writer(philo->table, philo->number, "is sleeping");
	usleep(philo->table->time_to_sleep);
}

void	*routine(void *data)
{
	t_philo			*philo;
	unsigned int	next_index;

	philo = (t_philo *)data;
	if (philo->number == philo->table->philos_total - 1)
		next_index = 0;
	else
		next_index = philo->number + 1;
	if (philo->number % 2 == 0)
		think(philo);
	while (true)
	{
		while (philo->table->exit == false && philo->dead == false && philo->table->ready == true)
		{
			eat_sleep(philo, next_index);
			think(philo);
		}
	}
	return (NULL);
}
