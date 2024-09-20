/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:52:31 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/20 09:39:53 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	timestamp()
{
	struct timeval	time;
	size_t			milliseconds;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&table->mutex);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

void	state_writer(t_table *table, int philo, char *str)
{
	pthread_mutex_lock(&table->mutex);
	printf("%lu %d %s\n", timestamp() - table->start_time, philo, str);
	pthread_mutex_unlock(&table->mutex);
	return ;
}
