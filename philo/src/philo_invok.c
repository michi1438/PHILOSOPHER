/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_invok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:46:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/13 12:08:47 by mguerga          ###   ########.fr       */
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
	pthread_mutex_t	mut;
	int				i;

	stbl_name = philos->name;
	comp = philos->compend;
	pthread_mutex_init(&mut, NULL);
	i = 0;
	while (i < comp.t_death / 100)
	{
		usleep(100);
		i++;
		pthread_mutex_lock(&mut);
		if (has_2_forks(comp, stbl_name) == 1)
		{
			i = 0;
			is_eating(comp, stbl_name);
			printlog(SLEEP, stbl_name);
			usleep(comp.t_sleep);
			printlog(THINK, stbl_name);
		}
		pthread_mutex_unlock(&mut);
	}
	printlog(DIE, stbl_name);
	exit (10); // TODO illegal I believe
}

void	is_eating(t_comp comp, int stbl_name)
{
	comp.forks[stbl_name] = 0;
	printlog(FORK, stbl_name);
	comp.forks[stbl_name - 1] = 0;
	printlog(FORK, stbl_name); // TODO must he pick both fork individualy
	printlog(EAT, stbl_name);
	usleep(comp.t_eat);
	comp.forks[stbl_name] = 1;
	comp.forks[stbl_name - 1] = 1;
}
