/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:48:52 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/13 16:31:14 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//check if a philo has eaten enough. if all have, flip exit condition
static int	meal_check(t_table *table, int number, unsigned int counter)
{
	pthread_mutex_lock(&table->mutex);
	if (table->philo[number]->meals_eaten >= table->meals_required)
		counter++;
	if (counter == table->philos_total)
		table->exit = true;
	pthread_mutex_unlock(&table->mutex);
	return (counter);
}

//check if a philo has died, if so, flip exit condition
void	welfare_check(t_table *table, int number)
{
	size_t	time;

	time = timestamp(table);
	pthread_mutex_lock(&table->mutex);
	if ((time - table->philo[number]->last_meal) > table->time_to_die)
	{
		table->exit = true;
		state_writer(table, table->philo[number]->number, "died");
	}
	pthread_mutex_unlock(&table->mutex);
	return ;
}

//check thru all the philos. loop as long as necessary
void	monitor_routine(t_table *table)
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
