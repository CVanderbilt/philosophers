/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
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

int	philo_act(t_philo *p)
{
	long long int	aux;

	while (1)
	{
		sem_wait(p->forks);
		aux = ft_now();
		numbered_philo_log(p, "has taken a fork", aux);
		numbered_philo_log(p, "has taken a fork", aux);
		p->will_die = aux + p->ttd;
		numbered_philo_log(p, "is eating", aux);
		p->times_eaten++;
		if (p->times_eaten == p->target)
			sem_post(p->tcsem);
		smart_sleep(aux + p->tte);
		aux = ft_now();
		numbered_philo_log(p, "is sleeping", aux);
		sem_post(p->forks);
		sem_post(p->forks);
		smart_sleep(aux + p->tts);
		philo_log(p, "is thinking", 0);
	}
	while (1)
		usleep(50);
	return (1);
}

void	*philo_checker(void *d)
{
	t_philo			*p;
	long long int	t;

	p = (t_philo *)d;
	while (42)
	{
		t = ft_now();
		if (t >= p->will_die)
		{
			sem_wait(p->log);
			philo_log(p, "died", 1);
			sem_post(p->diesem);
			return (0);
		}
		usleep(1000);
	}
}

void	*philo_thread(void *d)
{
	t_philo			*p;
	pthread_t		cid;

	p = (t_philo *)d;
	if (pthread_create(&cid, 0, philo_checker, d))
		return (0);
	pthread_detach(cid);
	philo_act(p);
	return (0);
}

int	awake_philo(t_philo *p, int *control)
{
	p->control = control;
	p->will_die = ft_now() + p->ttd;
	return ((int)philo_thread(p));
}
