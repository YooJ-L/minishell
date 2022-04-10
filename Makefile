# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 18:06:29 by yoojlee           #+#    #+#              #
#    Updated: 2022/04/10 12:26:04 by yoojlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      = minishell

CC         = gcc
CFLAGS      = $(INCFLAGS) #$(GFLAGS) #$(WFLAGS) 
WFLAGS      = -Wall -Wextra -Werror
GFLAGS      = -g -fsanitize=address
INCFLAGS   = -I$(INCDIR)

INCDIR      = includes
LIBDIR      = includes/libft
SRCDIR      = srcs
OBJDIR      = build
SUBDIR      = built_in_functions \
            error \
            execute \
            in_path \
            parse \
            redirection \
            utils \

RL_LIB_DIR   = /opt/homebrew/opt/readline/lib
RL_INC_DIR   = /opt/homebrew/opt/readline/include

vpath %.c   = $(SRCDIR)\
           $(addprefix $(SRCDIR)/, $(SUBDIR))

SRCS      = main.c\
           \
           cd.c \
           env.c \
           export.c \
           print_export.c \
           pwd.c \
           unset.c \
           echo.c \
           exit.c \
           \
           check_token.c \
           parse_env.c \
           parse_process.c \
           parse_util.c \
           replace_env.c \
           save_token.c \
           split_line.c \
           validate.c \
           \
           error.c \
           \
           fork.c\
           execute.c\
           \
           execute_etc.c \
           get_arg.c \
           get_env.c \
           \
           check_redirect.c \
           heredoc.c \
           input.c \
           output.c \
           \
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


OBJS      = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBNAME      = ft
LIB         = $(LIBDIR)/libft.a

all         : $(NAME)

$(NAME)      : $(LIB) $(OBJS)
		$(CC) -o $@ $(OBJS) $(CFLAGS) -L$(LIBDIR) -L$(RL_LIB_DIR) -l$(LIBNAME) -lreadline

$(LIB)      :
	make -C $(LIBDIR) bonus

$(OBJDIR)/%.o   : %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $^ -I$(RL_INC_DIR)

$(OBJDIR)   :
	mkdir build

clean      :
	$(RM) -r $(OBJDIR)
	make -C $(LIBDIR) clean

fclean      : clean
	$(RM) $(NAME) $(OBJDIR)
	make -C $(LIBDIR) fclean

re         : fclean all

.PHONY      : all clean fclean re 
