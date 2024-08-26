/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:09:25 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/26 11:29:48 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	timestamp(t_table *table)
{
	struct timeval	time;
	size_t			milliseconds;
	
	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	milliseconds = milliseconds - table->start_time;
	return (milliseconds);
}

void	state_writer(t_table *table, int philo, char *str)
{
	pthread_mutex_lock(&table->mutex);
	printf("%lu %d %s\n", timestamp(table), philo, str);
	pthread_mutex_unlock(&table->mutex);
	return ;
}

void	error_writer(t_table *table, char *str)
{
	pthread_mutex_lock(&table->mutex);
	printf("Error. %s\n", str);
	pthread_mutex_unlock(&table->mutex);
}
