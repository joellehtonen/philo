/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:02:27 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/19 15:52:36 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine(t_philo *philo)
{
	while (philo->dead == false)
	{
		if (philo->eating == false && philo->sleeping == false 
			&& philo[previous]->fork_available == true)
		{
			pthread_mutex_lock;
			philo->fork_available = false;
			philo->eating = true;
			usleep(philo->time_to_eat);
			philo->last_meal = 0;
			philo->meals_eaten++;
			philo->fork_available = true;
			philo->eating = false;
			pthread_mutex_unlock;
			philo->sleeping = true;
			usleep(philo->time_to_sleep);
			philo->sleeping = false;
		}
	}
	if (philo->dead == true)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}