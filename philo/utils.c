/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:22:50 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/05 15:59:56 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//check which forks philo has locked and release each
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

//"sleep" which periodically checks if it's time to exit
void	restless_usleep(t_table *table, int time)
{
	while (time > 0 && check_exit(table) == false)
	{
		usleep(10000);
		time -= 10000;
	}
}

//check if exit condition is fulfilled
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

//check if ready condition is fulfilled
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
