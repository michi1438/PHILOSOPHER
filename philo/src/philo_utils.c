/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:06:30 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/13 11:46:40 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

void	printlog(int log_type, int name)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (log_type == FORK)
		printf("%02ld.%03ld %d has taken a fork\n", tv.tv_sec % 100, tv.tv_usec / 1000, name + 1);
	else if (log_type == EAT)
		printf("%02ld.%03ld %d is eating\n", tv.tv_sec % 100, tv.tv_usec / 1000, name + 1);
	else if (log_type == SLEEP)
		printf("%02ld.%03ld %d is sleeping\n", tv.tv_sec % 100, tv.tv_usec / 1000, name + 1);
	else if (log_type == THINK)
		printf("%02ld.%03ld %d is thinking\n", tv.tv_sec % 100, tv.tv_usec / 1000, name + 1);
	else if (log_type == DIE)
		printf("%02ld.%03ld %d died\n", tv.tv_sec % 100, tv.tv_usec / 1000, name + 1);
}

int	has_2_forks(t_comp comp, int stbl_name)
{
	int	f_num;

	if (stbl_name == 0)
		f_num = comp.n_philo - 1;
	else
		f_num = stbl_name - 1;
	if (comp.forks[stbl_name] && comp.forks[f_num])
		return (1);
	return (0);
}
