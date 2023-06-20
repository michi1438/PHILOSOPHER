/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_invok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:46:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/20 10:59:34 by mguerga          ###   ########.fr       */
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
	int				i;
	int				t;

	t = 7000;
	pthread_mutex_lock(&philos->name_mutex);
	printlog(CREATE, enm);
	stbl_name = enm++;
	pthread_mutex_unlock(&philos->name_mutex);
	comp = philos->compend;
	stbl_cycles = comp.n_cycles;
	i = 0;
	while (i <= (comp.t_death) / 7 && stbl_cycles != 0)
	{
		if (has_2_forks(philos, comp, stbl_name) == 1)
		{
			stbl_cycles--;
			is_eating(philos, comp, stbl_name);
			printlog(SLEEP, stbl_name);
			sleep_timer(philos, comp, stbl_name);
			printlog(THINK, stbl_name);
			i = (comp.t_eat / 7 + comp.t_sleep / 7);
		}
		i++;
		usleep_wrapper(&t); // TODO try and replace with normal usleep(1000);
	}
	if (stbl_cycles != 0)
		printlog(DIE, stbl_name);
	pthread_detach(philos->thread[stbl_name]);
	return (NULL);
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
	printlog(FORK, stbl_name);
	pthread_mutex_unlock(&philos->name_mutex);
	printlog(EAT, stbl_name);
	eat_timer(philos, comp, stbl_name);
	pthread_mutex_lock(&philos->name_mutex);
	comp.forks[stbl_name] = 1;
	comp.forks[f_num] = 1;
	pthread_mutex_unlock(&philos->name_mutex);
}

void	eat_timer(t_philos *philos, t_comp comp, int stbl_name)
{
	int	i;
	int	t;

	i = 0;
	t = 7000;
	while (i < comp.t_eat / 7)
	{
		if (i >= comp.t_death / 7)
		{
			printlog(DIE, stbl_name);
			pthread_detach(philos->thread[i]);
		}
		usleep_wrapper(&t);
		i++;
	}
}

void	sleep_timer(t_philos *philos, t_comp comp, int stbl_name)
{
	int	i;
	int	t;

	t = 7000;
	i = comp.t_eat / 7;
	while (i < (comp.t_sleep / 7+ comp.t_eat / 7))
	{
		if (i >= comp.t_death / 7)
		{
			printlog(DIE, stbl_name);
			pthread_detach(philos->thread[i]);
		}
		usleep_wrapper(&t);
		i++;
	}
}

void	usleep_wrapper(int *t)
{
	struct timeval	tv_bef;
	struct timeval	tv_aft;
	pthread_mutex_t	wrap_mut;

	pthread_mutex_init(&wrap_mut, NULL);
	pthread_mutex_lock(&wrap_mut);
	if (*t <= 0 || *t > 7000)
		*t = 7000;
	pthread_mutex_unlock(&wrap_mut);
	gettimeofday(&tv_bef, NULL);
	pthread_mutex_lock(&wrap_mut);
	usleep(*t);
	pthread_mutex_unlock(&wrap_mut);
	gettimeofday(&tv_aft, NULL);
	pthread_mutex_lock(&wrap_mut);
	if (tv_bef.tv_usec <= tv_aft.tv_usec)
		*t = 7000 - (tv_aft.tv_usec - tv_bef.tv_usec - 7000);
	pthread_mutex_unlock(&wrap_mut);
}
