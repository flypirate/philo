/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 21:15:43 by albegar2          #+#    #+#             */
/*   Updated: 2026/03/11 12:45:07 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watcher_routine(void *arg)
{
	t_table	*table;
	int		i;
	long	start_time;

	table = (t_table *)arg;
	while (1)
	{
		table->count = 0;
		i = 0;
		while (i < table->numphilo)
		{
			start_time = get_time() - table->start_time;
			pthread_mutex_lock(&table->dead_mutex);
			if (table->dead_check == 1)
				return (dead_philo(start_time, table, i));
			pthread_mutex_unlock(&table->dead_mutex);
			check_eaten(table, i);
			if (!check_timing(table, i, start_time))
				return (NULL);
			i++;
		}
		if (!check_full(table))
			return (NULL);
	}
}

int	check_full(t_table *table)
{
	pthread_mutex_lock(&table->data_mutex);
	if (table->count == table->numphilo)
		return (pthread_mutex_unlock(&table->data_mutex), 0);
	pthread_mutex_unlock(&table->data_mutex);
	usleep(50);
	return (1);
}

void	check_eaten(t_table *table, int i)
{
	pthread_mutex_lock(&table->thread_data[i]->philo_mutex);
	pthread_mutex_lock(&table->data_mutex);
	if (table->must_eat > 0
		&& (table->thread_data[i]->eaten >= table->must_eat))
		table->count++;
}

int	check_timing(t_table *table, int i, long start_time)
{
	long	timesince_lm;

	timesince_lm = get_time() - table->thread_data[i]->last_meal_time;
	if (timesince_lm > table->tdie)
	{
		pthread_mutex_unlock(&table->data_mutex);
		pthread_mutex_unlock(&table->thread_data[i]->philo_mutex);
		pthread_mutex_lock(&table->dead_mutex);
		return (dead_philo(start_time, table, i), 0);
	}
	pthread_mutex_unlock(&table->data_mutex);
	pthread_mutex_unlock(&table->thread_data[i]->philo_mutex);
	return (1);
}

void	*dead_philo(long time, t_table *table, int i)
{
	table->dead_check = 1;
	pthread_mutex_lock(&table->print_mutex);
	pthread_mutex_lock(&table->thread_data[i]->philo_mutex);
	printf("%ld %d %s\n", time, table->thread_data[i]->philoid, "has died");
	pthread_mutex_unlock(&table->print_mutex);
	pthread_mutex_unlock(&table->thread_data[i]->philo_mutex);
	pthread_mutex_unlock(&table->dead_mutex);
	return (NULL);
}
