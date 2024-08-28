/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:27 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/28 17:14:27 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	//if (check_exit(philo->table) == true)
	if (philo->table->exit == true)
		return ;
	state_writer(philo->table, philo->number, "is thinking");
}

static void	sleeping(t_philo *philo)
{
	//if (check_exit(philo->table) == true)
	if (philo->table->exit == true)
		return ;
	state_writer(philo->table, philo->number, "is sleeping");
	restless_usleep(philo->table, philo->table->time_to_sleep);
}

static void	take_fork(t_philo *philo, int next_index)
{
	//f (check_exit(philo->table) == true)
	if (philo->table->exit == true)
		return ;
	if (philo->number % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		state_writer(philo->table, philo->number, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->philo[next_index]->fork);
		state_writer(philo->table, philo->number, "has taken a fork");
	}
	//if (check_exit(philo->table) == true)
	if (philo->table->exit == true)
		return ;
	if (philo->number % 2)
	{
		pthread_mutex_lock(&philo->table->philo[next_index]->fork);
		state_writer(philo->table, philo->number, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->fork);
		state_writer(philo->table, philo->number, "has taken a fork");
	}
}

static void	eating(t_philo *philo, int next_index)
{
	take_fork(philo, next_index);
	//if (check_exit(philo->table) == true)
	if (philo->table->exit == true)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->table->philo[next_index]->fork);
		return ;
	}
	state_writer(philo->table, philo->number, "is eating");
	philo->last_meal = timestamp(philo->table);
	restless_usleep(philo->table, philo->table->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->table->philo[next_index]->fork);
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
	while (philo->table->ready == false) //check_ready
		usleep(1);
	while (check_exit(philo->table) == false)
	{
		eating(philo, next_index);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
