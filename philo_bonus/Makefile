# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerga <mguerga@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 13:03:30 by mguerga           #+#    #+#              #
#    Updated: 2023/06/28 18:12:16 by mguerga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = gcc

CFLAGS = -Werror -Wall -Wextra #-fsanitize=address

SRC = bonus_philo_main.c bonus_philo_utils.c bonus_philo_init.c

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
