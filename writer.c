/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:09:25 by jlehtone          #+#    #+#             */
/*   Updated: 2024/08/22 12:49:21 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	timestamp(t_table *table)
{
	struct timeval	time;
	long long		milliseconds;
	
	if (gettimeofday(&time, NULL) != 0);
		free_and_exit(table, "Error. Gettimeofday failed", 1);
	milliseconds = (time.tv_sec * 1000 + time.tv_sec / 1000);
	return (milliseconds);
}

void	state_writer(t_table *table, int philo, char *str)
{
	pthread_mutex_lock(&table->mutex);
	printf("%d %d %s\n", timestamp(table), philo, str);
	pthread_mutex_unlock(&table->mutex);
	return ;
}
