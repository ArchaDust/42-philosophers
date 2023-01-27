/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlib.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:18:28 by aberneli          #+#    #+#             */
/*   Updated: 2022/01/05 15:38:13 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *s)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (s[i])
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	return (n);
}

int	check_nbr(char *nbr)
{
	int64_t	n;
	int		i;

	if (ft_strlen(nbr) > 11)
		return (-1);
	i = 0;
	while (nbr[i])
	{
		if (nbr[i] < '0' || nbr[i] > '9')
			return (-1);
		i++;
	}
	n = ft_atoi(nbr);
	if (n > INT32_MAX || n < 0)
		return (-1);
	return (n);
}
