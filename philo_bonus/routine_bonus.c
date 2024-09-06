/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:41:15 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/06 09:57:43 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	thinking(t_table *philo, unsigned int think_time)
{
	state_writer(philo, philo->philo_number, "is thinking");
	usleep(think_time);
}

static void	sleeping(t_table *philo)
{
	state_writer(philo, philo->philo_number, "is sleeping");
	usleep(philo->time_to_sleep);
}

static void	take_fork(t_table *philo)
{
	sem_wait(philo->forks);
	state_writer(philo, philo->philo_number, "has taken a fork");
	if (philo->philos_total == 1)
		return ;
	sem_wait(philo->forks);
	state_writer(philo, philo->philo_number, "has taken a fork");
}

static void	eating(t_table *philo)
{
	take_fork(philo);
	if (philo->philos_total == 1)
	{
		sem_post(philo->forks);
		if (philo->philos_total == 1)
			usleep(philo->time_to_die * 1000);
		return ;
	}
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
// then each thinks for an increasing amount to help with syncing
// then philo starts the routine
void	*routine(void *data)
{
	t_table			*philo;

	philo = (t_table*)data;
	if (pthread_create(&philo->monitor, NULL,
		&local_monitor_routine, philo) != 0);
	{
		sem_wait(philo->lock);
		printf("Error. Failed to create a monitor thread\n");
		sem_post(philo->lock);
		return (NULL); //is this correct return value?
	}
	thinking(philo, philo->philo_number * 100);
	while (true)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo, 0);
	}
	return (NULL);
}
