/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:06:57 by aberneli          #+#    #+#             */
/*   Updated: 2022/01/06 15:33:31 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_status(t_table *t, t_philo *p, char *msg)
{
	uint64_t	tm;

	tm = timestamp() - p->tstamp;
	pthread_mutex_lock(&t->chat);
	if (read_death(t) == 0 || p->status == S_DEAD)
		printf("[%8llu] %d %s\n", tm, p->id, msg);
	pthread_mutex_unlock(&t->chat);
}

uint64_t	timestamp(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1e3 + tv.tv_usec * 1e-3);
}

void	msleep(uint64_t twait)
{
	uint64_t	target;

	target = timestamp() + twait;
	while (timestamp() < target)
		usleep(50);
}

int	rel_fork(t_mutex *m1, t_mutex *m2)
{
	pthread_mutex_unlock(m1);
	pthread_mutex_unlock(m2);
	return (0);
}
