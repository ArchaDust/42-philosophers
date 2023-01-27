# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aberneli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/16 14:59:12 by aberneli          #+#    #+#              #
#    Updated: 2022/01/06 15:08:51 by aberneli         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := gcc
FLAGS := -Wall -Wextra -Werror -I. -O3

HEADER := philo.h

SRC := main.c philo.c utils.c mlib.c table.c
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

rebonus: fclean

.PHONY: all clean fclean re
