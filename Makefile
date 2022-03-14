# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 18:06:29 by yoojlee           #+#    #+#              #
#    Updated: 2022/03/14 19:07:15 by yoojlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -lreadline -L ./includes/libft -lft #-Wall -Wextra -Werror
CFLAGS += -g -fsanitize=address

BUILT_IN_FUNCS = $(addprefix built_in_functions/, \
					cd.c \
					env.c \
					export.c \
					pwd.c \
					unset.c \
					)

PARSE = $(addprefix parse/, \
			parse_env.c \
			)

ERROR = $(addprefix error/, \
			error.c \
			)

TEMP = $(addprefix temp/, \
		execute.c \
		is_executable.c \
		save_process.c \
		terminal.c \
		)

UTILS = $(addprefix utils/, \
		env_lst_new.c \
		env_lstadd_back.c \
		ft_split_in_two.c \
		)

SRCS = $(addprefix ./srcs/, \
		main.c \
		$(BUILT_IN_FUNCS) \
		$(PARSE) \
		$(ERROR) \
		$(TEMP) \
		$(UTILS) \
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