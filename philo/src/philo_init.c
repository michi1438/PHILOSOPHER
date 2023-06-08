/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:35:02 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/08 17:53:10 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

int	init_args(int ac, char **av, t_comp *compend)
{
	if (is_unsigned_int(av, ac) == -1)
		return (-1);
	if (ac == 6)
		compend->n_cycles = ft_atoi(av[5]);
	else
		compend->n_cycles = -1;
	if (ac == 5 || ac == 6)
	{
		compend->n_philo = ft_atoi(av[1]);
		compend->t_death = ft_atoi(av[2]);
		compend->t_eat = ft_atoi(av[3]);
		compend->t_sleep = ft_atoi(av[4]);
		return (0);
	}		
	else
		return (-1);
}

int	is_unsigned_int(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	init_philos(t_philos *philos, int i)
{
	philos->name = i;
	pthread_create(philos->thread, philos->attr, hello, NULL);
	return (0);
}

void	*hello(void *ptr)
{
	(void)ptr;
	printf("hello from the thread\n");
	return (NULL);
}
