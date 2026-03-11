/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 20:50:08 by albegar2          #+#    #+#             */
/*   Updated: 2026/03/11 12:42:53 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safeprint(t_table *table, int id, char *msg)
{
	int	is_dead;

	pthread_mutex_lock(&table->dead_mutex);
	is_dead = table->dead_check;
	pthread_mutex_unlock(&table->dead_mutex);
	if (is_dead == 0)
	{
		pthread_mutex_lock(&table->print_mutex);
		printf("%ld %d %s\n", get_time() - table->start_time, id, msg);
		pthread_mutex_unlock(&table->print_mutex);
	}
}

int	check_dead(t_thread *thread)
{
	pthread_mutex_lock(&thread->table_data->dead_mutex);
	if (thread->table_data->dead_check == 1)
	{
		pthread_mutex_unlock(&thread->table_data->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(&thread->table_data->dead_mutex);
	return (1);
}

int	check_pfinish(t_thread *thread, int first, int second)
{
	pthread_mutex_lock(&thread->philo_mutex);
	thread->eaten++;
	if (thread->eaten == thread->table_data->must_eat)
	{
		pthread_mutex_unlock(&thread->philo_mutex);
		pthread_mutex_unlock(&thread->table_data->forks[first]);
		pthread_mutex_unlock(&thread->table_data->forks[second]);
		return (0);
	}
	pthread_mutex_unlock(&thread->philo_mutex);
	pthread_mutex_unlock(&thread->table_data->forks[first]);
	pthread_mutex_unlock(&thread->table_data->forks[second]);
	return (1);
}
