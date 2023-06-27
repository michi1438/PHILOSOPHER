/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_philo_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 13:12:17 by mguerga           #+#    #+#             */
/*   Updated: 2023/06/27 16:59:53 by mguerga          ###   ########.fr       */
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

struct s_philos{
	t_compend		compend;
	pthread_t		*thread;
} t_philos;

struct s_comp{
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				n_philo;
	int				n_cycles;
	char			*forks;
	unsigned int	*tv_has_eaten;
}	t_comp
//B_PHILO_MAIN.C
int		errors_nargs(int ac, char **av);

//B_PHILO_INIT.C
void	philo_init(char **av);

#endif
