/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:23:19 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/13 12:05:52 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	*table = malloc(sizeof(t_table));
	if (*table == NULL)
	{
		printf("Error. Failed to mallocate the table\n");
		free_and_exit(*table);
	}
	memset(*table, 0, sizeof(t_table));
	if (parse_input(*table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	(*table)->pid = malloc(sizeof(size_t) * ((*table)->philos_total + 1));
	if ((*table)->pid == NULL)
	{
		printf("Error. Failed to mallocate the pid array\n");
		free_and_exit(*table);
	}
	return (EXIT_SUCCESS);
}
