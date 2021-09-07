/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
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

void	smart_sleep(long long end)
{
	while (ft_now() < end)
		usleep(50);
}

int	philo_act(t_philo *p, pthread_mutex_t *first, pthread_mutex_t *last)
{
	long long int	aux;

	while (!*p->kill_himself)
	{
		pthread_mutex_lock(first);
		numbered_philo_log(p, "has taken a fork", ft_now());
		pthread_mutex_lock(last);
		aux = ft_now() + p->tte;
		p->will_die = aux + p->ttd - p->tte;
		numbered_philo_log(p, "has taken a fork", ft_now());
		numbered_philo_log(p, "is eating", aux - p->tte);
		p->times_eaten++;
		if (p->times_eaten == p->target)
			*p->target_counter += 1;
		smart_sleep(aux);
		aux = ft_now() + p->tts;
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(last);
		numbered_philo_log(p, "is sleeping", aux - p->tts);
		smart_sleep(aux);
		numbered_philo_log(p, "is thinking", aux);
		usleep(500);
	}
	return (1);
}

void	*philo_checker(void *d)
{
	t_philo			*p;
	long long int	t;

	p = (t_philo *)d;
	while (42)
	{
		if (*p->kill_himself)
			return (0);
		t = ft_now();
		if (t >= p->will_die)
		{
			if (*p->control >= 0)
				return (0);
			philo_log(p, "died", 0);
			*p->control = p->id;
			return (0);
		}
		usleep(1000);
	}
}

void	*philo_thread(void *d)
{
	t_philo			*p;
	pthread_t		cid;
	pthread_mutex_t	*first;
	pthread_mutex_t	*last;

	p = (t_philo *)d;
	first = p->right;
	last = p->left;
	if (p->id % 2 != 0)
	{
		first = p->left;
		last = p->right;
	}
	if (pthread_create(&cid, 0, philo_checker, d))
		return (0);
	pthread_detach(cid);
	philo_act(p, first, last);
	return (0);
}

int	awake_philo(t_philo *p, int *control)
{
	p->control = control;
	p->will_die = ft_now() + p->ttd;
	return (pthread_create(&p->tid, 0, philo_thread, p));
}
