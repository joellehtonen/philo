/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:41:15 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/13 16:45:47 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	thinking(t_table *philo, unsigned int think_time)
{
	if (check_exit(philo) == true)
		return ;
	state_writer(philo, philo->philo_number, "is thinking");
	usleep(think_time);
}

static void	sleeping(t_table *philo)
{
	if (check_exit(philo) == true)
		return ;
	state_writer(philo, philo->philo_number, "is sleeping");
	usleep(philo->time_to_sleep);
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
		usleep(philo->time_to_die * 1000);
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
	usleep(philo->time_to_eat);
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
	thinking(philo, philo->philo_number * 100);
	while (check_exit(philo) == false)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo, 0);
	}
	return (NULL);
}
