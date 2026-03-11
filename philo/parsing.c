/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:54:58 by albegar2          #+#    #+#             */
/*   Updated: 2026/03/10 22:15:31 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		*table;
	t_thread	**thread;
	int			result;

	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (parsing(argc, argv) != 0 || fill_struct(argc, argv, table) != 0)
		return (free(table), 1);
	thread = cmallocs(table);
	if (!thread)
		return (cleaning_tool(table, thread), 1);
	result = manage_philos(table, thread);
	cleaning_tool(table, thread);
	return (result);
}

t_thread	**cmallocs(t_table *table)
{
	int			i;
	t_thread	**thread;

	i = 0;
	thread = malloc(sizeof(t_thread *) * table->numphilo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->numphilo);
	table->philoid = malloc(sizeof(pthread_t) * table->numphilo);
	table->thread_data = thread;
	if (!thread || !table->forks || !table->philoid)
		return (cleaning_tool(table, thread), NULL);
	while (i < table->numphilo)
	{
		thread[i] = malloc(sizeof(t_thread));
		if (!thread[i])
		{
			table->numphilo = i;
			cleaning_tool(table, thread);
			return (NULL);
		}
		memset(thread[i], 0, sizeof(t_thread));
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return (thread);
}

int	parsing(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (write(2, "Error: invalid arguments", 24), 1);
	while (i < argc)
	{
		if (isposnum(argv[i]) != 0)
			return (write(2, "Error: invalid arguments", 24), 1);
		else
			i++;
	}
	return (0);
}

int	fill_struct(int argc, char **argv, t_table *table)
{
	int	atoi_check;

	atoi_check = 0;
	table->dead_check = 0;
	table->numphilo = ft_atoi(argv[1], &atoi_check);
	table->tdie = ft_atoi(argv[2], &atoi_check);
	table->teat = ft_atoi(argv[3], &atoi_check);
	table->tsleep = ft_atoi(argv[4], &atoi_check);
	table->count = 0;
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5], &atoi_check);
	else
		table->must_eat = 0;
	if (table->numphilo < 1 || table->numphilo > 200 || table->must_eat < 0)
	{
		write(2, "Error: invalid arguments", 24);
		return (1);
	}
	if (atoi_check == 1)
	{
		write(2, "Error: invalid arguments", 24);
		return (1);
	}
	return (0);
}
