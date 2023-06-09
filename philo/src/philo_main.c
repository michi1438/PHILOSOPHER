/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:18:18 by mguerga           #+#    #+#             */
/*   Updated: 2023/07/14 13:05:56 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

int	main(int ac, char **av)
{
	t_philos	philos;
	int			init_val;

	init_val = init_args(ac, av, &philos.compend);
	if (init_val == -1)
	{
		printf ("err args: 4 or 5 args, must be positive ints...\n");
		return (-1);
	}
	else if (init_val == -2)
		return (-2);
	create_philos(&philos);
	return (0);
}
/*
 *
void	print_compend(t_comp *compend)
{
	printf("n_philo = %d$\n", compend->n_philo);
	printf("t_death = %d$\n", compend->t_death);
	printf("t_eat = %d$\n", compend->t_eat);
	printf("t_sleep = %d$\n", compend->t_sleep);
	printf("n_cycles = %d$\n", compend->n_cycles);
}
*/
