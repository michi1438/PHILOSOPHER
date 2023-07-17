/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:06:30 by mguerga           #+#    #+#             */
/*   Updated: 2023/07/17 14:45:42 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

void	printlog(t_comp *comp, int log_type, int name)
{
	struct timeval	tv;
	long			sec;
	unsigned long	msec;

	gettimeofday(&tv, NULL);
	msec = ((tv.tv_usec / 1000 + tv.tv_sec * 1000) - comp->og_time_usec);
	sec = (msec / 1000) % 100;
	msec = msec % 1000;
	if (log_type == FORK)
	{
		printf("%02ld.%03ld %d has taken a fork\n", sec, msec, name + 1);
		printf("%02ld.%03ld %d has taken a fork\n", sec, msec, name + 1);
		printf("%02ld.%03ld %d is eating\n", sec, msec, name + 1);
	}
	else if (log_type == SLEEP)
		printf("%02ld.%03ld %d is sleeping\n", sec, msec, name + 1);
	else if (log_type == THINK)
		printf("%02ld.%03ld %d is thinking\n", sec, msec, name + 1);
	else if (log_type == DIE)
		printf("%02ld.%03ld %d died\n", sec, msec, name + 1);
	else if (log_type == CREATE)
		printf("%02ld.%03ld %d CREATED\n", sec, msec, name + 1);
}
/*
int	has_2_forks(t_philos *philos, t_comp *comp, int stbl_name)
{
	int				f_num;

	pthread_mutex_lock(&philos->name_mutex);
	if (stbl_name == 0)
		f_num = comp->n_philo - 1;
	else
		f_num = stbl_name - 1;
	pthread_mutex_unlock(&philos->name_mutex);
	printf("philo n %d has his fork%d=%d and -1 %d=%d\n", stbl_name + 1, stbl_name + 1, comp->forks[stbl_name], f_num + 1, comp->forks[f_num]);
	pthread_mutex_lock(&philos->fork_mutex);
	if (comp->n_philo > 1 && comp->forks[stbl_name] && comp->forks[f_num])
	{
		return (1);
	}
	pthread_mutex_unlock(&philos->fork_mutex);
	return (0);
}
*/
