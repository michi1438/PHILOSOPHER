/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_philo_invok.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:05:20 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/29 18:08:04 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo_bonus.h"

int	create_philos(t_philos *philos)
{
	int		i;
	t_comp	*comp;

	i = 0;
	comp = &philos->compend;
	while (i < comp->n_philo)
	{
		philos->process[i] = fork();
		if (philos->process[i] == 0)
		{
			philos->process[0] = i;
			return (child_play(philos));
		}
		else
			i++;
	}
	return (0);
}

int	child_play(t_philos *philos)
{
	t_comp	*comp;
	int		i;

	i = 0;
	comp = &philos->compend;
	//if (has_2_forks(semaphore) == 1) ;
	print_log(philos->process[0], CREATE);
	while (i <= comp->t_death)
	{
		print_log(philos->process[0], FORK);
		usleep(comp->t_eat * 1000);
		print_log(philos->process[0], SLEEP);
		usleep(comp->t_sleep * 1000);
		print_log(philos->process[0], THINK);
		i++;
	}
	print_log(philos->process[0], DIE);
	return (1);
}
