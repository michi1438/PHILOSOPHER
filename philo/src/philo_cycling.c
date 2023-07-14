/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:58:39 by mguerga           #+#    #+#             */
/*   Updated: 2023/07/14 13:12:54 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

void	*cycler(int stbl_cycles, t_philos *philos, t_comp comp, int stbl_name)
{
	while (stbl_cycles != 0)
	{
		if (catch_me(philos, &comp) == 1)
			return (NULL);
		if (has_2_forks(philos, &comp, stbl_name) == 1)
		{
			if (is_eatin(philos, &comp, stbl_name, &stbl_cycles) == 1)
				return (NULL);
			if (sleep_timer(philos, &comp, stbl_name) == 1)
				return (NULL);
			pthread_mutex_lock(&philos->done_mutex);
			if (*comp.done != -1)
				printlog(THINK, stbl_name);
			pthread_mutex_unlock(&philos->done_mutex);
		}
	}
	return (NULL);
}

int	is_eatin(t_philos *philos, t_comp *comp, int stbl_name, int *stbl_cycl)
{
	int				f_num;
	struct timeval	tv_buf;
	unsigned long	time_stmp;

	f_num = tk_frks(philos, comp, stbl_name, stbl_cycl);
	gettimeofday(&tv_buf, NULL);
	time_stmp = tv_buf.tv_usec / 1000 + tv_buf.tv_sec * 1000;
	pthread_mutex_lock(&philos->eaten_mutex);
	comp->tv_has_eaten[stbl_name] = time_stmp;
	pthread_mutex_unlock(&philos->eaten_mutex);
	if (eat_timer(philos, stbl_name, comp) == 1)
		return (1);
	pthread_mutex_lock(&philos->fork_mutex);
	comp->forks[stbl_name] = 1;
	comp->forks[f_num] = 1;
	pthread_mutex_lock(&philos->done_mutex);
	if (*comp->done != -1)
		printlog(SLEEP, stbl_name);
	pthread_mutex_unlock(&philos->done_mutex);
	pthread_mutex_unlock(&philos->fork_mutex);
	return (0);
}

int	tk_frks(t_philos *philos, t_comp *comp, int stbl_name, int *stbl_cycl)
{
	int				f_num;

	pthread_mutex_lock(&philos->fork_mutex);
	if (stbl_name == 0)
		f_num = comp->n_philo - 1;
	else
		f_num = stbl_name - 1;
	pthread_mutex_lock(&philos->done_mutex);
	if (*comp->done != -1)
		printlog(FORK, stbl_name);
	pthread_mutex_unlock(&philos->done_mutex);
	comp->forks[stbl_name] = 0;
	comp->forks[f_num] = 0;
	pthread_mutex_unlock(&philos->fork_mutex);
	pthread_mutex_lock(&philos->done_mutex);
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
