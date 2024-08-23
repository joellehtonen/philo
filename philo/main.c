/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:55:23 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/23 13:20:31 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_table *table)
{
	unsigned int	i;
	
	if (pthread_create(&table->observer, NULL, &observer_routine, &table) != 0)
	{
		free_and_exit(table, "failed to create observer thread");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < table->philos_total)
	{
		if (pthread_create(&table->philo[i]->thread, NULL, &routine, &table) != 0)
		{
			free_and_exit(table, "failed to create philo threads");
			return (EXIT_FAILURE);
		}
		table->philo[i]->fork_available = true;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	init_philo(t_table *table, t_philo *philo, int i)
{
	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
	{
		free_and_exit(table, "failed to malloc a philo");
		return (EXIT_FAILURE);
	}
	memset(philo, 0, sizeof(t_philo));
	if (pthread_mutex_init(&philo->fork, NULL) != 0)
	{
		free_and_exit(table, "failed to init a fork");
		return (EXIT_FAILURE);
	}
	philo->number = i;
	return (EXIT_SUCCESS);
}

static int	init_table(t_table *table, int argc, char **argv)
{
	unsigned int	i;
	
	table = malloc(sizeof(t_table));
	if (table == NULL)
	{
		free_and_exit(table, "failed to malloc the table");
		return (EXIT_FAILURE);
	}
	memset(table, 0, sizeof(t_table));
	table->philos_total = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->meals_required = ft_atoi(argv[5]);
	i = 0;
	while(i < table->philos_total)
	{
		if (init_philo(table, table->philo[i], i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_table			*table;
	
	table = NULL;
	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	if (init_table(table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&table->mutex, NULL) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_threads(table) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	routine(table);
	free_and_exit(table, NULL);
	return (EXIT_SUCCESS);
}
