/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:43:03 by aberneli          #+#    #+#             */
/*   Updated: 2022/01/06 15:54:39 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>

# define STATUSMSG_FORK "has taken a fork"
# define STATUSMSG_EAT "is eating"
# define STATUSMSG_SLEEP "is sleeping"
# define STATUSMSG_THINK "is thinking"
# define STATUSMSG_DIED "died"

typedef enum e_status
{
	S_THINK,
	S_EAT,
	S_SLEEP,
	S_DEAD
}			t_status;

typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	void		*ctx;
	uint64_t	tstamp;
	pthread_t	tid;
	uint64_t	date_for_action;
	uint64_t	date_to_die;
	int			id;
	int			ate_count;
	t_status	status;
}				t_philo;

typedef struct s_settings
{
	int			num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_times;
}				t_settings;

typedef struct s_table
{
	t_settings	settings;
	t_mutex		*forks;
	t_philo		*philos;
	t_mutex		chat;
	t_mutex		dying;
	int			amount;
	int			death;
}				t_table;

// main.c
void		write_death(t_table *t);
int			read_death(t_table *t);
void		*ft_memset(void *p, int val, size_t len);

// table.c
void		thread_start(t_table *table);
int			flip_table(t_table *table);
int			init_table(t_table *table);

// utils.c
void		log_status(t_table *t, t_philo *p, char *msg);
uint64_t	timestamp(void);
void		msleep(uint64_t twait);
int			rel_fork(t_mutex *m1, t_mutex *m2);

// philo.c
void		*philo_entry(void *p);

// mlib.c
size_t		ft_strlen(const char *str);
int			ft_atoi(const char *s);
int			check_nbr(char *nbr);

#endif
