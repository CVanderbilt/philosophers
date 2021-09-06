#include "philo.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

void	numbered_philo_log(t_philo *p, const char *str, long int n)
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

void	philo_log(t_philo *p, const char *str, int ignore)
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

void		smart_sleep(long long end)
{
	while (ft_now() < end)
		usleep(50);
}

int	philo_act(t_philo *p, pthread_mutex_t *first, pthread_mutex_t *last)
{
	long long int aux;
	while (1)
	{
		pthread_mutex_lock(first);
//		philo_log(p, "has taken a fork", 0);
		numbered_philo_log(p, "has taken a fork", ft_now());
		pthread_mutex_lock(last);
		p->will_die = ft_now() + p->ttd;
		numbered_philo_log(p, "has taken a fork", ft_now());
//		philo_log(p, "has taken a fork", 0);
		aux = ft_now() + p->tte;
		numbered_philo_log(p, "is eating", aux - p->tte);
//		philo_log(p, "is eating", 0);
		p->times_eaten++;
		if (p->times_eaten == p->target)
			*p->target_counter += 1;
		smart_sleep(aux);
		//usleep(1000 * p->tte);
		aux = ft_now() + p->tts;
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(last);
		numbered_philo_log(p, "is sleeping", aux - p->tts);
//		philo_log(p, "is sleeping", 0);
		smart_sleep(aux);
		//usleep(1000 * p->tts);
		numbered_philo_log(p, "is thinking", aux);
//		philo_log(p, "is thinking", 0);
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
			pthread_mutex_lock(p->log);
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
	pthread_mutex_t	*first;
	pthread_mutex_t	*last;

	p = (t_philo *)d;
	first = p->right;
	last = p->left;
	if (p->id % 2)
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