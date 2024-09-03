/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:41:15 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/03 15:57:33 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static void	take_fork(t_philo *philo, int next_index)
{
	if (check_exit(philo->table) == false)
		sem_wait(philo->table->forks);
	if (check_exit(philo->table) == false)
		state_writer(philo->table, philo->number, "has taken a fork");
	if (check_exit(philo->table) == true || philo->table->philos_total == 1)
		return ;
	if (check_exit(philo->table) == false)
		sem_wait(philo->table->forks);
	if (check_exit(philo->table) == false)
		state_writer(philo->table, philo->number, "has taken a fork");
}

static void	eating(t_philo *philo, int next_index)
{
	take_fork(philo, next_index);
	if (check_exit(philo->table) == true || philo->table->philos_total == 1)
	{
		sem_post(philo->table->forks);
		if (philo->table->philos_total == 1)
			restless_usleep(philo->table, philo->table->time_to_die * 1000);
		sem_post(philo->table->forks);
		return ;
	}
	state_writer(philo->table, philo->number, "is eating");
	philo->last_meal = timestamp(philo->table);
	restless_usleep(philo->table, philo->table->time_to_eat);
	philo->meals_eaten++;
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
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
	while (check_ready(philo->table) == false)
		usleep(10);
	if (philo->number % 2 == 0)
		thinking(philo, 100);
	while (check_exit(philo->table) == false)
	{
		eating(philo, next_index);
		sleeping(philo);
		thinking(philo, 0);
	}
	return (NULL);
}
