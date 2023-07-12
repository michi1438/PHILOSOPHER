/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_philo_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:46:49 by mguerga           #+#    #+#             */
/*   Updated: 2023/07/12 16:04:04 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo_bonus.h"

int	ft_atoi(char *nbr)
{
	int	i;
	int	ret;
	int	mult;

	mult = 1;
	ret = 0;
	i = ft_strlen(nbr) - 1;
	while (i >= 0)
	{
		ret += (nbr[i] - 48) * mult;
		mult *= 10;
		i--;
	}
	return (ret);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	print_compend(t_philos *philos)
{
	t_comp	comp;

	comp = philos->compend;
	printf("n_philo = %d$\n", comp.n_philo);
	printf("t_death = %d$\n", comp.t_death);
	printf("t_eat = %d$\n", comp.t_eat);
	printf("t_sleep= %d$\n", comp.t_sleep);
	printf("n_cycles = %d$\n", comp.n_cycles);
}

int	print_log(int name, int status)
{
	struct timeval	tv;
	unsigned int	sec;
	unsigned int	msec;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec % 100;
	msec = tv.tv_usec / 1000;
	if (status == DIE)
		(printf("%02d.%03d %02d died\n", sec, msec, name + 1));
	if (status == FORK)
	{
		(printf("%02d.%03d %02d has taken a fork\n", sec, msec, name + 1));
		(printf("%02d.%03d %02d has taken a fork\n", sec, msec, name + 1));
		(printf("%02d.%03d %02d is eating\n", sec, msec, name + 1));
	}
	if (status == SLEEP)
		(printf("%02d.%03d %02d is sleeping\n", sec, msec, name + 1));
	if (status == THINK)
		(printf("%02d.%03d %02d is thinking\n", sec, msec, name + 1));
	if (status == CREATE)
		(printf("%02d.%03d %02d CREATED\n", sec, msec, name + 1));
	return (0);
}

void	set_time_last_eat(t_comp *comp)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	comp->tv_has_eaten = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
