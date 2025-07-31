# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/10 15:32:20 by hyakici           #+#    #+#              #
#    Updated: 2025/07/31 14:24:50 by hyakici          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = pipex.a

SRCS = ft_split.c ft_strjoin.c ft_substr.c pipex.c utils.c command_pars.c ft_strdup.c control_parms.c

OBJS = $(SRCS:.c=.o)
		
all : $(NAME)



$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean :
	rm -f $(OBJS)

run : $(NAME)
	cc pipex.c pipex.a -o pipex

fclean: clean
	rm -f $(NAME) pipex

re: fclean all

.PHONY: all clean re fclean run
