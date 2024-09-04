/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:41:15 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/04 15:53:55 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	thinking(t_table *philo, unsigned int think_time)
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
	if (check_exit(philo) == false)
		sem_wait(philo->forks);
	if (check_exit(philo) == false)
		state_writer(philo, philo->philo_number, "has taken a fork");
	if (check_exit(philo) == true || philo->philos_total == 1)
		return ;
	if (check_exit(philo) == false)
		sem_wait(philo->forks);
	if (check_exit(philo) == false)
		state_writer(philo, philo->philo_number, "has taken a fork");
}

static void	eating(t_table *philo)
{
	take_fork(philo);
	if (check_exit(philo) == true || philo->philos_total == 1)
	{
		sem_post(philo->forks);
		if (philo->philos_total == 1)
			restless_usleep(philo, philo->time_to_die * 1000);
		sem_post(philo->forks);
		return ;
	}
	state_writer(philo, philo->philo_number, "is eating");
	philo->last_meal = timestamp(philo);
	restless_usleep(philo, philo->time_to_eat);
	philo->meals_eaten++;
	sem_post(philo->forks);
	sem_post(philo->forks);
}

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
	while (check_exit(philo) == false)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo, 0);
	}
	return (NULL);
}
