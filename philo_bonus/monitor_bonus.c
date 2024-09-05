/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:54:46 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/05 12:03:13 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all_processes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_total)
	{
		kill(table->pid[i], SIGKILL);
		i++;
	}
	return ;
}

void	global_monitor_routine(t_table *table)
{
	pid_t	died;
	int		i;
	
	while (true)
	{
		died = waitpid(0, NULL, WNOHANG);
		if (died > 0)
		{
			kill_all_processes(table);
			return ;
		}
		
	}
	return ;
}

int	local_monitor_routine(t_table *philo)
{
	size_t	time;
	int		signal_sent;
	
	signal_sent = 0;
	while (true)
	{
		time = timestamp(philo);
		if ((time - philo->last_meal) > philo->time_to_die)
		{
			return (philo->pid);
		}
		if (philo->meals_eaten >= philo->meals_required && signal_sent == 0)
		{
			sem_wait(philo->hungry);
			signal_sent = 1;
		}
	}
	return (0);
} 
