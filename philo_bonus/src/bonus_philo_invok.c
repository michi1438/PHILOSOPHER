/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_philo_invok.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:05:20 by mguerga           #+#    #+#             */
/*   Updated: 2023/07/01 10:27:19 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo_bonus.h"

int	create_philos(t_philos *philos)
{
	int		i;
	t_comp	*comp;

	i = 0;
	comp = &philos->compend;
	while (i < comp->n_philo)
	{
		philos->process[i] = fork();
		if (philos->process[i] == 0)
		{
			philos->process[0] = i;
			return (child_play(philos));
		}
		else
			i++;
	}
	while (1)
		usleep (1000);
	//catching_func();
	return (0);
}

int	child_play(t_philos *philos)
{
	t_comp			*comp;

	comp = &philos->compend;
	print_log(philos->process[0], CREATE);
//	printf("passed\n");
	set_time_last_eat(comp);
	while (comp->n_cycles != 0)
	{
		check_for_death(philos);
		//if (has_2_forks(semaphore) == 1) ;
		is_eating(philos, comp);
		sleep_timer(philos, comp);
	}
	print_log(philos->process[0], DIE);
	return (1);
}

int	check_for_death(t_philos *philos)
{
	struct timeval	tv;
	unsigned long	act_time;
	t_comp			*comp;

	comp = &philos->compend;
	gettimeofday(&tv, NULL);	
	act_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (act_time - comp->tv_has_eaten >= (unsigned long)comp->t_death)
	{
		print_log(philos->process[0], DIE);
		exit (10);
	}
	return (0);
}

int	is_eating(t_philos *philos, t_comp *comp)
{
	int	i;

	i = 0;
	//take out 2 forks.
	print_log(philos->process[0], FORK);
	set_time_last_eat(comp);
	while (i < comp->t_eat)
	{
		check_for_death(philos);
		usleep(1000);//wrapper
		i++;
	}
	return (0);
	//give back the 2 forks;
}

int	sleep_timer(t_philos *philos, t_comp *comp)
{
	int	i;

	i = 0;
	print_log(philos->process[0], SLEEP);
	while (i < comp->t_sleep)
	{
		check_for_death(philos);
		usleep(1000);//wrapper
		i++;
	}
	print_log(philos->process[0], THINK);
	return (0);
}
