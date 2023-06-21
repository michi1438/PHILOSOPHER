/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:35:02 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/21 15:13:32 by mguerga          ###   ########.fr       */
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
		init_forks(compend);
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

void	init_forks(t_comp *compend)
{
	char	fork_ini[compend->n_philo];

	compend->forks = memset(fork_ini, 1, compend->n_philo);
}
