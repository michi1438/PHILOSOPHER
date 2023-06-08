/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:10:55 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/08 16:13:29 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head_philo.h"

int	ft_atoi(const char *num)
{
	int	i;
	int	ret;
	int	mult;

	i = num_len(num);
	if (i == -1)
		return (-1);
	mult = 1;
	ret = 0;
	while (--i >= 0)
	{
		ret += (num[i] - 48) * mult;
		mult *= 10;
	}
	return (ret);
}

int	num_len(char const *num)
{
	int	i;

	i = 0;
	while (num[i] != '\0')
	{
		if (!(num[i] >= '0' && num[i] <= '9'))
			return (-1);
		i++;
	}
	return (i);
}
