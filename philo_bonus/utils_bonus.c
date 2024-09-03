/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:55:26 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/03 15:57:30 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	restless_usleep(t_table *table, int time)
{
	while (time > 0 && check_exit(table) == false)
	{
		usleep(10000);
		time -= 10000;
	}
}

int	check_exit(t_table *table)
{
	sem_wait(table->lock);
	if (table->exit == true)
	{
		sem_post(table->lock);
		return (true);
	}
	sem_post(table->lock);
	return (false);
}

int	check_ready(t_table *table)
{
	sem_wait(table->lock);
	if (table->ready == true)
	{
		sem_post(table->lock);
		return (true);
	}
	sem_post(table->lock);
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
