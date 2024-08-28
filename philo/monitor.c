/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:48:52 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/28 16:00:39 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int meal_check(t_table *table, int number, unsigned int counter)
{
	if (table->philo[number]->meals_eaten > table->meals_required)
		counter++;
	if (counter == table->philos_total)
	{
		pthread_mutex_lock(&table->mutex);
		table->exit = true;
		pthread_mutex_unlock(&table->mutex);
	}
	return (counter);
}

void	welfare_check(t_table *table, int number)
{
	size_t	time;

	time = timestamp(table);
	if ((time - table->philo[number]->last_meal) > table->time_to_die)
	{
		pthread_mutex_lock(&table->mutex);
		table->exit = true;
		pthread_mutex_unlock(&table->mutex);
		state_writer(table, table->philo[number]->number, "died");
	}
	return ;
}

void	monitor_routine(t_table *table)
{
	unsigned int		philo_index;
	unsigned int		counter;
	
	philo_index = 0;
	counter = 0;
	while (table->exit == false)
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
