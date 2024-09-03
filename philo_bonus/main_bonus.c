/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:16:13 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/03 15:58:08 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_input(char **argv)
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

void	print_instructions(void)
{
	printf("Error. Invalid amount of arguments. Instructions:\n");
	printf(" 1. Number of philosophers\n");
	printf(" 2. Time to die\n 3. Time to eat\n 4. Time to sleep\n");
	printf(" 5. How many times each philosopher must eat (optional)\n");
}

int	main(int argc, char **argv)
{
	t_table			*table;
	t_philo			*philo;

	table = NULL;
	if (argc < 5 || argc > 6)
	{
		print_instructions();
		return (EXIT_FAILURE);
	}
	if (check_input(argv) == EXIT_FAILURE)
	{
		printf("Error. Only positive integers as input\n");
		return (EXIT_FAILURE);
	}
	if (init_table(&table, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	create_semaphores();
	// if (pthread_mutex_init(&table->mutex, NULL) == EXIT_FAILURE)
	// {
	// 	printf("Error. Failed to init general mutex\n");
	// 	return (EXIT_FAILURE);
	// }
	// if (create_threads(table) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	// monitor_routine(table);
	free_and_exit(table);
	return (EXIT_SUCCESS);
}
