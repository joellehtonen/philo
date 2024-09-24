/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:55:26 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/24 09:53:08 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// "sleep" which periodically checks if it's time to exit
void	restless_usleep(t_table *table, size_t time)
{
	size_t	wake_up;

	wake_up = timestamp() + time;
	while (timestamp() < wake_up && check_exit(table) == false)
	{
		usleep(100);
	}
}

void	time_to_exit(t_table *philo)
{
	unsigned int	i;

	i = 0;
	while (i < philo->philos_total)
	{
		sem_post(philo->start_cleanup);
		i++;
	}
	sem_post(philo->child_finished);
}

int	check_exit(t_table *philo)
{
	int	exit_value;

	sem_wait(philo->lock);
	exit_value = philo->exit;
	sem_post(philo->lock);
	return (exit_value);
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
