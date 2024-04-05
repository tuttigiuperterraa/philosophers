/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:33:48 by gcosenza          #+#    #+#             */
/*   Updated: 2024/04/05 15:08:42 by marvin           ###   ########.fr       */
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

int	 main(int argc, char **argv)
{
	t_params	params;

	if (argc != 5 && argc != 6)
		error_exit("Wrong number of arguments");
	if (!check_input(argv, argc))
		error_exit("Only positive unsigned numbers accepted"); //all params should be numbers
	set_param(argv, &params); //convert char to numbers and fill the struct
	//dinner();//TODO
	//Clean-TODO
	return (0);
}