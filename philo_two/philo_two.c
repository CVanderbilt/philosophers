#include "philo.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

void	philo_log(t_philo *p, const char *str, int ignore)
{
	if (!ignore)
		sem_wait(p->log);
	ft_putnbr(ft_now());
	write(1, " ", 1);
	ft_putnbr(p->id + 1);
	write(1, " ", 1);
	ft_putstr(str);
	write(1, "\n", 1);
	if (!ignore)
		sem_post(p->log);
}

int	philo_act(t_philo *p)
{
	while (1)
	{
		sem_wait(p->forks);
		philo_log(p, "has taken a fork", 0);
		philo_log(p, "has taken a fork", 0);
		p->will_die = ft_now() + p->ttd;
		philo_log(p, "is eating", 0);
		p->times_eaten++;
		if (p->times_eaten == p->target)
			*p->target_counter += 1;
		usleep(1000 * p->tte);
		philo_log(p, "is sleepin", 0);
		sem_post(p->forks);
		sem_post(p->forks);
		usleep(1000 * p->tts);
		philo_log(p, "is thinking", 0);
	}
	return (1);
}

void	*philo_checker(void *d)
{
	t_philo	*p;
	long long int	t;

	p = (t_philo *)d;
	while (42)
	{
		t = ft_now();
		if (t >= p->will_die)
		{
			sem_wait(p->log);
			philo_log(p, "died", 1);
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
	return (pthread_create(&p->tid, 0, philo_thread, p));
}