/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <eduhgb5198@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:44:57 by eherrero          #+#    #+#             */
/*   Updated: 2021/05/07 14:22:00 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "utils.h"
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
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
	int				pid;
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
	sem_t			*tcsem;
	sem_t			*diesem;
	long long int	will_die;
	int				*control;
}	t_philo;

typedef struct s_control
{
	t_philo	*arr;
	sem_t	*log;
	sem_t	*forks;
	sem_t	*tcsem;
	sem_t	*diesem;
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
void	*target_checker(void *d);
void	*dead_checker(void *d);

#endif