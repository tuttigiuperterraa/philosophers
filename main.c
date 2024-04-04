/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:33:48 by gcosenza          #+#    #+#             */
/*   Updated: 2024/04/04 07:59:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

typedef	struct	s_param
{
	unsigned int	n_philos;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	*n_eat;
}	t_params;

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
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
unsigned int	*ft_atoi(const char *nptr)
{
	int	i;
	unsigned int	*num;

	i = 0;
	*num = 0;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		*num = 10 * *num + nptr[i] - 48;
		i++;
	}
	return (num);
}

void	set_param(int argc, char **argv, t_params *params)
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

int	 main(int argc, char **argv)
{
	int 		i;
	t_params	params;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		write(1, "Wrong number of arguments\n", 26);
		return(1);
	}
	if (!check_input(argv, argc)) //all params should be numbers
	{
		write(1, "Only positive unsigned int accepted\n", 27);
		return(1);
	}
	set_param(argc, argv, &params); //convert char to numbers and fill the struct
	return (0);
}
