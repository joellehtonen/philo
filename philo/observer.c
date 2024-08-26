/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:48:52 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/26 12:02:17 by jlehtone         ###   ########.fr       */
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
	if (table->philo[number] == NULL)
	{
		error_writer(table, "Problem with the philo index");
		return ;
	}
	if ((time - table->philo[number]->last_meal) >= table->time_to_die)
	{
		pthread_mutex_lock(&table->mutex);
		printf("I am philo %d\n", table->philo[number]->number);
		printf("time now: %zu\n", time);
		printf("last meal time: %zu\n", table->philo[number]->last_meal);
		printf("time since last meal %zu\n", time - table->philo[number]->last_meal);
		printf("time to die: %zu\n", table->time_to_die);
		table->philo[number]->dead = true;
		table->exit = true;
		pthread_mutex_unlock(&table->mutex);
		state_writer(table, table->philo[number]->number, "died");
	}
	return ;
}

void	*observer_routine(void *data)
{
	t_table				*table;
	unsigned int		number;
	unsigned int		counter;
	
	table = (t_table *)data;
	number = 0;
	counter = 0;
	while (table->exit == false)
	{
		welfare_check(table, number);
		if (table->meals_required > 0)
			counter = meal_check(table, number, counter);
		if (number == table->philos_total - 1)
		{
			number = 0;
			counter = 0;
		}
		else
			number++;
	}
	return (NULL);
}
