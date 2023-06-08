/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_philo.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:15:27 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/08 17:51:12 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_PHILO_H
# define HEAD_PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_comp
{
	int		n_cycles;
	int		n_philo;
	int		t_death;
	int		t_eat;
	int		t_sleep;
}	t_comp;

typedef struct s_philos
{
	int									name;
	pthread_t	*restrict				thread;
	const pthread_attr_t	*restrict	attr;
}	t_philos;

//FOR_TESTING.C
void	print_compend(t_comp *compend);

//PHILO_MAIN.C
void	create_philos(t_comp *compend, t_philos *philos);

//PHILO_INIT.C
int		init_args(int ac, char **av, t_comp *compend);
int		is_unsigned_int(char **av, int ac);
int		init_philos(t_philos *philos, int i);
void	*hello(void *ptr);

//PHILO_atoi.c
int		ft_atoi(const char *num);
int		num_len(const char *num);

#endif
