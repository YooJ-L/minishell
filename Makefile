# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dim <dim@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 18:06:29 by yoojlee           #+#    #+#              #
#    Updated: 2022/03/22 19:12:38 by dim              ###   ########.fr        #
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
					echo.c \
					exit.c \
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
		check_num.c \
		exit_process.c \
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
	make libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)

all : $(NAME)

libft :
		make bonus -C includes/libft

clean :
	rm -rf $(OBJS)
	make -C includes/libft clean

fclean : clean
	rm -rf $(NAME)
	make -C includes/libft fclean

bonus : all

re : fclean all