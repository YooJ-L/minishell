# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 18:06:29 by yoojlee           #+#    #+#              #
#    Updated: 2022/03/12 21:24:47 by yoojlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -lreadline -L ./includes/libft -lft #-Wall -Wextra -Werror
CFLAGS += -g -fsanitize=address

SRCS = $(addprefix ./srcs/, \
		cd.c \
		pwd.c	\
		env_lst_new.c	\
		env_lstadd_back.c	\
		env.c	\
		parse_env.c \
		error.c \
		is_executable.c \
		ft_split_in_two.c \
		main.c \
		)

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

bonus : all

re : fclean all