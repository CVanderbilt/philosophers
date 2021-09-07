/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <eduhgb5198@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:44:57 by eherrero          #+#    #+#             */
/*   Updated: 2021/05/07 14:22:00 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int	aux_init(t_control *c)
{
	int	i;

	i = -1;
	sem_unlink("forks");
	sem_unlink("log");
	sem_unlink("tcsem");
	sem_unlink("diesem");
	c->diesem = sem_open("diesem", O_CREAT | O_EXCL, 0644, 0);
	c->tcsem = sem_open("tcsem", O_CREAT | O_EXCL, 0644, 0);
	c->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, c->num / 2);
	c->log = sem_open("log", O_CREAT | O_EXCL, 0644, 1);
	while (++i < c->num)
	{
		c->arr[i].id = i;
		c->arr[i].ttd = c->ttd;
		c->arr[i].tte = c->tte;
		c->arr[i].tts = c->tts;
		c->arr[i].forks = c->forks;
		c->arr[i].log = c->log;
		c->arr[i].tcsem = c->tcsem;
		c->arr[i].diesem = c->diesem;
		c->arr[i].times_eaten = 0;
		c->arr[i].target_counter = &c->philosophers_ended;
		c->arr[i].target = c->target;
	}
	return (1);
}

int	init(int argc, char *argv[], t_control *c)
{
	c->who_died = -1;
	c->philosophers_ended = 0;
	if (argc < 5 || argc > 6
		|| !ft_str_is_int(argv[1]) || !ft_str_is_int(argv[2])
		|| !ft_str_is_int(argv[3]) || !ft_str_is_int(argv[4]))
		return (0);
	c->num = ft_atoi(argv[1]);
	if (c->num <= 0)
		return (0);
	c->ttd = ft_atoi(argv[2]);
	c->tte = ft_atoi(argv[3]);
	c->tts = ft_atoi(argv[4]);
	if (c->ttd < 0 || c->tte < 0 || c->tts < 0)
		return (0);
	c->target = -1;
	if (argc == 6)
	{
		c->target = ft_atoi(argv[5]);
		if (!ft_str_is_int(argv[5]) || c->target < 0)
			return (0);
	}
	c->arr = (t_philo *)malloc(sizeof(t_philo *) * c->num);
	if (!c->arr)
		return (0);
	return (aux_init(c));
}

void	*target_checker(void *d)
{
	t_control	*c;
	int			i;

	c = (t_control *)d;
	if (c->target < 0)
		return (0);
	i = -1;
	while (++i < c->num)
		sem_wait(c->tcsem);
	sem_wait(c->log);
	c->philosophers_ended = c->num;
	return (0);
}

void	*dead_checker(void *d)
{
	t_control	*c;

	c = (t_control *)d;
	sem_wait(c->diesem);
	c->who_died = 1;
	return (0);
}

int	awake_philos(t_control *c)
{
	int			i;
	pthread_t	cid;

	i = -1;
	while (++i < c->num)
	{
		c->arr[i].pid = fork();
		if (c->arr[i].pid < 0)
			return (0);
		if (!c->arr[i].pid)
			if (awake_philo(&c->arr[i], &c->who_died))
				return (1);
	}
	pthread_create(&cid, 0, target_checker, c);
	pthread_detach(cid);
	pthread_create(&cid, 0, dead_checker, c);
	pthread_detach(cid);
	while (1)
		if ((c->who_died >= 0)
			|| (c->target >= 0 && c->philosophers_ended >= c->num))
			break ;
	i = -1;
	while (++i < c->num)
		kill(c->arr[i].pid, SIGINT);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_control	c;

	if (!init(argc, argv, &c))
	{
		write(1, "Invalid arguments\n", 18);
		return (1);
	}
	return (awake_philos(&c));
}
