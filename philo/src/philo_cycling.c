/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:58:39 by mguerga           #+#    #+#             */
/*   Updated: 2023/07/18 11:41:35 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

void	*cycler(int stbl_cycles, t_philos *philos, t_comp comp, int stbl_name)
{
	while (stbl_cycles != 0)
	{
		if (catch_me(philos, &comp) == 1)
			return (NULL);
		if (is_eatin(philos, &comp, stbl_name, &stbl_cycles) == 1)
			return (NULL);
		if (sleep_timer(philos, &comp, stbl_name) == 1)
			return (NULL);
		pthread_mutex_lock(&philos->done_mutex);
		if (*comp.done != -1)
			printlog(&comp, THINK, stbl_name);
		pthread_mutex_unlock(&philos->done_mutex);
	}
	return (NULL);
}

int	is_eatin(t_philos *philos, t_comp *comp, int stbl_name, int *stbl_cycl)
{
	int				f_num;
	struct timeval	tv_buf;

	f_num = tk_frks(philos, comp, stbl_name, stbl_cycl);
	gettimeofday(&tv_buf, NULL);
	if (eat_timer(philos, stbl_name, comp) == 1)
	{
		pthread_mutex_unlock(&philos->fork_mutex[stbl_name]);
		pthread_mutex_unlock(&philos->fork_mutex[f_num]);
		return (1);
	}
	pthread_mutex_lock(&philos->done_mutex);
	if (*comp->done != -1)
		printlog(comp, SLEEP, stbl_name);
	pthread_mutex_unlock(&philos->done_mutex);
	comp->forks[f_num] = 1;
	comp->forks[stbl_name] = 1;
	pthread_mutex_unlock(&philos->fork_mutex[f_num]);
	pthread_mutex_unlock(&philos->fork_mutex[stbl_name]);
	return (0);
}

int	lock_order(t_comp *comp, t_philos *philos, int stbl_name)
{
	int				f_num;

	if (stbl_name == 0 && comp->n_philo % 2 != 1)
	{
		f_num = comp->n_philo - 1;
		pthread_mutex_lock(&philos->fork_mutex[stbl_name]);
		pthread_mutex_lock(&philos->fork_mutex[f_num]);
		comp->forks[stbl_name] = 0;
		comp->forks[f_num] = 0;
	}
	else
	{
		f_num = stbl_name - 1;
		if (stbl_name == 0)
			f_num = comp->n_philo - 1;
		pthread_mutex_lock(&philos->fork_mutex[f_num]);
		pthread_mutex_lock(&philos->fork_mutex[stbl_name]);
		comp->forks[f_num] = 0;
		comp->forks[stbl_name] = 0;
	}
	return (f_num);
}

int	tk_frks(t_philos *philos, t_comp *comp, int stbl_name, int *stbl_cycl)
{
	int				f_num;
	unsigned long	time_stmp;
	struct timeval	tv_buf;

	f_num = lock_order(comp, philos, stbl_name);
	pthread_mutex_lock(&philos->done_mutex);
	if (*comp->done != -1)
	{
		gettimeofday(&tv_buf, NULL);
		time_stmp = tv_buf.tv_usec / 1000 + tv_buf.tv_sec * 1000;
		pthread_mutex_lock(&philos->eaten_mutex);
		comp->tv_has_eaten[stbl_name] = time_stmp;
		printlog(comp, EAT, stbl_name);
		pthread_mutex_unlock(&philos->eaten_mutex);
	}
	if (*stbl_cycl > 0)
		(*stbl_cycl)--;
	if (*stbl_cycl == 0)
		(*comp->done)++;
	pthread_mutex_unlock(&philos->done_mutex);
	return (f_num);
}

int	catch_me(t_philos *philos, t_comp *comp)
{
	pthread_mutex_lock(&philos->done_mutex);
	if (*comp->done == -1)
	{
		pthread_mutex_unlock(&philos->done_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philos->done_mutex);
	return (0);
}
