/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:54:42 by albegar2          #+#    #+#             */
/*   Updated: 2026/03/11 12:44:32 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(void *arg)
{
	t_thread	*thread;

	thread = (t_thread *)arg;
	if (thread->philoid % 2 != 0)
		usleep(50);
	while (1)
	{
		pthread_mutex_lock(&thread->table_data->dead_mutex);
		if (thread->table_data->dead_check == 1)
		{
			pthread_mutex_unlock(&thread->table_data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&thread->table_data->dead_mutex);
		if (!eating(thread))
			return ;
		sleep_and_think(thread);
	}
	return ;
}

void	take_forks(t_thread *thread, int first, int second)
{
	pthread_mutex_lock(&thread->table_data->forks[first]);
	safeprint(thread->table_data, thread->philoid, "has taken a fork");
	pthread_mutex_lock(&thread->table_data->forks[second]);
	safeprint(thread->table_data, thread->philoid, "has taken a fork");
}

int	eating(t_thread *thread)
{
	int	first;
	int	second;

	if (thread->philoid % 2 == 0)
	{
		first = thread->fork_left;
		second = thread->fork_right;
	}
	else
	{
		first = thread->fork_right;
		second = thread->fork_left;
	}
	if (!check_dead(thread))
		return (0);
	take_forks(thread, first, second);
	pthread_mutex_lock(&thread->philo_mutex);
	thread->last_meal_time = get_time();
	pthread_mutex_unlock(&thread->philo_mutex);
	safeprint(thread->table_data, thread->philoid, "is eating");
	custom_sleep(thread->table_data->teat, thread);
	if (!check_pfinish(thread, first, second))
		return (0);
	return (1);
}

void	sleep_and_think(t_thread *thread)
{
	long	csleep;

	safeprint(thread->table_data, thread->philoid, "is sleeping");
	custom_sleep(thread->table_data->tsleep, thread);
	safeprint(thread->table_data, thread->philoid, "is thinking");
	if (thread->table_data->numphilo % 2 != 0)
	{
		csleep = thread->table_data->teat * 2 - thread->table_data->tsleep;
		if (csleep < 0)
			csleep = 0;
		custom_sleep((csleep * 0.50), thread);
	}
}

void	routine4one(void *arg)
{
	t_thread	*thread;
	long		time;

	thread = (t_thread *)arg;
	time = get_time() - thread->table_data->start_time;
	safeprint(thread->table_data, thread->philoid, "has taken a fork");
	usleep(thread->table_data->tdie * 1000);
	printf("%ld %d %s\n", time, thread->philoid, "has died");
}
