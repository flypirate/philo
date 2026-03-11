/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:54:19 by albegar2          #+#    #+#             */
/*   Updated: 2026/03/11 12:43:29 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h> 
# include <sys/time.h>
# include <string.h>

typedef struct s_table
{
	int				numphilo;
	int				tdie;
	int				tsleep;
	int				teat;
	int				must_eat;
	int				dead_check;
	long			start_time;
	int				count;
	pthread_mutex_t	*forks;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		*philoid;
	pthread_t		watcher;
	struct s_thread	**thread_data;
}	t_table;

typedef struct s_thread
{
	int				philoid;
	int				eaten;
	int				fork_right;
	int				fork_left;
	long			last_meal_time;
	pthread_mutex_t	philo_mutex;
	struct s_table	*table_data;
}	t_thread;

int			parsing(int argc, char **argv);
int			isposnum(char *arg);
void		custom_sleep(long time, t_thread *thread);
int			fill_struct(int argc, char **argv, t_table *table);
int			create_philos(t_table *table, t_thread **thread);
int			manage_philos(t_table *table, t_thread **thread);
void		routine(void *arg);
int			ft_atoi(char *arg, int *atoi_check);
long		get_time(void);
int			join_philos(t_table *table);
void		*watcher_routine(void *arg);
void		cleaning_tool(t_table *table, t_thread **thread);
t_thread	**cmallocs(t_table *table);
void		safeprint(t_table *table, int id, char *msg);
void		destroy_mutex(t_table *table);
void		routine4one(void *arg);
int			eating(t_thread *thread);
void		sleep_and_think(t_thread *thread);
int			fill_and_launch(t_table *table, t_thread **thread, int i);
void		*dead_philo(long time, t_table *table, int i);
int			check_timing(t_table *table, int i, long start_time);
void		check_eaten(t_table *table, int i);
int			check_pfinish(t_thread *thread, int first, int second);
int			check_dead(t_thread *thread);
int			check_full(t_table *table);

#endif 
