/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:41:15 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/24 10:01:28 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	thinking(t_table *philo, size_t think_time)
{
	if (check_exit(philo) == true)
		return ;
	state_writer(philo, philo->philo_number, "is thinking");
	restless_usleep(philo, think_time);
	return ;
}

static void	sleeping(t_table *philo)
{
	if (check_exit(philo) == true)
		return ;
	state_writer(philo, philo->philo_number, "is sleeping");
	restless_usleep(philo, philo->time_to_sleep);
	return ;
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
		restless_usleep(philo, philo->time_to_die + 1);
		return ;
	}
	sem_wait(philo->forks);
	if (check_exit(philo) == true)
	{
		sem_post(philo->forks);
		return ;
	}
	state_writer(philo, philo->philo_number, "has taken a fork");
	return ;
}

static void	eating(t_table *philo)
{
	take_fork(philo);
	if (check_exit(philo) == true)
		return ;
	state_writer(philo, philo->philo_number, "is eating");
	sem_wait(philo->lock);
	philo->last_meal = timestamp() - philo->start_time;
	sem_post(philo->lock);
	restless_usleep(philo, philo->time_to_eat);
	philo->meals_eaten++;
	meal_check(philo);
	sem_post(philo->forks);
	sem_post(philo->forks);
	return ;
}

// philos wait for semaphore to start the routine
// then they create a monitor thread to check wellbeing
// then they start the routine, even-numbered by thinking
void	*routine(void *data)
{
	t_table			*philo;

	philo = (t_table *)data;
	sem_wait(philo->all_ready);
	create_philo_monitor_threads(philo);
	if (philo->philo_number % 2 == 0)
		thinking(philo, philo->time_to_eat / 2);
	while (check_exit(philo) == false)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo, 10);
	}
	return (NULL);
}
