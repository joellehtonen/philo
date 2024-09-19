/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:23:19 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/19 15:18:17 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	parse_input(t_table *table, int argc, char **argv)
{
	table->philos_total = ft_atoll(argv[1]);
	table->time_to_die = ft_atoll(argv[2]);
	table->time_to_eat = ft_atoll(argv[3]);
	table->time_to_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		table->meals_required = ft_atoll(argv[5]);
	if (table->philos_total > 400)
	{
		printf("Error. Too many philosophers (400 or fewer please)\n");
		free_and_exit(table, 1);
	}
	if (table->time_to_die >= INT_MAX || table->time_to_eat >= INT_MAX
		|| table->time_to_sleep >= INT_MAX || table->meals_required >= INT_MAX)
	{
		printf("Error. Input values are too big\n");
		free_and_exit(table, 1);
	}
	return (EXIT_SUCCESS);
}

int	init_table(t_table **table, int argc, char **argv)
{
	*table = malloc(sizeof(t_table));
	if (*table == NULL)
	{
		printf("Error. Failed to mallocate the table\n");
		free_and_exit(*table, 1);
	}
	memset(*table, 0, sizeof(t_table));
	if (parse_input(*table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	(*table)->pid = malloc(sizeof(size_t) * ((*table)->philos_total + 1));
	if ((*table)->pid == NULL)
	{
		printf("Error. Failed to mallocate the pid array\n");
		free_and_exit(*table, 1);
	}
	return (EXIT_SUCCESS);
}
