/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:55:23 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/23 15:58:09 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_table *table)
{
	unsigned int	i;
	
	i = 0;
	while (i < table->philos_total)
	{
		if (pthread_create(&table->philo[i]->thread, NULL, &routine, &table) != 0)
		{
			free_and_exit(table, "Error. Failed to create a philo thread");
			return (EXIT_FAILURE);
		}
		table->philo[i]->fork_available = true;
		// pthread_mutex_lock(&table->mutex);
		// printf("created thread %d\n", i);
		// pthread_mutex_unlock(&table->mutex);
		i++;
	}
	if (pthread_create(&table->observer, NULL, &observer_routine, &table) != 0)
	{
		free_and_exit(table, "Error. Failed to create an observer thread");
		return (EXIT_FAILURE);
	}
	table->ready = 1;
	return (EXIT_SUCCESS);
}

static int	init_philo(t_table *table, int i)
{
	table->philo[i] = malloc(sizeof(t_philo));
	if (table->philo[i] == NULL)
	{
		free_and_exit(table, "Error. Failed to malloc for philos");
		return (EXIT_FAILURE);
	}
	memset(table->philo[i], 0, sizeof(t_philo));
	if (pthread_mutex_init(&table->philo[i]->fork, NULL) != 0)
	{
		free_and_exit(table, "Error. Failed to init a fork");
		return (EXIT_FAILURE);
	}
	table->philo[i]->number = i;
	//printf("inited philo %d\n", i);
	return (EXIT_SUCCESS);
}

static int	init_table(t_table **table, int argc, char **argv)
{
	unsigned int	i;
	
	*table = malloc(sizeof(t_table));
	if (table == NULL)
	{
		free_and_exit(*table, "Error. Failed to malloc for the table");
		return (EXIT_FAILURE);
	}
	memset(*table, 0, sizeof(t_table));
	(*table)->philos_total = ft_atoi(argv[1]);
	if ((*table)->philos_total > 200)
	{
		free_and_exit(*table, "Error. Too many philosophers");
		return (EXIT_FAILURE);
	}
	(*table)->philo = malloc(sizeof(t_philo) * ((*table)->philos_total + 1));
	if ((*table)->philo == NULL)
	{
		free_and_exit(*table, "Error. Failed to malloc for the philo array");
		return (EXIT_FAILURE);
	}
	(*table)->time_to_die = ft_atoi(argv[2]);
	(*table)->time_to_eat = ft_atoi(argv[3]);
	(*table)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*table)->meals_required = ft_atoi(argv[5]);
	i = 0;
	while(i < (*table)->philos_total)
	{
		if (init_philo(*table, i) == EXIT_FAILURE)
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
	{
		printf("Error. Invalid amount of arguments. Instructions:\n");
		printf(" 1. Number of philosophers\n");
		printf(" 2. Time to die\n 3. Time to eat\n 4. Time to sleep\n");
		printf(" 5. How many times each philosopher must eat (optional)\n");
		return (EXIT_FAILURE);
	}
	if (init_table(&table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&table->mutex, NULL) == EXIT_FAILURE)
	{
		printf("Error. Failed to init the general mutex\n");
		return (EXIT_FAILURE);
	}
	if (create_threads(table) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	routine(table);
	free_and_exit(table, NULL);
	return (EXIT_SUCCESS);
}
