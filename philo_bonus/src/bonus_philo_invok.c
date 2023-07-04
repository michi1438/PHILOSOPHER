/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_philo_invok.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:05:20 by mguerga           #+#    #+#             */
/*   Updated: 2023/07/03 14:49:50 by mguerga          ###   ########.fr       */
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
	set_time_last_eat(comp);
	pthread_create(&philos->thread, NULL, (void *)check_for_death, philos);
	while (comp->n_cycles != 0)
	{
		sem_wait(philos->semaphore);
		sem_wait(philos->semaphore);
		//check_for_death(philos);
		is_eating(philos, comp);
		sleep_timer(philos, comp);
		usleep(1000);
	}
	return (1);
}

void	*check_for_death(t_philos *philos)
{
	unsigned long	act_time;
	t_comp			*comp;

	comp = &philos->compend;
	act_time = actual_time();
	while (1)
	{
		if (act_time - comp->tv_has_eaten >= (unsigned long)comp->t_death)
		{
			act_time = actual_time();
			print_log(philos->process[0], DIE);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

unsigned long	actual_time(void)
{
	struct timeval	tv;
	unsigned long	act_time;

	gettimeofday(&tv, NULL);
	act_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (act_time);
}

int	is_eating(t_philos *philos, t_comp *comp)
{
	unsigned long	act_time;

	print_log(philos->process[0], FORK);
	set_time_last_eat(comp); // detach the thread, and init new one...
	pthread_detach(philos->thread);
	pthread_create(&philos->thread, NULL, (void *)check_for_death, philos);
	act_time = actual_time();
	while (act_time - comp->tv_has_eaten < (unsigned long)comp->t_eat)
	{
		act_time = actual_time();
		usleep(1000);
	}
	return (0);
}

int	sleep_timer(t_philos *philos, t_comp *comp)
{
	unsigned long	act_time;
	unsigned long	t_slp_eat;

	print_log(philos->process[0], SLEEP);
	sem_post(philos->semaphore);
	sem_post(philos->semaphore);
	act_time = actual_time();
	t_slp_eat = (unsigned long)comp->t_sleep + (unsigned long)comp->t_eat;
	while (act_time - comp->tv_has_eaten < t_slp_eat)
	{
		act_time = actual_time();
		usleep(1000);
	}
	print_log(philos->process[0], THINK);
	return (0);
}
