/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_philo.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:15:27 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/13 12:04:51 by mguerga          ###   ########.fr       */
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
	int		t_death;
	int		t_eat;
	int		t_sleep;
	int		*forks;
}	t_comp;

typedef struct s_philos
{
	int			name;
	t_comp		compend;
	pthread_t	*thread;
}	t_philos;

enum e_logs
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
};

//FOR_TESTING.C
void	print_compend(t_comp *compend);

//PHILO_MAIN.C

//PHILO_UTILS.C
void	printlog(int log_type, int name);
int		has_2_forks(t_comp comp, int stbl_name);

//PHILO_INIT.C
int		init_args(int ac, char **av, t_comp *compend);
int		is_unsigned_int(char **av, int ac);
void	init_forks(t_comp *compend);

//PHILO_INVOK.C
void	create_philos(t_philos *philos);
void	init_philos(t_philos *philos, int i);
void	*hello(t_philos *ptr);
void	is_eating(t_comp comp, int stbl_name);

//PHILO_atoi.c
int		ft_atoi(const char *num);
int		num_len(const char *num);

#endif
