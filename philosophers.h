#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_fork t_fork;
typedef struct s_philo t_philo;

typedef	struct	s_param
{
	unsigned long	n_philos;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	unsigned long	start_dinner;
	unsigned long	*n_eat;
	bool 			end;
	t_fork			*forks;
	t_philo			*philos;
}	t_params;

struct s_fork
{
	int 	fid;
	pthread_mutex_t fork;

};

struct s_philo
{
	int			pid;
	pthread_t	tid;
	long	n_eat;
	t_fork	sx;
	t_fork	dx;
	long	last_meal_time;
};

void    error_exit(char *msg);

#endif