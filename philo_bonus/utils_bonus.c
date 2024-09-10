/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:55:26 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/10 12:00:09 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void create_monitor_threads(t_table *philo)
{
	if (pthread_create(&philo->monitor, NULL,
		&local_monitor_routine, philo) != 0)
	{
		sem_wait(philo->writer);
		printf("Error. Failed to create a monitor thread\n");
		sem_post(philo->writer);
		free_and_exit(philo);
	}
	if (pthread_create(&philo->secondary_monitor, NULL,
		&check_cleanup, philo) != 0)
	{
		sem_wait(philo->writer);
		printf("Error. Failed to create a secondary monitor thread\n");
		sem_post(philo->writer);
		free_and_exit(philo);
	}
	return ;
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	sign = 1;
	result = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result * sign > INT_MAX)
			return (-1);
		else if (result * sign < INT_MIN)
			return (0);
		str++;
	}
	return ((int)result * sign);
}
