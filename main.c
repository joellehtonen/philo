/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:55:23 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/19 14:51:48 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(int argc, char **argv)
{
	t_philo			philo;
	
	philo = malloc(sizeof(t_philo));
	memset(philo, 0, sizeof(t_philo));
	philo.philos = argv[1];
	philo.time_to_die = argv[2];
	philo.time_to_eat = argv[3];
	philo.time_to_sleep = argv[4];
	if (argc == 6)
		philo.meals_required = argv[5];
}

int main(int argc, char **argv)
{
	int				number;
	pthread_mutex_t	mutex;
	
	if (argc != 5 || argc != 6)
		return (EXIT_FAILURE);
	number = argv[1];
	while (number > 0)
		init_philos(argc, argv);
	pthread_mutex_init(&mutex, NULL);
	routine();
	pthread_mutex_destroy(&mutex);
	return (EXIT_SUCCESS)
}
