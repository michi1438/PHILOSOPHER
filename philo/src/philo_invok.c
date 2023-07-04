/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_invok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:46:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/07/04 18:03:47 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

void	create_philos(t_philos *philos)
{
	t_comp			comp;
	int				i;

	comp = philos->compend;
	philos->thread = malloc(sizeof(pthread_t) * comp.n_philo);
	pthread_mutex_init(&philos->fork_mutex, NULL);
	pthread_mutex_init(&philos->name_mutex, NULL);
	pthread_mutex_init(&philos->eaten_mutex, NULL);
	pthread_mutex_init(&philos->done_mutex, NULL);
	i = 0;
	while (i < comp.n_philo)
	{
		pthread_create(&(philos->thread[i]), NULL, (void *)hello, philos);
		i++;
	}
	return (philos_catcher(philos, comp));
}

void	kill_or_not(t_philos *philos, t_comp comp, int i, int flg)
{
	if (flg == 1)
	{
		pthread_mutex_unlock(&philos->eaten_mutex);
		pthread_mutex_lock(&philos->done_mutex);
		*comp.done = -1;
		pthread_mutex_unlock(&philos->done_mutex);
		printlog(DIE, i);
	}
	else
		pthread_mutex_unlock(&philos->done_mutex);
	i = 0;
	while (i < comp.n_philo)
		pthread_join(philos->thread[i++], NULL);
	free(comp.forks);
	free(comp.done);
	free(comp.tv_has_eaten);
	free(philos->thread);
	return ;
}

void	*hello(t_philos *philos)
{
	t_comp			comp;
	int				stbl_name;
	int				stbl_cycles;
	static int		enm;
	struct timeval	tv_buf;

	pthread_mutex_lock(&philos->name_mutex);
	stbl_name = enm++;
	pthread_mutex_unlock(&philos->name_mutex);
	comp = philos->compend;
	gettimeofday(&tv_buf, NULL);
	pthread_mutex_lock(&philos->eaten_mutex);
	comp.tv_has_eaten[stbl_name] = tv_buf.tv_usec / 1000 + tv_buf.tv_sec * 1000;
	pthread_mutex_unlock(&philos->eaten_mutex);
	stbl_cycles = comp.n_cycles;
	return (cycler(stbl_cycles, philos, comp, stbl_name));
}

void	philos_catcher(t_philos *philos, t_comp comp)
{
	int				i;
	struct timeval	tv_act;
	unsigned long	act;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philos->done_mutex);
		if (*comp.done >= comp.n_philo)
			return (kill_or_not(philos, comp, i, 0));
		pthread_mutex_unlock(&philos->done_mutex);
		while (i < comp.n_philo)
		{
			gettimeofday(&tv_act, NULL);
			act = tv_act.tv_sec * 1000 + tv_act.tv_usec / 1000;
			pthread_mutex_lock(&philos->eaten_mutex);
			if (act - comp.tv_has_eaten[i] > (long unsigned)comp.t_death)
				return (kill_or_not(philos, comp, i, 1));
			pthread_mutex_unlock(&philos->eaten_mutex);
			i++;
		}
		usleep(1000);
		i = 0;
	}
}
