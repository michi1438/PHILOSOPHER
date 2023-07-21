/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_philo_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:12:17 by mguerga           #+#    #+#             */
/*   Updated: 2023/07/21 16:52:51 by mguerga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_PHILO_BONUS_H
# define HEAD_PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <stdatomic.h>

typedef struct s_comp{
	int						t_death;
	int						t_eat;
	int						t_sleep;
	int						n_philo;
	int						n_cycles;
	int						forks;
	_Atomic(unsigned long)	tv_has_eaten;
}	t_comp;

typedef struct s_philos{
	t_comp			compend;
	pid_t			*process;
	sem_t			*semaphore;
	sem_t			*semaphore_wwait;
	sem_t			*semaphore_wwait2;
	pthread_t		thread;
}	t_philos;

enum	e_status{
	EAT,
	DIE,
	FORK,
	SLEEP,
	THINK,
	CREATE,
};

//B_PHILO_MAIN.C
int				errors_nargs(int ac, char **av);

//B_PHILO_INIT.C
void			philo_init(int ac, char **av, t_philos *philos);
void			init_process(t_philos *philos);
void			init_semaphore(t_philos *philos);

//B_PHILO_UTILS.C
int				ft_strlen(char *str);
int				ft_atoi(char *nbr);
void			print_compend(t_philos *philos);
int				print_log(int name, int status);
void			set_time_last_eat(t_philos *philos, t_comp *comp);

//B_PHILO_INVOK.C
int				create_philos(t_philos *philos);
int				child_play(t_philos *philos);
void			*death_wwait(t_philos *philos);
void			*check_for_death(t_philos *philos);
unsigned long	actual_time(void);
int				is_eating(t_philos *philos, t_comp *comp);
int				sleep_timer(t_philos *philos, t_comp *comp);

#endif
