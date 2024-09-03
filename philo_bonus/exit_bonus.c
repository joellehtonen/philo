/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:44:32 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/03 16:48:48 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void close_semaphores(t_table *table);
{
	
}

static void	free_memory(t_table *table)
{
	unsigned int	i;

	if (table == NULL)
		return ;
	i = 0;
	while (i < table->philos_total)
	{
		free(table->philo[i]);
		i++;
	}
	free(table->philo);
	free(table);
}


void	free_and_exit(t_table *table)
{
	close_semaphores(table);
	free_memory(table);
	return ;
}