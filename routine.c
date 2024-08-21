/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:27 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/21 12:39:25 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int observer_routine(t_philo **philo, int argc)
{
	int	number;
	
	while (1)
	{
		if (philo[number]->last_meal > philo[number]->time_to_die)
		{
			philo[number]->dead = true;
			printf("%d %d has died\n", gettimeofday, philo[number]);
			free_and_exit();
		}
		if (number == philo[number]->philos_total)
			number = 0;
		else
			number++;
	}
}

void	routine(t_table *table, int argc)
{
	while (philo->dead == false)
	{
		if (philo->fork_available == true && philo[next]->fork_available == true)
		{
			pthread_mutex_lock;
			pthread_mutex_lock;
			philo->fork_available = false;
			printf("%d %d has taken a fork\n", gettimeofday, );
			philo[next]->fork_available = false;
			printf("%d %d has taken a fork\n", gettimeofday, );
			philo->eating = true;
			printf("%d %d is eating\n", gettimeofday, );
			usleep(philo->time_to_eat);
			philo->last_meal = 0;
			philo->meals_eaten++;
			philo->fork_available = true;
			philo[next]->fork_available = true;
			philo->eating = false;
			pthread_mutex_unlock;
			pthread_mutex_lock;
			philo->sleeping = true;
			printf("%d %d is sleeping\n", gettimeofday, );
			usleep(philo->time_to_sleep);
			philo->sleeping = false;
		}
		if (philo)
	}
	if (philo->last_meal > philo->time_to_die)
		philo->dead = true;
	else if (philo->meals_eaten == philo->meals_required)
		return (EXIT_SUCCESS);
}
