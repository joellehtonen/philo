/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:40:41 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/05 10:45:25 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_table *table, unsigned int i)
{
	table->philo = malloc(sizeof(t_philo *) * table->philos_total);
	if (table->philo == NULL)
	{
		printf("Error. Failed to mallocate the philo array\n");
		return (EXIT_FAILURE);
	}
	while (i < table->philos_total)
	{
		table->philo[i] = malloc(sizeof(t_philo));
		if (table->philo[i] == NULL)
		{
			printf("Error. Failed to mallocate a philo\n");
			return (EXIT_FAILURE);
		}
		memset(table->philo[i], 0, sizeof(t_philo));
		if (pthread_mutex_init(&table->philo[i]->fork, NULL) != 0)
		{
			printf("Error. Failed to init a fork\n");
			return (EXIT_FAILURE);
		}
		table->philo[i]->number = i + 1;
		table->philo[i]->table = table;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	parse_input(t_table *table, int argc, char **argv)
{
	table->philos_total = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]) * 1000;
	table->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		table->meals_required = ft_atoi(argv[5]);
	return (EXIT_SUCCESS);
}

int	init_table(t_table **table, int argc, char **argv)
{
	unsigned int	i;

	i = 0;
	*table = malloc(sizeof(t_table));
	if (*table == NULL)
	{
		printf("Error. Failed to mallocate the table\n");
		return (EXIT_FAILURE);
	}
	memset(*table, 0, sizeof(t_table));
	if (parse_input(*table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philos(*table, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(*table)->mutex, NULL) == EXIT_FAILURE)
	{
		printf("Error. Failed to init general mutex\n");
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&(*table)->writer, NULL) == EXIT_FAILURE)
	{
		printf("Error. Failed to init writer mutex\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
