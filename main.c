/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:55:23 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/21 12:53:50 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_total)
	{
		if (pthread_create(&table->philo[i]->thread, NULL, &routine, ) != 0)
		i++;
	}
}

void	init_philo(t_philo *philo, int i)
{
	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		free_and_exit(); //make this later
	memset(philo, 0, sizeof(t_philo));
	philo->number = i;
}

void	init_table(t_table *table, int argc, char **argv)
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
		init_philo(table->philo[i], i);
		i++;
	}
}

int main(int argc, char **argv)
{
	int				number;
	pthread_mutex_t	mutex;
	t_table			*table;
	
	if (argc != 5 || argc != 6)
		return (EXIT_FAILURE);
	init_table(&table, argc, argv);
	create_threads(&table);
	pthread_mutex_init(&mutex, NULL);
	routine(table, argc);
	pthread_mutex_destroy(&mutex);
	return (EXIT_SUCCESS);
}
