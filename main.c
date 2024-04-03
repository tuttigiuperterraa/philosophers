/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosenza <gcosenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:33:48 by gcosenza          #+#    #+#             */
/*   Updated: 2024/04/03 08:57:54 by gcosenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef	struct	s_param
{
	unsigned int	n_philos;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	n_eat;
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

void	set_param(char **argc, int argv, t_params params)
{
	//atoi
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
		write(1, "Only positive int accepted\n", 27);
		return(1);
	}
	set_param(argv,argc, params); //convert char to numbers and fill the struct
	return (0);
}