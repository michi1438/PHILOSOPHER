/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_philo.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:15:27 by mguerga           #+#    #+#             */
/*   Updated: 2023/07/17 12:05:07 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_PHILO_H
# define HEAD_PHILO_H

# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_comp
{
	int				n_cycles;
	int				n_philo;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				*done;
	char			*forks;
	unsigned long	*tv_has_eaten;	
	unsigned long	og_time_sec;
	unsigned long	og_time_usec;
}	t_comp;

typedef struct s_philos
{
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	name_mutex;
	pthread_mutex_t	eaten_mutex;
	pthread_mutex_t	done_mutex;
	t_comp			compend;
	pthread_t		*thread;
}	t_philos;

enum e_logs
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
	CREATE,
};

//FOR_TESTING.C
void	print_compend(t_comp *compend);

//PHILO_MAIN.C

//PHILO_UTILS.C
void	printlog(t_comp *comp, int log_type, int name);
int		has_2_forks(t_philos *philos, t_comp *comp, int stbl_name);

//PHILO_INIT.C
int		init_args(int ac, char **av, t_comp *compend);
int		is_unsigned_int(char **av, int ac);
void	init_forks_n_done(t_comp *compend);
void	init_tv_has_eaten(t_comp *comp);
void	init_og_time(t_comp *comp);

//PHILO_INVOK.C
void	create_philos(t_philos *philos);
void	kill_or_not(t_philos *philos, t_comp comp, int i, int flg);
void	*hello(t_philos *ptr);
void	philos_catcher(t_philos *philos, t_comp comp);

//PHILO_CYCLING.C
void	*cycler(int stbl_cycles, t_philos *philos, t_comp comp, int stbl_name);
int		is_eatin(t_philos *philos, t_comp *comp, int stbl_name, int *stbl_cycl);
int		tk_frks(t_philos *philos, t_comp *comp, int stbl_name, int *stbl_cycl);
int		catch_me(t_philos *philos, t_comp *comp);

//PHILO_TIMER.C
int		eat_timer(t_philos *philos, int stbl_name, t_comp *comp);
int		sleep_timer(t_philos *philos, t_comp *comp, int stbl_name);

//PHILO_atoi.c
int		ft_atoi(const char *num);
int		num_len(const char *num);

#endif
