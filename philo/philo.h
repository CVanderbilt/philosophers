#ifndef PHILO_H
# define PHILO_H
# include "utils.h"
# include <pthread.h>

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
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	pthread_mutex_t *log;
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
	pthread_mutex_t *forks;
	int				*forks_status;
	pthread_mutex_t log;
	int				philosophers_ended;
	int				target;
	int				ttd;
	int				tte;
	int				tts;
	int				num;
	int				who_died;
}	t_control;

void	*philo_thread(void *d);
int		awake_philo(t_philo *p, int *control);
#endif