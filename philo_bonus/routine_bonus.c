/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:41:15 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/19 14:20:07 by jlehtone         ###   ########.fr       */
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

static int	eating(t_table *philo, int signal_sent)
{
	take_fork(philo);
	if (check_exit(philo) == true)
		return (signal_sent);
	sem_wait(philo->lock);
	state_writer(philo, philo->philo_number, "is eating");
	philo->last_meal = timestamp(philo);
	sem_post(philo->lock);
	restless_usleep(philo, philo->time_to_eat);
	philo->meals_eaten++;
	signal_sent = meal_check(philo, signal_sent);
	sem_post(philo->forks);
	sem_post(philo->forks);
	return (signal_sent);
}

// creates a monitor thread to check wellbeing
// then each philo thinks for an increasing amount to help with syncing
// then philos start the routine
void	*routine(void *data)
{
	t_table			*philo;
	int				signal_sent;

	philo = (t_table *)data;
	signal_sent = 0;
	sem_wait(philo->all_ready);
	create_philo_monitor_threads(philo);
	if (philo->philo_number % 2 == 0 && check_exit(philo) == false)
		thinking(philo, philo->time_to_eat / 2);
	while (check_exit(philo) == false)
	{
		signal_sent = eating(philo, signal_sent);
		sleeping(philo);
		thinking(philo, 0);
	}
	return (NULL);
}
