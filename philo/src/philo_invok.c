/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_invok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:46:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/15 16:48:37 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

void	create_philos(t_philos *philos)
{
	int		i;
	t_comp	comp;

	comp = philos->compend;
	philos->thread = malloc(sizeof(int) * comp.n_philo + 1);
	pthread_mutex_init(&philos->name_mutex, NULL);  
	i = 0;
	while (i < comp.n_philo)
	{
		init_philos(philos, i);
		i++;
	}
	i = 0;
	while (i < comp.n_philo)
	{
		pthread_join(philos->thread[i], NULL);
		i++;
	}
}

void	init_philos(t_philos *philos, int i)
{
	pthread_create(&(philos->thread[i]), NULL, (void *)hello, philos);
//	pthread_detach(philos->thread[i]);
}

void	*hello(t_philos *philos)
{
	t_comp			comp;
	int				stbl_name;
	static int		enm;
	int				i;

	pthread_mutex_lock(&philos->name_mutex);
	printlog(CREATE, enm);
	stbl_name = enm++; 
	pthread_mutex_unlock(&philos->name_mutex);
	comp = philos->compend;
	i = 0;
	while (i < comp.t_death / 1000)
	{
		usleep(1000);
		i++;
		if (has_2_forks(philos, comp, stbl_name) == 1)
		{
			is_eating(philos, comp, stbl_name);
			i = 0;
			printlog(SLEEP, stbl_name);
			usleep(comp.t_sleep);
			printlog(THINK, stbl_name);
		}
	}
	printlog(DIE, stbl_name);
	exit (10); // TODO illegal I believe
}

void	is_eating(t_philos *philos, t_comp comp, int stbl_name)
{
	int	f_num;

	if (stbl_name == 0)
		f_num = comp.n_philo - 1;
	else
		f_num = stbl_name - 1;
	pthread_mutex_lock(&philos->name_mutex);
	comp.forks[stbl_name] = 0;
	printlog(FORK, stbl_name);
	comp.forks[f_num] = 0;
	printlog(FORK, stbl_name); // TODO must he pick both fork individualy
	pthread_mutex_unlock(&philos->name_mutex);
	printlog(EAT, stbl_name);
	usleep(comp.t_eat);
	pthread_mutex_lock(&philos->name_mutex);
	comp.forks[stbl_name] = 1;
	comp.forks[f_num] = 1;
	pthread_mutex_unlock(&philos->name_mutex);
}
