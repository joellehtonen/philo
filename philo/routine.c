/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:27 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/05 11:34:39 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo, unsigned int think_time)
{
	if (check_exit(philo->table) == true)
		return ;
	state_writer(philo->table, philo->number, "is thinking");
	restless_usleep(philo->table, think_time);
}

static void	sleeping(t_philo *philo)
{
	if (check_exit(philo->table) == true)
		return ;
	state_writer(philo->table, philo->number, "is sleeping");
	restless_usleep(philo->table, philo->table->time_to_sleep);
}

static void	take_fork(t_philo *philo)
{
	if (check_exit(philo->table) == false)
		pthread_mutex_lock(&philo->fork);
	if (check_exit(philo->table) == false)
		state_writer(philo->table, philo->number, "has taken a fork");
	if (check_exit(philo->table) == true || philo->table->philos_total == 1)
		return ;
	if (check_exit(philo->table) == false)
		pthread_mutex_lock(&philo->table->philo[philo->next_fork]->fork);
	if (check_exit(philo->table) == false)
		state_writer(philo->table, philo->number, "has taken a fork");
}

static void	eating(t_philo *philo)
{
	take_fork(philo);
	if (check_exit(philo->table) == true || philo->table->philos_total == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		if (philo->table->philos_total == 1)
			restless_usleep(philo->table, philo->table->time_to_die * 1000);
		pthread_mutex_unlock(&philo->table->philo[philo->next_fork]->fork);
		return ;
	}
	state_writer(philo->table, philo->number, "is eating");
	pthread_mutex_lock(&philo->table->mutex);
	philo->last_meal = timestamp(philo->table);
	pthread_mutex_unlock(&philo->table->mutex);
	restless_usleep(philo->table, philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->mutex);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->table->philo[philo->next_fork]->fork);
}

void	*routine(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	if (philo->number == philo->table->philos_total)
		philo->next_fork = 0;
	else
		philo->next_fork = philo->number;
	while (check_ready(philo->table) == false)
		usleep(10);
	if (philo->number % 2 == 0)
		thinking(philo, 100);
	while (check_exit(philo->table) == false)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo, 0);
	}
	return (NULL);
}
