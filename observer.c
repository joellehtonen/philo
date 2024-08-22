/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:48:52 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/22 10:57:13 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wellfare_check(t_table *table, int number)
{
	if (table->philo[number]->last_meal > table->time_to_die)
	{
		state_writer(table, table->philo[number], "died");
		free_and_exit(table, NULL, 0);
	}
	return ;
}

void	*observer_routine(void *data)
{
	t_table	*table;
	int		number;
	int		counter;
	
	table = (t_table *)data;
	number = 0;
	while (1)
	{
		wellfare_check(table, number);
		if (table->meals_required > 0)
		{
			if (table->philo[number]->meals_eaten > table->meals_required)
				counter++;
			if (counter == table->philos_total)
				free_and_exit(table, NULL, 0);
		}
		if (number == table->philos_total)
		{
			number = 0;
			counter = 0;
		}
		else
			number++;
	}
}
