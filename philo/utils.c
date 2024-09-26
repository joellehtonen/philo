/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:22:50 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/26 13:57:20 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check which forks philo has locked and release each
void	release_forks(t_philo *philo)
{
	if (philo->own_fork_locked == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		philo->own_fork_locked = 0;
	}
	if (philo->next_fork_locked == 1)
	{
		pthread_mutex_unlock(&philo->table->philo[philo->next_index]->fork);
		philo->next_fork_locked = 0;
	}
}

// "sleep" which periodically checks if it's time to exit
void	restless_usleep(t_table *table, size_t time)
{
	time = time * 1000;
	while (time > 0 && check_exit(table) == false)
	{
		usleep(100000);
		time -= 100000;
		if (time < 100000)
		{
			usleep(time);
			time = 0;
		}
	}
}

int	check_exit(t_table *table)
{
	pthread_mutex_lock(&table->mutex);
	if (table->exit == true)
	{
		pthread_mutex_unlock(&table->mutex);
		return (true);
	}
	pthread_mutex_unlock(&table->mutex);
	return (false);
}

int	check_ready(t_table *table)
{
	pthread_mutex_lock(&table->mutex);
	if (table->ready == true)
	{
		pthread_mutex_unlock(&table->mutex);
		return (true);
	}
	pthread_mutex_unlock(&table->mutex);
	return (false);
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
