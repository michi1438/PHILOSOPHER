/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_invok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:46:43 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/29 11:30:04 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

void	create_philos(t_philos *philos)
{
	int				i;
	unsigned long	act;
	t_comp			comp;
	struct timeval	tv_act;

	comp = philos->compend;
	philos->thread = malloc(sizeof(pthread_t) * comp.n_philo);
	pthread_mutex_init(&philos->fork_mutex, NULL);
	pthread_mutex_init(&philos->name_mutex, NULL);
	pthread_mutex_init(&philos->eaten_mutex, NULL);
	i = 0;
	while (i < comp.n_philo)
	{
		pthread_create(&(philos->thread[i]), NULL, (void *)hello, philos);
		i++;
	}
	i = 0;
	while (1)
	{
		if (*comp.done >= comp.n_philo)
		{
			i = 0;
			while (i < comp.n_philo)
				pthread_join(philos->thread[i++], NULL);
			return ;
		}
		while (i < comp.n_philo)
		{
			gettimeofday(&tv_act, NULL);
			act = tv_act.tv_sec * 1000 + tv_act.tv_usec / 1000;
			pthread_mutex_lock(&philos->eaten_mutex);
			if (act - comp.tv_has_eaten[i] > (long unsigned)comp.t_death)
			{
				pthread_mutex_unlock(&philos->eaten_mutex);
				*comp.done = -1;
				printlog(DIE, i);
				i = 0;
				while (i < comp.n_philo)
					pthread_join(philos->thread[i++], NULL);
				return ;
			}
			pthread_mutex_unlock(&philos->eaten_mutex);
			i++;
		}
		usleep(1000);
		i = 0;
	}
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
	pthread_mutex_lock(&philos->eaten_mutex);
	comp.tv_has_eaten[stbl_name] = tv_buf.tv_usec / 1000 + tv_buf.tv_sec * 1000;
	pthread_mutex_unlock(&philos->eaten_mutex);
	stbl_cycles = comp.n_cycles;
	while (stbl_cycles != 0)
	{
		if (catch_me(philos, &comp) == 1)
			return (NULL);
		if (has_2_forks(philos, &comp, stbl_name) == 1)
		{
			if (is_eating(philos, &comp, stbl_name, &stbl_cycles) == 1)
				return (NULL);
			if (sleep_timer(philos, &comp, stbl_name) == 1)
				return (NULL);
		}
	}
	return (NULL);
}

int	catch_me(t_philos *philos, t_comp *comp)
{
	(void)philos;
	if (*comp->done == -1)
	{
		return (1);
	}
	return (0);
}

int	is_eating(t_philos *philos, t_comp *comp, int stbl_name, int *stbl_cycles)
{
	int				f_num;
	struct timeval	tv_buf;

	pthread_mutex_lock(&philos->fork_mutex);
	if (stbl_name == 0)
		f_num = comp->n_philo - 1;
	else
		f_num = stbl_name - 1;
	printlog(FORK, stbl_name);
	comp->forks[stbl_name] = 0;
	comp->forks[f_num] = 0;
	pthread_mutex_unlock(&philos->fork_mutex);
	if (*stbl_cycles != -1)
		(*stbl_cycles)--;
	if (*stbl_cycles == 0)
		(*comp->done)++;
	gettimeofday(&tv_buf, NULL);
	pthread_mutex_lock(&philos->eaten_mutex);
	comp->tv_has_eaten[stbl_name] = tv_buf.tv_usec / 1000 + tv_buf.tv_sec * 1000;
	pthread_mutex_unlock(&philos->eaten_mutex);
	if (eat_timer(philos, stbl_name, comp) == 1)
		return (1);
	pthread_mutex_lock(&philos->fork_mutex);
	comp->forks[stbl_name] = 1;
	comp->forks[f_num] = 1;
	printlog(SLEEP, stbl_name);
	pthread_mutex_unlock(&philos->fork_mutex);
	return (0);
}

int	eat_timer(t_philos *philos, int stbl_name, t_comp *comp)
{
	struct timeval	tv_aft;
	long unsigned	aft;
	long unsigned	bef;

	gettimeofday(&tv_aft, NULL);
	//pthread_mutex_lock(&philos->eaten_mutex);
	bef = comp->tv_has_eaten[stbl_name];
	//pthread_mutex_unlock(&philos->eaten_mutex);
	aft = tv_aft.tv_sec * 1000 + tv_aft.tv_usec / 1000;
	while (aft - bef <= (long unsigned)comp->t_eat)
	{
		if (catch_me(philos, comp) == 1)
			return (1);
		gettimeofday(&tv_aft, NULL);
		aft = tv_aft.tv_sec * 1000 + tv_aft.tv_usec / 1000;
		usleep(1000);
	}
	return (0);
}

int	sleep_timer(t_philos *philos, t_comp *comp, int stbl_name)
{
	struct timeval	tv_aft;
	long unsigned	aft;
	long unsigned	bef;

	gettimeofday(&tv_aft, NULL);
	aft = tv_aft.tv_sec * 1000 + tv_aft.tv_usec / 1000;
	//pthread_mutex_lock(&philos->eaten_mutex);
	bef = comp->tv_has_eaten[stbl_name] + comp->t_eat;
	//pthread_mutex_unlock(&philos->eaten_mutex);
	while (aft - (bef) <= (long unsigned)comp->t_sleep)
	{
		if (catch_me(philos, comp) == 1)
			return (1);
		gettimeofday(&tv_aft, NULL);
		aft = tv_aft.tv_sec * 1000 + tv_aft.tv_usec / 1000;
		usleep(1000);
	}
	printlog(THINK, stbl_name);
	return (0);
}
