/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:55:26 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/16 16:14:34 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// "sleep" which periodically checks if it's time to exit
void	restless_usleep(t_table *table, size_t time)
{
	time = time * 1000;
	while (time > 0 && check_exit(table) == false)
	{
		usleep(100000);
		time -= 100000;
	}
}

int	check_exit(t_table *philo)
{
	int	exit_value;

	sem_wait(philo->lock);
	exit_value = philo->exit;
	sem_post(philo->lock);
	return (exit_value);
}

void	*check_cleanup(void *data)
{
	t_table	*philo;

	philo = (t_table *)data;
	sem_wait(philo->start_cleanup);
	sem_post(philo->start_cleanup);
	sem_wait(philo->lock);
	philo->exit = 1;
	sem_post(philo->lock);
	return (NULL);
}

void	create_philo_monitor_threads(t_table *philo)
{
	if (pthread_create(&philo->monitor, NULL,
			&local_monitor_routine, philo) != 0)
	{
		sem_wait(philo->writer);
		printf("Error. Failed to create a philo monitor thread\n");
		sem_post(philo->writer);
		free_and_exit(philo);
	}
	if (pthread_create(&philo->secondary_monitor, NULL,
			&check_cleanup, philo) != 0)
	{
		sem_wait(philo->writer);
		printf("Error. Failed to create a secondary philo monitor thread\n");
		sem_post(philo->writer);
		free_and_exit(philo);
	}
	return ;
}

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;

	sign = 1;
	result = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0') * sign;
		str++;
	}
	return (result);
}
