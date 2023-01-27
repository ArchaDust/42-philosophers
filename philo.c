/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:04:53 by aberneli          #+#    #+#             */
/*   Updated: 2022/01/06 15:49:41 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_die(t_philo *p, t_table *t)
{
	if (p->status == S_DEAD)
		return (0);
	if (timestamp() < p->date_to_die)
		return (1);
	if (read_death(t) != 0)
		return (0);
	write_death(t);
	p->status = S_DEAD;
	log_status(t, p, STATUSMSG_DIED);
	return (0);
}

static int	philo_eat(t_philo *p, t_table *t)
{
	if (p->status == S_DEAD || read_death(t) != 0 || timestamp() \
			>= p->date_to_die || p->ate_count >= t->settings.must_eat_times)
		return (0);
	pthread_mutex_lock(&t->forks[p->id]);
	log_status(t, p, STATUSMSG_FORK);
	if (read_death(t) != 0 || timestamp() >= p->date_to_die)
	{
		pthread_mutex_unlock(&t->forks[p->id]);
		return (0);
	}
	pthread_mutex_lock(&t->forks[(p->id + 1) % t->amount]);
	if (timestamp() >= p->date_to_die || read_death(t) != 0)
		return (rel_fork(&t->forks[p->id], &t->forks[(p->id + 1) % t->amount]));
	log_status(t, p, STATUSMSG_FORK);
	log_status(t, p, STATUSMSG_EAT);
	p->date_to_die = timestamp() + t->settings.time_to_die;
	p->date_for_action = timestamp() + t->settings.time_to_eat;
	while (timestamp() < p->date_for_action && timestamp() < p->date_to_die)
		msleep(1);
	rel_fork(&t->forks[p->id], &t->forks[(p->id + 1) % t->amount]);
	if (timestamp() >= p->date_to_die)
		return (0);
	p->ate_count++;
	return (1);
}

static int	philo_sleep(t_philo *p, t_table *t)
{
	if (p->status == S_DEAD || read_death(t) != 0 || timestamp() \
			>= p->date_to_die || p->ate_count >= t->settings.must_eat_times)
		return (0);
	log_status(t, p, STATUSMSG_SLEEP);
	p->date_for_action = timestamp() + t->settings.time_to_sleep;
	while (timestamp() < p->date_for_action)
	{
		msleep(1);
		if (timestamp() >= p->date_to_die)
			return (0);
	}
	if (read_death(t) != 0)
		return (0);
	log_status(t, p, STATUSMSG_THINK);
	return (1);
}

static void	*lonely(t_philo *p, t_table *t)
{
	pthread_mutex_lock(&t->forks[p->id]);
	log_status(t, p, STATUSMSG_FORK);
	while (timestamp() < p->date_to_die)
		msleep(1);
	log_status(t, p, STATUSMSG_DIED);
	pthread_mutex_unlock(&t->forks[p->id]);
	return (NULL);
}

void	*philo_entry(void *a)
{
	t_philo	*p;
	t_table	*t;

	p = (t_philo *)a;
	t = (t_table *)p->ctx;
	p->tstamp = timestamp();
	p->date_to_die = timestamp() + t->settings.time_to_die;
	if (t->amount == 1)
		return (lonely(p, t));
	if (p->id % 2 == 1)
		msleep(t->settings.time_to_eat / 2);
	while (p->status != S_DEAD && read_death(t) == 0 \
			&& p->ate_count < t->settings.must_eat_times)
	{
		philo_eat(p, t);
		philo_sleep(p, t);
		philo_die(p, t);
	}
	return (NULL);
}
