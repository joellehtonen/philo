/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:54:46 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/19 13:56:26 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_cleanup(void *data)
{
	t_table	*philo;

	philo = (t_table *)data;
	sem_wait(philo->start_cleanup);
	sem_wait(philo->lock);
	philo->exit = true;
	sem_post(philo->lock);
	return (NULL);
}

// checks if the philo has eaten enough, and increments semaphore once if so
int	meal_check(t_table *philo, int signal_sent)
{
	if (philo->meals_required > 0
		&& philo->meals_eaten >= philo->meals_required && signal_sent == 0)
	{
		sem_post(philo->full_bellies);
		signal_sent = 1;
	}
	return (signal_sent);
}

// checks if it's been too long since philo's last meal
// if so, alters a variable to exit
// and increments a semaphore to let the parent know that a child died
static void	welfare_check(t_table *philo)
{
	size_t			time;
	
	sem_wait(philo->lock);
	time = timestamp(philo);
	if ((time - philo->last_meal) > philo->time_to_die)
	{
		if (philo->exit ==  false)
			state_writer(philo, philo->philo_number, "died");
		philo->exit = true;
		time_to_exit(philo);
		sem_post(philo->child_finished);
	}
	sem_post(philo->lock);
	return ;
}

// personal monitor that calls check functions
// until it's time to exit
void	*local_monitor_routine(void *data)
{
	t_table	*philo;

	philo = (t_table *)data;
	while (true)
	{
		welfare_check(philo);
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

void	create_philo_monitor_threads(t_table *philo)
{
	if (pthread_create(&philo->monitor, NULL,
			&local_monitor_routine, philo) != 0)
	{
		sem_wait(philo->writer);
		printf("Error. Failed to create a philo monitor thread\n");
		sem_post(philo->writer);
		free_and_exit(philo);
	}
	if (pthread_create(&philo->secondary_monitor, NULL,
			&check_cleanup, philo) != 0)
	{
		sem_wait(philo->writer);
		printf("Error. Failed to create a secondary philo monitor thread\n");
		sem_post(philo->writer);
		free_and_exit(philo);
	}
	return ;
}
