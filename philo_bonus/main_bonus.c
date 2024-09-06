/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:16:13 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/06 13:25:26 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// starts processes by forking
// if parent, stores the pid of the new child in an array
// if child, sets its philo number and starts the routine
static int	create_processes(t_table *table)
{
	unsigned int	i;
	pid_t			pid;
	
	table->start_time = timestamp(table);
	i = 0;
	while (i < table->philos_total)
	{
		pid = fork();
		if (pid < 0)
			return (EXIT_FAILURE);
		else if (pid > 0)
			table->pid[i] = pid;
		else if (pid == 0)
		{
			table->philo_number = i + 1;
			routine(table);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

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

static void	print_instructions(void)
{
	printf("Error. Invalid amount of arguments. Instructions:\n");
	printf(" 1. Number of philosophers\n");
	printf(" 2. Time to die\n 3. Time to eat\n 4. Time to sleep\n");
	printf(" 5. How many times each philosopher must eat (optional)\n");
}

int	main(int argc, char **argv)
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
		printf("Error. Only positive integers as input\n");
		return (EXIT_FAILURE);
	}
	init_table(&table, argc, argv);
	create_lock_semaphores(table);
	create_comm_semaphores(table);
	create_processes(table);
	global_monitor_routine(table);
	free_and_exit(table);
	return (EXIT_SUCCESS);
}
