# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/04 19:47:35 by mguerga           #+#    #+#              #
#    Updated: 2023/07/18 11:31:14 by mguerga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc 

CFLAGS = -lpthread -Werror -Wall -Wextra #-g3 -fsanitize=thread

SRC = philo_main.c philo_init.c philo_atoi.c philo_invok.c philo_utils.c philo_cycling.c \
		philo_timer.c

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
