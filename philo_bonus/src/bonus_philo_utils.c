/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_philo_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:46:49 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/28 18:02:15 by mguerga          ###   ########.fr       */
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
