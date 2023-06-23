/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:35:02 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/23 16:52:59 by mguerga          ###   ########.fr       */
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
		init_tv_has_eaten(compend);
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
	int	i;

	i = 0;
	compend->forks = malloc(sizeof(char) * compend->n_philo);
	while (i < compend->n_philo)
	{
		compend->forks[i] = 1;
		i++;
	}
}

void	init_tv_has_eaten(t_comp *compend)
{
	int				i;
	struct timeval	*tv_buf;

	i = 0;
	tv_buf = malloc(sizeof(struct timeval));
	compend->tv_has_eaten = malloc(sizeof(struct timeval) * compend->n_philo);
	while (i < compend->n_philo)
	{
		gettimeofday(tv_buf, NULL);
		compend->tv_has_eaten[i] = tv_buf->tv_usec;
		i++;
	}
	free(tv_buf);
}
