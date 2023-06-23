/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_invok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:46:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/23 17:41:01 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

void	create_philos(t_philos *philos)
{
	int				i;
	t_comp			comp;
	int				is_not_dead;
	struct timeval	tv_act;

	comp = philos->compend;
	philos->thread = malloc(sizeof(int) * comp.n_philo + 1);
	pthread_mutex_init(&philos->name_mutex, NULL);
	pthread_mutex_init(&philos->fork_mutex, NULL);
	is_not_dead = 1;
	i = 0;
	while (i < comp.n_philo)
	{
		init_philos(philos, i);
		i++;
	}
	i = 0;
	while (is_not_dead == 1)
	{
		while (i < comp.n_philo)
		{
			gettimeofday(&tv_act, NULL);
			if ((tv_act.tv_usec - comp.tv_has_eaten[i]) / 1000 >= comp.t_death)
			{
				printlog(DIE, i);
				return ;
			}
			i++;
		}
		i = 0;
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
	struct timeval	tv_buf;

	pthread_mutex_lock(&philos->name_mutex);
	stbl_name = enm++;
	printlog(CREATE, stbl_name);
	pthread_mutex_unlock(&philos->name_mutex);
	comp = philos->compend;
	gettimeofday(&tv_buf, NULL);
	comp.tv_has_eaten[stbl_name] = tv_buf.tv_usec;
	stbl_cycles = comp.n_cycles;
	while (stbl_cycles != 0)
	{
		if (has_2_forks(philos, comp, stbl_name) == 1)
		{
			if (stbl_cycles != -1)
				stbl_cycles--;
			is_eating(philos, comp, stbl_name);
		}
	}
	pthread_detach(philos->thread[stbl_name]);
	return (NULL);
}

void	is_eating(t_philos *philos, t_comp comp, int stbl_name)
{
	int				f_num;
	struct timeval	tv_buf;

	if (stbl_name == 0)
		f_num = comp.n_philo - 1;
	else
		f_num = stbl_name - 1;
	pthread_mutex_lock(&philos->fork_mutex);
	comp.forks[stbl_name] = 0;
	comp.forks[f_num] = 0;
	pthread_mutex_unlock(&philos->fork_mutex);
	printlog(FORK, stbl_name);
	gettimeofday(&tv_buf, NULL);
	comp.tv_has_eaten[stbl_name] = tv_buf.tv_usec;
	eat_timer(comp);
	pthread_mutex_lock(&philos->fork_mutex);
	comp.forks[stbl_name] = 1;
	comp.forks[f_num] = 1;
	pthread_mutex_unlock(&philos->fork_mutex);
	sleep_timer(comp, stbl_name);
}

void	eat_timer(t_comp comp)
{
	struct timeval	tv_bef;
	struct timeval	tv_aft;
	long unsigned	bef;
	long unsigned	aft;

	gettimeofday(&tv_bef, NULL);
	bef = tv_bef.tv_sec * 1000 + tv_bef.tv_usec / 1000;
	gettimeofday(&tv_aft, NULL);
	aft = tv_aft.tv_sec * 1000 + tv_aft.tv_usec / 1000;
	while (aft - bef <= (long unsigned)comp.t_eat)
	{
		//printf("diff = %ld\n", tv_aft.tv_usec - tv_bef.tv_usec);
		gettimeofday(&tv_aft, NULL);
		aft = tv_aft.tv_sec * 1000 + tv_aft.tv_usec / 1000;
		usleep(1000);
	}
}

void	sleep_timer(t_comp comp, int stbl_name)
{
	struct timeval	tv_bef;
	struct timeval	tv_aft;
	long unsigned	bef;
	long unsigned	aft;

	printlog(SLEEP, stbl_name);
	gettimeofday(&tv_bef, NULL);
	bef = tv_bef.tv_sec * 1000 + tv_bef.tv_usec / 1000;
	gettimeofday(&tv_aft, NULL);
	aft = tv_aft.tv_sec * 1000 + tv_aft.tv_usec / 1000;
	while (aft - bef <= (long unsigned)comp.t_sleep)
	{
		//printf("diff = %ld\n", tv_aft.tv_usec - tv_bef.tv_usec);
		gettimeofday(&tv_aft, NULL);
		aft = tv_aft.tv_sec * 1000 + tv_aft.tv_usec / 1000;
		usleep(1000);
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
