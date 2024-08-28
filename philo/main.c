/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:55:23 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/28 15:13:37 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_table *table)
{
	unsigned int	i;
	
	i = 0;
	while (i < table->philos_total)
	{
		if (pthread_create(&table->philo[i]->thread, NULL, &routine, table->philo[i]) != 0)
		{
			error_writer(table, "Failed to create a philo thread");
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_create(&table->observer, NULL, &observer_routine, table) != 0)
	{
		error_writer(table, "Failed to create an observer thread");
		return (EXIT_FAILURE);
	}
	table->ready = 1;
	return (EXIT_SUCCESS);
}

static int check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (j == 0)
			{
				if (argv[i][j] < '1' || argv[i][j] > '9')
					return (EXIT_FAILURE); 
			}
			else
			{
				if (argv[i][j] < '0' || argv[i][j] > '9')
					return (EXIT_FAILURE); 
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void print_instructions(void)
{
	printf("Error. Invalid amount of arguments. Instructions:\n");
	printf(" 1. Number of philosophers\n");
	printf(" 2. Time to die\n 3. Time to eat\n 4. Time to sleep\n");
	printf(" 5. How many times each philosopher must eat (optional)\n");
}

int main(int argc, char **argv)
{
	t_table			*table;
	
	table = NULL;
	if (argc < 5 || argc > 6)
	{
		print_instructions();
		return (EXIT_FAILURE);
	}
	if (check_input(argv) == EXIT_FAILURE)
	{
		printf("Error. Only positive integers accepted as input\n");
		return (EXIT_FAILURE);
	}
	if (init_table(&table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&table->mutex, NULL) == EXIT_FAILURE)
	{
		printf("Error. Failed to init the general mutex\n");
		return (EXIT_FAILURE);
	}
	table->start_time = timestamp(table);
	if (create_threads(table) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//observe(table);
	free_and_exit(table);
	return (EXIT_SUCCESS);
}
