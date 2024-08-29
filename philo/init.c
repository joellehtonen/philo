/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:40:41 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/29 16:46:19 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo(t_table *table, int i)
{
	table->philo[i] = malloc(sizeof(t_philo));
	if (table->philo[i] == NULL)
	{
		error_writer(table, "Failed to mallocate a philo");
		return (EXIT_FAILURE);
	}
	memset(table->philo[i], 0, sizeof(t_philo));
	if (pthread_mutex_init(&table->philo[i]->fork, NULL) != 0)
	{
		error_writer(table, "Failed to init a fork");
		while (i > 0)
			pthread_mutex_destroy(&table->philo[--i]->fork);
		return (EXIT_FAILURE);
	}
	table->philo[i]->number = i + 1;
	table->philo[i]->table = table;
	return (EXIT_SUCCESS);
}

static int	parse_input(t_table ***table, int argc, char **argv)
{
	(**table)->philos_total = ft_atoi(argv[1]);
	(**table)->time_to_die = ft_atoi(argv[2]);
	(**table)->time_to_eat = ft_atoi(argv[3]) * 1000;
	(**table)->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		(**table)->meals_required = ft_atoi(argv[5]);
	return (EXIT_SUCCESS);
}

int	init_table(t_table **table, int argc, char **argv)
{
	unsigned int	i;

	*table = malloc(sizeof(t_table));
	if (*table == NULL)
	{
		error_writer(*table, "Failed to mallocate the table");
		return (EXIT_FAILURE);
	}
	memset(*table, 0, sizeof(t_table));
	if (parse_input(&table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	(*table)->philo = malloc(sizeof(t_philo *) * (*table)->philos_total);
	if ((*table)->philo == NULL)
	{
		error_writer(*table, "Failed to mallocate the philo array");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < (*table)->philos_total)
	{
		if (init_philo(*table, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
