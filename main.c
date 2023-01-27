/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:42:29 by aberneli          #+#    #+#             */
/*   Updated: 2022/01/06 15:57:40 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_death(t_table *t)
{
	pthread_mutex_lock(&t->dying);
	t->death++;
	pthread_mutex_unlock(&t->dying);
}

int	read_death(t_table *t)
{
	int	res;

	pthread_mutex_lock(&t->dying);
	res = t->death;
	pthread_mutex_unlock(&t->dying);
	return (res);
}

void	*ft_memset(void *p, int val, size_t len)
{
	uint8_t	*mem;
	size_t	i;

	mem = p;
	i = 0;
	while (i < len)
	{
		mem[i] = val;
		i++;
	}
	return (p);
}

static int	read_args(t_settings *settings, int flag, char **argv)
{
	settings->num = check_nbr(argv[1]);
	settings->time_to_die = check_nbr(argv[2]);
	settings->time_to_eat = check_nbr(argv[3]);
	settings->time_to_sleep = check_nbr(argv[4]);
	if (settings->num < 1)
		return (0);
	if (settings->time_to_die < 1)
		return (0);
	if (settings->time_to_eat < 1)
		return (0);
	if (settings->time_to_sleep < 1)
		return (0);
	settings->must_eat_times = INT32_MAX;
	if (flag)
	{
		settings->must_eat_times = check_nbr(argv[5]);
		if (settings->must_eat_times < 1)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	ft_memset(&table, 0, sizeof(table));
	if (argc < 5 || argc > 6)
		return (0);
	if (!read_args(&table.settings, argc == 6, argv))
		return (0);
	table.amount = table.settings.num;
	init_table(&table);
	thread_start(&table);
	flip_table(&table);
	return (0);
}
