/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:32 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/19 14:22:21 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(table->writer);
	printf("%lu %d %s\n", timestamp(table), philo, str);
	sem_post(table->writer);
	return ;
}
