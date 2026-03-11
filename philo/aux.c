/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:19:16 by albegar2          #+#    #+#             */
/*   Updated: 2026/03/10 20:56:33 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *arg, int *atoi_check)
{
	long	num;
	long	sign;
	long	i;

	num = 0;
	sign = 1;
	i = 0;
	while (arg[i] < 48 || arg[i] > 57)
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	while (arg[i] >= 48 && arg[i] <= 57)
	{
		num = num * 10;
		num = num + (arg[i] - '0');
		i++;
	}
	num = num * sign;
	if (num > 2147483647 || num < 0)
		return (*atoi_check = 1, 1);
	else
		return (num);
}

int	isposnum(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < 48 || arg[i] > 57)
			return (1);
		else
			i++;
	}
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	cleaning_tool(t_table *table, t_thread **thread)
{
	int	i;

	i = 0;
	if (thread)
	{
		while (i < table->numphilo)
		{
			free(thread[i]);
			i++;
		}
		free(thread);
	}
	if (table)
	{
		if (table->forks)
			free(table->forks);
		if (table->philoid)
			free(table->philoid);
		free(table);
	}
}

void	custom_sleep(long time, t_thread *thread)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
	{
		pthread_mutex_lock(&thread->table_data->dead_mutex);
		if (thread->table_data->dead_check == 1)
		{
			pthread_mutex_unlock(&thread->table_data->dead_mutex);
			return ;
		}
		pthread_mutex_unlock(&thread->table_data->dead_mutex);
		usleep(100);
	}
}
