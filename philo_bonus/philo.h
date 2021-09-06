#ifndef PHILO_H
# define PHILO_H
# include "utils.h"
# include <pthread.h>
# include <fcntl.h>           /* For O_* constants */
# include <sys/stat.h>        /* For mode constants */
# include <semaphore.h>

typedef enum e_status
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING
}	t_status;

typedef struct s_philo
{
	pthread_t		tid;
	sem_t			*forks;
	sem_t			*log;
	int				id;
	int				ttd;
	int				tte;
	int				tts;
	int				times_eaten;
	int				target;
	int				*target_counter;
	long long int	will_die;
	int				*control;
}	t_philo;

typedef struct s_control
{
	t_philo	*arr;
	sem_t	*log;
	sem_t	*forks;
	int		philosophers_ended;
	int		target;
	int		ttd;
	int		tte;
	int		tts;
	int		num;
	int		who_died;
}	t_control;

void	*philo_thread(void *d);
int		awake_philo(t_philo *p, int *control);
void	numbered_philo_log(t_philo *p, const char *str, long int n);
void	philo_log(t_philo *p, const char *str, int ignore);
#endif