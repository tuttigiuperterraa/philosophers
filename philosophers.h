#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

typedef struct s_fork t_fork;
typedef struct s_philo t_philo;

typedef	enum	e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,

} t_code;

typedef	struct	s_params
{
	unsigned long	n_philos;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	unsigned long	start_dinner;
	unsigned long	*n_eat;
	bool 			end;
	bool			all_ready;
	pthread_mutex_t table_mutex;
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
	t_fork	*first;
	t_fork	*second;
	t_params	*params;
	bool	full;
	bool	ready;
	long	last_meal_time;
};

void    error_exit(char *msg);
void *safe_malloc(size_t bytes);
void    handle_mutex_error(int status, t_code opc);
void safe_mutex(pthread_mutex_t *mutex, t_code opc);

#endif
