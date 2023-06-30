/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_timer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:01:14 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/30 12:01:55 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

int	eat_timer(t_philos *philos, int stbl_name, t_comp *comp)
{
	struct timeval	tv_aft;
	long unsigned	aft;
	long unsigned	bef;

	gettimeofday(&tv_aft, NULL);
	bef = comp->tv_has_eaten[stbl_name];
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
	bef = comp->tv_has_eaten[stbl_name] + comp->t_eat;
	while (aft - (bef) <= (long unsigned)comp->t_sleep)
	{
		if (catch_me(philos, comp) == 1)
			return (1);
		gettimeofday(&tv_aft, NULL);
		aft = tv_aft.tv_sec * 1000 + tv_aft.tv_usec / 1000;
		usleep(1000);
	}
	return (0);
}
