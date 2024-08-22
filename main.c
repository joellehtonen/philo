/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:55:23 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/22 12:57:38 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_table *table)
{
	int	i;
	
	if (pthread_create(&table->observer, NULL, &observer_routine, &table) != 0)
	{
		free_and_exit(table, "failed to create threads", 1);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < table->philos_total)
	{
		if (pthread_create(&table->philo[i]->thread, NULL, &routine, &table) != 0)
		{
			free_and_exit(table, "failed to create threads", 1);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	init_philo(t_philo *philo, int i)
{
	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (EXIT_FAILURE);
	memset(philo, 0, sizeof(t_philo));
	pthread_mutex_init(&philo->fork, NULL)
	philo->number = i;
	return (EXIT_SUCCESS)
}

static int	init_table(t_table *table, int argc, char **argv)
{
	int	i;
	
	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (EXIT_FAILURE);
	memset(table, 0, sizeof(t_table));
	table->philos_total = argv[1];
	table->time_to_die = argv[2];
	table->time_to_eat = argv[3];
	table->time_to_sleep = argv[4];
	if (argc == 6)
		table->meals_required = argv[5];
	i = 0;
	while(i < table->philos_total)
	{
		if (init_philo(table->philo[i], i) == EXIT_FAILURE)
		{
			free_and_exit(table, "failed to init philos", 1);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	int				number;
	t_table			*table;
	
	if (argc != 5 || argc != 6)
		return (EXIT_FAILURE);
	if (init_table(&table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&table->mutex, NULL) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_threads(&table) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	routine(table);
	pthread_mutex_destroy(&table->mutex);
	return (EXIT_SUCCESS);
}
