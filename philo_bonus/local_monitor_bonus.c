/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:54:46 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/13 16:59:04 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// checks if the philo has eaten enough, and increments semaphore once if so
static void	meal_check(t_table *philo, int signal_sent)
{
	if (philo->meals_required > 0
		&& philo->meals_eaten >= philo->meals_required && signal_sent == 0)
	{
		sem_post(philo->full_bellies);
		signal_sent = 1;
	}
}

// checks if it's been too long since philo's last meal
// if so, alters a variable and increments a semaphore
static void	welfare_check(t_table *philo)
{
	size_t	time;

	time = timestamp(philo);
	sem_wait(philo->lock);
	if ((time - philo->last_meal) > philo->time_to_die)
	{
		philo->exit = 1;
		sem_post(philo->child_finished);
		state_writer(philo, philo->philo_number, "died");
	}
	sem_post(philo->lock);
	return ;
}

// personal monitor that calls check functions
// leaves if it's time to go
void	*local_monitor_routine(void *data)
{
	int		signal_sent;
	t_table	*philo;

	philo = (t_table *)data;
	signal_sent = 0;
	while (true)
	{
		welfare_check(philo);
		meal_check(philo, signal_sent);
		sem_wait(philo->lock);
		if (philo->exit == 1)
		{
			sem_post(philo->lock);
			break ;
		}
		else
			sem_post(philo->lock);
	}
	return (NULL);
}
