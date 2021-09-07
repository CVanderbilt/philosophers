/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <eduhgb5198@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:44:57 by eherrero          #+#    #+#             */
/*   Updated: 2021/05/07 14:22:00 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

void	numbered_philo_log(t_philo *p, const char *str, long int n)
{
	if (!*p->kill_himself)
	{
		pthread_mutex_lock(p->log);
		ft_putnbr(n);
		write(1, " ", 1);
		ft_putnbr(p->id + 1);
		write(1, " ", 1);
		ft_putstr(str);
		write(1, "\n", 1);
		pthread_mutex_unlock(p->log);
	}
}

void	philo_log(t_philo *p, const char *str, int ignore)
{
	if (!*p->kill_himself)
	{
		if (!ignore)
			pthread_mutex_lock(p->log);
		ft_putnbr(ft_now());
		write(1, " ", 1);
		ft_putnbr(p->id + 1);
		write(1, " ", 1);
		ft_putstr(str);
		write(1, "\n", 1);
		if (!ignore)
			pthread_mutex_unlock(p->log);
	}
}
