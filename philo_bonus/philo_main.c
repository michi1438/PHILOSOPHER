/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:16:31 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/27 16:32:52 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "

int	main(int ac, char **av)
{
	if (parse_nargs(ac))
		return (1);
	return (0);
}

int parse_nargs(int ac)
{
	if (ac == 1)
		printf("passed\n");
	return (0);
}
