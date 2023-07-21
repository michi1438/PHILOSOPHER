# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 13:03:30 by mguerga           #+#    #+#              #
#    Updated: 2023/07/20 13:03:25 by mguerga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = gcc

CFLAGS = -lpthread -Werror -Wall -Wextra #-g3 -fsanitize=thread

SRC = bonus_philo_main.c bonus_philo_utils.c bonus_philo_init.c bonus_philo_invok.c \
		bonus_philo_timers.c

AR = ar rcs

SOURCES = $(addprefix src/, $(SRC))

OBJS = $(SOURCES:c=o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re bonus
