/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:54:16 by albegar2          #+#    #+#             */
/*   Updated: 2026/03/10 20:52:57 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	manage_philos(t_table *table, t_thread **thread)
{
	if (create_philos(table, thread) != 0)
		return (1);
	pthread_join(table->watcher, NULL);
	if (join_philos(table) != 0)
		return (1);
	destroy_mutex(table);
	return (0);
}

int	create_philos(t_table *table, t_thread **thread)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->data_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->dead_mutex, NULL) != 0)
		return (1);
	table->start_time = get_time();
	while (i < table->numphilo)
	{
		if (fill_and_launch(table, thread, i) != 0)
			return (1);
		i++;
	}
	if (table->numphilo != 1)
	{
		if (pthread_create(&table->watcher, NULL, watcher_routine, table) != 0)
			return (1);
	}
	return (0);
}

int	fill_and_launch(t_table *table, t_thread **thread, int i)
{
	int	c;

	if (pthread_mutex_init(&thread[i]->philo_mutex, NULL) != 0)
		return (1);
	pthread_mutex_lock(&thread[i]->philo_mutex);
	thread[i]->philoid = i + 1;
	thread[i]->fork_left = i;
	thread[i]->fork_right = (i + 1) % table->numphilo;
	thread[i]->table_data = table;
	thread[i]->eaten = 0;
	thread[i]->last_meal_time = table->start_time;
	if (table->numphilo == 1)
		c = pthread_create(&table->philoid[i], NULL,
				(void *)routine4one, thread[i]);
	else
		c = pthread_create(&table->philoid[i], NULL,
				(void *)routine, thread[i]);
	if (c != 0)
	{
		while (i >= 0)
			pthread_mutex_unlock(&thread[i--]->philo_mutex);
		return (1);
	}
	pthread_mutex_unlock(&thread[i]->philo_mutex);
	return (0);
}

int	join_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->numphilo)
	{
		if (pthread_join(table->philoid[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->numphilo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->thread_data[i]->philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->data_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->dead_mutex);
}
