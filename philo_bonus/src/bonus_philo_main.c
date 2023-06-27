/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_philo_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:50:17 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/27 17:00:04 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo_bonus.h"

int	main(int ac, char **av)
{
	if (errors_nargs(ac, av) == -1)
	{
		printf("arguments should be 4 or 5, and only digits\n");
		return (1);
	}
	philo_init(av);
	//create_philos(&philos,  
	return (0);
}

int	errors_nargs(int ac, char **av)
{
	int	e;
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (-1);
	while (i < ac)
	{
		e = 0;
		while (av[i][e] != '\0')
		{
			if (av[i][e] < '0' || av[i][e] > '9')
				return (-1);
			e++;
		}
		i++;
	}
	return (0);
}
