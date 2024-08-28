/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:22:50 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/28 17:15:21 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	restless_usleep(t_table *table, int time)
{
	//while (time > 0 && check_exit(table) == false)
	while (time > 0 && table->exit == false)
	{
		usleep(1000);
		time -= 1000;
	}
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
