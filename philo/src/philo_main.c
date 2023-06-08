/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:18:18 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/08 17:51:38 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

int	main(int ac, char **av)
{
	t_comp		compend;
	t_philos	philos;

	if (init_args(ac, av, &compend) == -1)
	{
		printf ("err args: 4 or 5 args, must be positive ints...\n");
		return (-1);
	}
	print_compend(&compend);
	create_philos(&compend, &philos);
	return (0);
}

void	print_compend(t_comp *compend)
{
	printf("n_philo = %d$\n", compend->n_philo);
	printf("t_death = %d$\n", compend->t_death);
	printf("t_eat = %d$\n", compend->t_eat);
	printf("t_sleep = %d$\n", compend->t_sleep);
	printf("n_cycles = %d$\n", compend->n_cycles);
}

void	create_philos(t_comp *compend, t_philos *philos)
{
	int	i;

	i = 1;
	while (i <= compend->n_philo)
	{
		init_philos(philos, i);
		i++;
	}
}
