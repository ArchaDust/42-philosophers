/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:07:31 by aberneli          #+#    #+#             */
/*   Updated: 2022/01/06 15:29:56 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_start(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->amount)
	{
		table->philos[i].id = i;
		table->philos[i].ctx = table;
		table->philos[i].status = S_THINK;
		pthread_create(&table->philos[i].tid, NULL, philo_entry, \
				&table->philos[i]);
		i++;
	}
	i = 0;
	while (i < table->amount)
	{
		pthread_join(table->philos[i].tid, NULL);
		i++;
	}
}

int	flip_table(t_table *table)
{
	int	i;

	if (table->forks)
	{
		i = 0;
		while (i < table->amount)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
	}
	free(table->forks);
	free(table->philos);
	pthread_mutex_destroy(&table->chat);
	pthread_mutex_destroy(&table->dying);
	return (0);
}

int	init_table(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->chat, NULL);
	pthread_mutex_init(&table->dying, NULL);
	table->philos = malloc(table->amount * sizeof(t_philo));
	if (!table->philos)
		return (flip_table(table));
	ft_memset(table->philos, 0, table->amount * sizeof(t_philo));
	table->forks = malloc(table->amount * sizeof(t_mutex));
	if (!table->forks)
		return (flip_table(table));
	while (i < table->amount)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return (1);
}
