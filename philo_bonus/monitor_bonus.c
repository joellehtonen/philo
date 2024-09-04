/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:54:46 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/04 16:01:04 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static int	meal_check(t_table *table, int number, unsigned int counter)
// {
// 	if (table->philo[number]->meals_eaten > table->meals_required)
// 		counter++;
// 	if (counter == table->philos_total)
// 	{
// 		pthread_mutex_lock(&table->mutex);
// 		table->exit = true;
// 		pthread_mutex_unlock(&table->mutex);
// 	}
// 	return (counter);
// }

// void	welfare_check(t_table *table, int number)
// {
// 	size_t	time;

// 	time = timestamp(table);
// 	if ((time - table->philo[number]->last_meal) > table->time_to_die)
// 	{
// 		pthread_mutex_lock(&table->mutex);
// 		table->exit = true;
// 		pthread_mutex_unlock(&table->mutex);
// 		state_writer(table, table->philo[number]->number, "died");
// 	}
// 	return ;
// }

void	global_monitor_routine(t_table *table)
{
	unsigned int		philo_index;
	unsigned int		counter;

	philo_index = 0;
	counter = 0;
	while (check_exit(table) == false)
	{
		welfare_check(table, philo_index);
		if (table->meals_required > 0)
			counter = meal_check(table, philo_index, counter);
		philo_index++;
		if (philo_index == table->philos_total)
		{
			philo_index = 0;
			counter = 0;
		}
	}
	return ;
}

int	local_monitor_routine(t_table *philo)
{
	size_t	time;
	
	while (true)
	{
		time = timestamp(philo);
		if ((time - philo->last_meal) > philo->time_to_die)
		{
			return (philo->pid);
		}
		if (philo->meals_eaten >= philo->meals_required)
		{
			kill()
		}
	}
	return (0);
}