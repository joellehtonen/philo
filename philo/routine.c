/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:27 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/16 16:13:36 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo, size_t think_time)
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

// philos take a fork, and check whether they should take the other one
static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo->own_fork_locked = 1;
	if (check_exit(philo->table) == false)
		state_writer(philo->table, philo->number, "has taken a fork");
	if (check_exit(philo->table) == true || philo->table->philos_total == 1)
		return ;
	pthread_mutex_lock(&philo->table->philo[philo->next_index]->fork);
	philo->next_fork_locked = 1;
	if (check_exit(philo->table) == false)
		state_writer(philo->table, philo->number, "has taken a fork");
}

// philos first take forks (and release them immediately if needed)
// then they eat, locking themselves everytime they update their variables
// then they release their forks, for others to use
static void	eating(t_philo *philo)
{
	take_fork(philo);
	if (check_exit(philo->table) == true || philo->table->philos_total == 1)
	{
		release_forks(philo);
		if (philo->table->philos_total == 1)
			restless_usleep(philo->table, philo->table->time_to_die);
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
	release_forks(philo);
}

// first philos get the index of their other fork,
// then wait until all are ready
// even-numbered philos start by thinking a bit, to help with timing
// then they run their routine, until an exit condition is flipped
void	*routine(void *data)
{
	t_philo			*philo;

	philo = (t_philo *)data;
	if (philo->number == philo->table->philos_total)
		philo->next_index = 0;
	else
		philo->next_index = philo->number;
	while (check_ready(philo->table) == false)
		usleep(10);
	if (philo->number % 2 == 0)
		thinking(philo, philo->table->time_to_eat / 2);
	while (check_exit(philo->table) == false)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo, 0);
	}
	return (NULL);
}
