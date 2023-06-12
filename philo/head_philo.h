/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_philo.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:15:27 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/10 09:45:32 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_PHILO_H
# define HEAD_PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_comp
{
	int		n_cycles;
	int		n_philo;
	int		n_forks;
	int		t_death;
	int		t_eat;
	int		t_sleep;
}	t_comp;

typedef struct s_philos
{
	int			name;
	t_comp		compend;
	pthread_t	*thread;
}	t_philos;

//FOR_TESTING.C
void	print_compend(t_comp *compend);

//PHILO_MAIN.C

//PHILO_INIT.C
int		init_args(int ac, char **av, t_comp *compend);
int		is_unsigned_int(char **av, int ac);

//PHILO_INVOK.C
void	create_philos(t_philos *philos);
void	init_philos(t_philos *philos, int i);
void	*hello(t_philos *ptr);

//PHILO_atoi.c
int		ft_atoi(const char *num);
int		num_len(const char *num);

#endif
