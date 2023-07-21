/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_philo_timers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:06:52 by mguerga           #+#    #+#             */
/*   Updated: 2023/07/21 17:21:26 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo_bonus.h"

int	is_eating(t_philos *philos, t_comp *comp)
{
	unsigned long	act_time;

	set_time_last_eat(philos, comp);
	print_log(philos->process[0], EAT);
	act_time = actual_time();
	comp->n_cycles--;
	while (act_time - comp->tv_has_eaten < (unsigned long)comp->t_eat)
	{
		check_for_death(philos);
		act_time = actual_time();
		usleep(1000);
	}
	print_log(philos->process[0], SLEEP);
	return (0);
}

int	sleep_timer(t_philos *philos, t_comp *comp)
{
	unsigned long	act_time;
	unsigned long	t_slp_eat;

	sem_post(philos->semaphore);
	sem_post(philos->semaphore);
	act_time = actual_time();
	t_slp_eat = (unsigned long)comp->t_sleep + (unsigned long)comp->t_eat;
	while (act_time - comp->tv_has_eaten < t_slp_eat)
	{
		check_for_death(philos);
		act_time = actual_time();
		usleep(1000);
	}
	print_log(philos->process[0], THINK);
	return (0);
}
