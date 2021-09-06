// number_of_philosophers 
//time_to_die 
//time_to_eat
//time_to_sleep
//[number_of_times_each_philosopher_must_eat]
#include "philo.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	init(int argc, char *argv[], t_control *c)
{
	int	i;

	if (pthread_mutex_init(&c->log, 0))
		return (0);
	c->who_died = -1;
	c->philosophers_ended = 0;
	if (argc < 5 || argc > 6
	|| !ft_str_is_int(argv[1]) || !ft_str_is_int(argv[2])
	|| !ft_str_is_int(argv[3]) || !ft_str_is_int(argv[4]))
		return (0);
	c->num = ft_atoi(argv[1]);
	if (c->num <= 0)
		return (0);
	c->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * c->num);
	if (!c->forks)
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
	c->arr = (t_philo *)malloc(sizeof(t_philo) * c->num);
	if (!c->arr)
		return (0);
	i = -1;
	while (++i < c->num)
	{
		if (pthread_mutex_init(&c->forks[i], 0))
			return (0);
		c->arr[i].id = i;
		c->arr[i].ttd = c->ttd;
		c->arr[i].tte = c->tte;
		c->arr[i].tts = c->tts;
		c->arr[i].left = &c->forks[i];
		c->arr[i].right = &c->forks[(i + 1) % c->num];
		c->arr[i].log = &c->log;
		c->arr[i].times_eaten = 0;
		c->arr[i].target_counter = &c->philosophers_ended;
		c->arr[i].target = c->target;
	}
	return (1);
}

int	awake_philos(t_control *c)
{
	int	i;

	i = -1;
	while (++i < c->num)
	{
		if (awake_philo(&c->arr[i], &c->who_died))
			return (1);
		pthread_detach(c->arr[i].tid);
//		if (i % 2)
//			usleep(15000);
	}
	while (1)
		if ((c->who_died >= 0)
			|| (c->target >= 0 && c->philosophers_ended >= c->num))
			break ;
	usleep(c->ttd * 1000);
	return (0);
}

int main(int argc, char *argv[])
{
	t_control c;

	if (!init(argc, argv, &c))
	{
		write(1, "Invalid arguments\n", 18);
		return (1);
	}
	//awake_philos(&c);
	//write(1, "ttd: ", 5); ft_putnbr(c.ttd);
	//write(1, "tte: ", 5); ft_putnbr(c.tte);
	//write(1, "tts: ", 5); ft_putnbr(c.tts);
	return (awake_philos(&c));
}