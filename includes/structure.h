/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:04:36 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/04 23:52:27 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <stdio.h>
# include <stdbool.h> //bool
# include <dirent.h> //opendir
# include <readline/readline.h> //readline
# include <readline/history.h> //add_history
# include <sys/stat.h> //stat
# include <term.h> //tcgetattr
# include <errno.h> //errno
# include "libft/libft.h"

# define PATH_MAX 1024

# define SINGLE_IN 1
# define DOUBLE_IN 2
# define SINGLE_OUT 3
# define DOUBLE_OUT 4

typedef struct	s_redirection
{
	char					symbol;
	char					*filename;
	struct s_redirection	*next;
}				t_redirection;

typedef struct	s_process
{
	bool			heredoc;
	pid_t			pid;
	char			*instruction;
	t_list			*option;
	t_list			*arg;
	t_redirection	*redirect;
	char			*input_file; //초기화는 null로 해주기
	char			*heredoc_str;
}				t_process;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_info
{
	t_env		*env;
	t_process	*process;
	int			process_cnt;
}				t_info;

void	execute_echo(t_info *info, t_process *process);
int		execute_env(t_info *info, t_process *process);
int		execute_exit(t_info *info, t_process *process);
int		execute_unset(t_info *info, t_process *process);
int		execute_export(t_info *info, t_process *process);

void	make_error(void);
void	perror_and_exit(char *text, int errnum);
void	print_error_and_exit(char *output, int error_num);

void	env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_lst_new(char **arr);
char	**ft_split_in_two(char *str, char ch);

int		exit_process(t_info *info, t_process *process, int exit_status);
int		str_is_num(char *str);
int		str_is_long(char *str);
int		parse_env(t_env **env, char **envp);
char	*get_env_value(t_env *env, char *key);

void	sig_exit_handler(int sig) //자식이 죽었을 때
void	sigint_handler(void);
void	init_mom_setting(t_info *info);

void	add_character_to_str(char **str, char character)

int	run_heredoc(t_info *info, t_process *process)

//input.c
void	set_input_fd(t_process *process, int input_fd);

//output.c
void	set_output_fd(t_process *process, int pipe_fd[2], bool is_last);

//heredoc.c
int	run_heredoc(t_info *info, t_process *process);

//execute.c
void	execute(t_info *info, t_process *process);

//ft_builtin.c
bool	is_builtin_function(t_process *cur_process);
int		execute_single_builtin(t_info *info, t_process *process);

// built_in_functions
//cd.c

//echo.c
//env.c
//exit.c
int	execute_exit(t_info *info, t_process *process);
//export.c
int	execute_export(t_info *info, t_process *process);
//ft_builtin.c
int		execute_single_builtin(t_info *info, t_process *process);
bool	is_builtin_function(t_process *cur_process);
//pwd.c
int	execute_pwd(t_info *info, t_process *process);
//unset.c
int	execute_unset(t_info *info, t_process *process);

// error
//error.c

// in_path
//execute_etc.c
//get_arg.c
//get_env.c

// redirection
//heredoc.c
//input.c
//output.c

// temp
//execute.c
//is_executable.c
//sav





#endif