/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_philo_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:31:22 by mguerga           #+#    #+#             */
/*   Updated: 2023/07/20 10:12:44 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo_bonus.h"

void	philo_init(int ac, char **av, t_philos *philos)
{
	t_comp	*comp;

	comp = &philos->compend;
	comp->n_philo = ft_atoi(av[1]);
	comp->t_death = ft_atoi(av[2]);
	comp->t_eat = ft_atoi(av[3]);
	comp->t_sleep = ft_atoi(av[4]);
	comp->n_cycles = -1;
	if (ac == 6)
		comp->n_cycles = ft_atoi(av[5]);
	comp->forks = comp->n_philo;
	init_semaphore(philos);
	init_process(philos);
}

void	init_process(t_philos *philos)
{
	t_comp	*comp;

	comp = &philos->compend;
	philos->process = malloc(sizeof(*philos->process) * comp->n_philo);
}

void	init_semaphore(t_philos *philos)
{
	t_comp	*comp;

	comp = &philos->compend;
	sem_unlink("/forks");
	sem_unlink("/wwait");
	sem_unlink("/wwait2");
	philos->semaphore = sem_open("/forks", O_CREAT, 0777, comp->n_philo);
	philos->semaphore_wwait = sem_open("/wwait", O_CREAT, 0777, 1);
	philos->semaphore_wwait2 = sem_open("/wwait2", O_CREAT, 0777, 1);
}
