/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:09:25 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/24 10:53:29 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	timestamp(void)
{
	struct timeval	time;
	size_t			milliseconds;
	
	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

void	state_writer(t_table *table, int philo, char *str)
{
	pthread_mutex_lock(&table->mutex);
	printf("%lu %d %s\n", (timestamp() - table->start_time), philo + 1, str);
	pthread_mutex_unlock(&table->mutex);
	return ;
}
