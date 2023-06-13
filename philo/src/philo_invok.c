/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_invok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:46:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/12 09:52:52 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

void	create_philos(t_philos *philos)
{
	int		i;
	t_comp	comp;

	comp = philos->compend;
	philos->thread = malloc(sizeof(int) * comp.n_philo + 1);
	i = 0;
	while (i < comp.n_philo)
	{
		usleep(100);
		init_philos(philos, i);
		i++;
	}
	i = 0;
	while (i < comp.n_philo)
	{
		usleep(100);
		pthread_join(philos->thread[i], NULL);
		i++;
	}
}

void	init_philos(t_philos *philos, int i)
{
	philos->name = i;
	pthread_create(&(philos->thread[i]), NULL, (void *)hello, philos);
//	pthread_detach(philos->thread[i]);
}

void	*hello(t_philos *philos)
{
	t_comp			comp;
	int				stbl_name;
	struct timeval	tv;

	stbl_name = philos->name;
	comp = philos->compend;
	if (comp.forks[stbl_name] && comp.forks[stbl_name - 1])
	{
		comp.forks[stbl_name] = 0;
		comp.forks[stbl_name - 1] = 0;
		gettimeofday(&tv, NULL);
		printf("%ld.%ld %d got 2 forks\n", tv.tv_sec % 100, tv.tv_usec / 1000, stbl_name + 1);
	}
	usleep(comp.t_death);
	gettimeofday(&tv, NULL);
	printf("%ld.%ld %d has died\n", tv.tv_sec % 100, tv.tv_usec / 1000, stbl_name + 1);
	return (NULL);
}
