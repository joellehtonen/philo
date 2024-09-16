/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:41:15 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/16 10:02:26 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	thinking(t_table *philo, size_t think_time)
{
	if (check_exit(philo) == true)
		return ;
	state_writer(philo, philo->philo_number, "is thinking");
	restless_usleep(philo, think_time);
}

static void	sleeping(t_table *philo)
{
	if (check_exit(philo) == true)
		return ;
	state_writer(philo, philo->philo_number, "is sleeping");
	restless_usleep(philo, philo->time_to_sleep);
}

static void	take_fork(t_table *philo)
{
	sem_wait(philo->forks);
	if (check_exit(philo) == true)
	{
		sem_post(philo->forks);
		return ;
	}
	state_writer(philo, philo->philo_number, "has taken a fork");
	if (philo->philos_total == 1)
	{
		sem_post(philo->forks);
		restless_usleep(philo, philo->time_to_die);
		return ;
	}
	sem_wait(philo->forks);
	if (check_exit(philo) == true)
	{
		sem_post(philo->forks);
		return ;
	}
	state_writer(philo, philo->philo_number, "has taken a fork");
}

static void	eating(t_table *philo)
{
	take_fork(philo);
	if (check_exit(philo) == true)
		return ;
	state_writer(philo, philo->philo_number, "is eating");
	sem_wait(philo->lock);
	philo->last_meal = timestamp(philo);
	sem_post(philo->lock);
	restless_usleep(philo, philo->time_to_eat);
	sem_wait(philo->lock);
	philo->meals_eaten++;
	sem_post(philo->lock);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

// creates a monitor thread to check wellbeing
// then each philo thinks for an increasing amount to help with syncing
// then philos start the routine
void	*routine(void *data)
{
	t_table			*philo;

	philo = (t_table *)data;
	create_philo_monitor_threads(philo);
	if (philo->philo_number % 2 == 0)
		thinking(philo, philo->time_to_eat / 2);
	while (check_exit(philo) == false)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo, 0);
	}
	return (NULL);
}
