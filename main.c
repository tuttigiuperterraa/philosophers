/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:33:48 by gcosenza          #+#    #+#             */
/*   Updated: 2024/04/09 17:08:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_input(char **argv, int n)
{
	int	i;
	int	j;

	i = 1;
	while (i < n)
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' && argv[i][j] != 20) || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
unsigned long	*ft_atoi(const char *nptr)
{
	int	i;
	unsigned long	num;
	unsigned long	*ptr_num;

	i = 0;
	num = 0;
	while (nptr[i] == ' ')
				i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		num = 10 * num + nptr[i] - 48;
		i++;
	}
	ptr_num = &num;
	return (ptr_num);
}

void	set_param(char **argv, t_params *params)
{
	(*params).n_philos = *ft_atoi(argv[1]);
	(*params).t_die = *ft_atoi(argv[2]);
	(*params).t_eat = *ft_atoi(argv[3]);
	(*params).t_sleep = *ft_atoi(argv[4]);
	if (argv[5])
		(*params).n_eat = ft_atoi(argv[5]);
	else
		(*params).n_eat = (void *)NULL;
}

void	fork_init(t_params *params)
{
	int i;

	i = 0;
	while (i < params->n_philos)
	{
		safe_mutex(&params->forks[i].fork, INIT);
		params->forks[i].fid = i;
		i++;
	}
}
take_forks(t_philo *philo, t_fork *forks, int sit)
{
	philo->second = &forks[sit];
	philo->first = &forks[(philo->params->n_philos + 1) % philo->params->n_philos];
	if (philo->pid % 2)
	{
		philo->first = &forks[sit];
		philo->second = &forks[(philo->params->n_philos + 1) % philo->params->n_philos];
	}	
}
void	philo_init(t_params *params)
{
	int i;
	t_philo *philo;

	i = 0;
	while (i < params->n_philos)
	{
		philo = params->philos + 1;
		philo->pid = i + 1;
		philo->full = false;
		philo->n_eat = 0;
		philo->params = params;
		take_forks(philo, params->forks, i);

	}
}

void	wait_threads(t_params *params)
{
	while(!(params->all_ready == true))
		;
}

void	*events(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;

	wait_threads(philo->params);
	while(1)
	{

	}

	return(NULL);
}

void	dinner(t_params *params)
{
	int i;

	i = 0;
	if(*(params->n_eat) == 0)
		return;
	//if(params->n_philos == 1)
		//TODO;
	else
	{
		while(i < params->n_philos);
		{
			safe_thread(&params->philos[i].tid, events, &params->philos[i], CREATE);
			i++;
		}
		safe_mutex(params->table_mutex, LOCK);
		params->all_ready = true;
		safe_mutex(params->table_mutex, UNLOCK);
		//get_time
	}

}

void	invite_philo(t_params *params)
{
	params->end = false;
	params->all_ready = false;
	params->philos = safe_malloc(sizeof(t_philo) * params->n_philos);
	safe_mutex(&params->table_mutex, INIT);
	params->forks = safe_malloc(sizeof(t_fork) * params->n_philos);
	fork_init(params);
	philo_init(params);
}

int	 main(int argc, char **argv)
{
	t_params	params;
	t_philo		**philos;

	if (argc != 5 && argc != 6)
		error_exit("Wrong number of arguments");
	if (!check_input(argv, argc))
		error_exit("Only positive unsigned numbers accepted"); //all params should be numbers
	set_param(argv, &params); //convert char to numbers and fill the struct
	invite_philo(&params);
	dinner(&params);//TODO
	//Clean-TODO
	return (0);
}
