/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_invok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:46:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/21 12:18:04 by mguerga          ###   ########.fr       */
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
}

void	*hello(t_philos *philos)
{
	t_comp			comp;
	int				stbl_name;
	int				stbl_cycles;
	static int		enm;
	struct timeval	tv_bef;
	int				i;
	int				t;

	t = 1000;
	pthread_mutex_lock(&philos->name_mutex);
	printlog(CREATE, enm);
	stbl_name = enm++;
	pthread_mutex_unlock(&philos->name_mutex);
	comp = philos->compend;
	stbl_cycles = comp.n_cycles;
	i = 0;
	while (i <= (comp.t_death) + 1 && stbl_cycles != 0)
	{
		if (has_2_forks(philos, comp, stbl_name) == 1)
		{
			stbl_cycles--;
			is_eating(philos, comp, stbl_name);
			sleep_timer(philos, comp, stbl_name);
			i = (comp.t_eat + comp.t_sleep);
		}
		gettimeofday(&tv_bef, NULL);
		i++;
		usleep_wrapper(tv_bef, &t);
	}
	if (stbl_cycles != 0)
		printlog(DIE, stbl_name);
	pthread_detach(philos->thread[stbl_name]);
	return (NULL);
}

void	is_eating(t_philos *philos, t_comp comp, int stbl_name)
{
	int				f_num;
	pthread_mutex_t	forks_mutex;

	pthread_mutex_init(&forks_mutex, NULL);
	if (stbl_name == 0)
		f_num = comp.n_philo - 1;
	else
		f_num = stbl_name - 1;
	pthread_mutex_lock(&forks_mutex);
	comp.forks[stbl_name] = 0;
	comp.forks[f_num] = 0;
	pthread_mutex_unlock(&forks_mutex);
	printlog(FORK, stbl_name);
	eat_timer(philos, comp, stbl_name);
	pthread_mutex_lock(&forks_mutex);
	comp.forks[stbl_name] = 1;
	comp.forks[f_num] = 1;
	pthread_mutex_unlock(&forks_mutex);
	printlog(SLEEP, stbl_name);
}

void	eat_timer(t_philos *philos, t_comp comp, int stbl_name)
{
	int				i;
	int				t;
	struct timeval	tv_bef;

	i = 0;
	t = 1000;
	while (i < comp.t_eat)
	{
		gettimeofday(&tv_bef, NULL);
		if (i > comp.t_death)
		{
			printlog(DIE, stbl_name);
			pthread_detach(philos->thread[i]);
		}
		usleep_wrapper(tv_bef, &t);
		i++;
	}
}

void	sleep_timer(t_philos *philos, t_comp comp, int stbl_name)
{
	int				i;
	int				t;
	struct timeval	tv_bef;

	t = 1000;
	i = comp.t_eat;
	while (i < (comp.t_sleep + comp.t_eat))
	{
		gettimeofday(&tv_bef, NULL);
		if (i > comp.t_death)
		{
			printlog(DIE, stbl_name);
			pthread_detach(philos->thread[i]);
		}
		usleep_wrapper(tv_bef, &t);
		i++;
	}
	printlog(THINK, stbl_name);
}

void	usleep_wrapper(struct timeval tv_bef, int *t)
{
	struct timeval	tv_aft;

	if (*t > 1000)
		*t = 1000;
	if (*t < 1)
		*t = 1;
	usleep(*t);
	gettimeofday(&tv_aft, NULL);
	if (tv_bef.tv_usec <= tv_aft.tv_usec)
		*t = 1000 - (tv_aft.tv_usec - tv_bef.tv_usec - *t);
}
