# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 18:06:29 by yoojlee           #+#    #+#              #
#    Updated: 2022/04/06 22:47:09 by yoojlee          ###   ########.fr        #
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
					ft_builtin.c \
					)

PARSE = $(addprefix parse/, \
			check_token.c \
			parse_env.c \
			parse_process.c \
			parse_util.c \
			replace_env.c \
			save_token.c \
			split_line.c \
			validate.c \
			)

ERROR = $(addprefix error/, \
			error.c \
			)

EXECUTE = $(addprefix execute/, \
			execute.c \
			fork.c \
			)

IN_PATH = $(addprefix in_path/, \
			execute_etc.c \
			get_arg.c \
			get_env.c \
			)

REDIRECTION = $(addprefix redirection/, \
				heredoc.c \
				input.c \
				output.c \
				)

UTILS = $(addprefix utils/, \
			add_char.c \
			check_num.c \
			exit_process.c \
			ft_split_in_two.c \
			get_env_value.c \
			is_executable.c \
			lst_func.c \
			lst_env_func.c \
			free.c \
			signal.c \
			terminal.c \
		)

SRCS = $(addprefix ./srcs/, \
		main.c \
		$(BUILT_IN_FUNCS) \
		$(PARSE) \
		$(ERROR) \
		$(EXECUTE) \
		$(IN_PATH) \
		$(REDIRECTION) \
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