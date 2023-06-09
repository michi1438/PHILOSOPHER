/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_invok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:46:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/09 10:59:53 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

void	create_philos(t_philos *philos)
{
	int		i;
	t_comp	comp;

	comp = philos->compend;
	i = 1;
	while (i <= comp.n_philo)
	{
		init_philos(philos, i);
		i++;
	}
	i = 1;
}

int	init_philos(t_philos *philos, int i)
{
	philos->name = i;
	pthread_create(&philos->thread, NULL, (void *)hello, philos);
	pthread_join(philos->thread, NULL);
	return (0);
}

void	*hello(t_philos *philos)
{
	t_comp			comp;
	struct timeval	tv;

	comp = philos->compend;
	gettimeofday(&tv, NULL);
	printf("%ld.%ld %d has taken a fork\n", tv.tv_sec % 100, tv.tv_usec / 1000, philos->name);
	usleep(comp.t_death);
	printf("philo %d has died\n", philos->name);
	return (NULL);
}
