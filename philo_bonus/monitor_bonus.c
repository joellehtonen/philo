/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlehtone <jlehtone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:54:46 by jlehtone          #+#    #+#             */
/*   Updated: 2024/09/06 13:40:16 by jlehtone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// first decrements cleanup semaphore to let children know it's time to finish
// waits until all children have acknowledged that they're ready to die
// then kills all processes with SIGTERM
void	kill_all_processes(t_table *table)
{
	unsigned int	i;

	i = 0;
	sem_wait(table->start_cleanup);
	while (true)
	{
		if (sem_wait(table->ready_to_die) == 0)
			sem_post(table->ready_to_die);
		else
			break ;
	}
	while (i < table->philos_total)
	{
		kill(table->pid[i], SIGTERM);
		i++;
	}
	return ;
}

// global monitor that intermittenly checks if a child process has died
// also checks if hungry semaphore is 0 by trying to decrement it
// if successful (meaning semaphore is above 0), immediately increments it back
// kills all processes if a child has died or unable to decrement the semaphore
void	global_monitor_routine(t_table *table)
{
	pid_t	died;
	
	while (true)
	{
		died = waitpid(0, NULL, WNOHANG);
		if (died > 0)
		{
			kill_all_processes(table);
			return ;
		}
		if (sem_wait(table->hungry_left) == 0)
			sem_post(table->hungry_left);
		else
		{
			kill_all_processes(table);
			return ;
		}
		//usleep(10);
	}
	return ;
}

// personal monitor that checks if it's been too long since philo's last meal
// also checks if philo has eaten enough, and decrements semaphore once if so
void	*local_monitor_routine(void *data)
{
	size_t	time;
	int		signal_sent;
	t_table *philo;
	
	philo = (t_table *)data;
	signal_sent = 0;
	while (true)
	{
		time = timestamp(philo);
		if ((time - philo->last_meal) > philo->time_to_die)
		{
			// sem_wait(philo->child_died);
			child_cleanup(philo);
			return (NULL);
		}
		if (philo->meals_eaten >= philo->meals_required && signal_sent == 0)
		{
			sem_wait(philo->hungry_left);
			signal_sent = 1;
		}
		if (sem_wait(philo->start_cleanup) == 0)
			sem_post(philo->start_cleanup);
		else
			child_cleanup(philo);
		//usleep(10);
	}
} 
