/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:32 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/23 14:02:57 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(table->lock);
	if (table->exit == true)
		return ;
	printf("%lu %d %s\n", timestamp() - table->start_time, philo, str);
	sem_post(table->lock);
	return ;
}
