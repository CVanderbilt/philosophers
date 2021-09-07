/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checkers.c                                    :+:      :+:    :+:   */
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
