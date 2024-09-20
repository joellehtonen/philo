/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:32 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/19 17:32:14 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	timestamp()
{
	struct timeval	time;
	size_t			milliseconds;

	gettimeofday(&time, NULL);
	milliseconds = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (milliseconds);
}

void	state_writer(t_table *table, int philo, char *str)
{
	if (table->exit == true)
		return ;
	sem_wait(table->lock);
	printf("%lu %d %s\n", timestamp() - table->start_time, philo, str);
	sem_post(table->lock);
	return ;
}
