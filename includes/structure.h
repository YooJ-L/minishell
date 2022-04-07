/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:04:36 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/07 15:36:10 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <stdio.h>
# include <stdbool.h> //bool
# include <dirent.h> //opendir
# include <fcntl.h> //open
# include <readline/readline.h> //readline
# include <readline/history.h> //add_history
# include <sys/stat.h> //stat
# include <term.h> //tcgetattr
# include <errno.h> //errno
# include "libft/libft.h"
# include "libft/get_next_line.h"

# define PATH_MAX 1024

# define SINGLE_IN 1
# define DOUBLE_IN 2
# define SINGLE_OUT 3
# define DOUBLE_OUT 4

typedef struct	s_redirection
{
	int						symbol;
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
	unsigned char	last_exit_status;
	t_env			*env;
	int				process_cnt;
	struct termios	org_term; //ecoctl 끄고 킬 때 사용하는 것
	struct termios	new_term;

}				t_info;

int				execute_echo(t_info *info, t_process *process);
int				execute_env(t_info *info, t_process *process);
int				execute_exit(t_info *info, t_process *process);
int				execute_unset(t_info *info, t_process *process);
int				execute_export(t_info *info, t_process *process);
int				execute_pwd(t_info *info, t_process *process);
int				execute_cd(t_info *info, t_process *process);
void			execute_etc_instruction(t_info *info, t_process *process);
void			print_export(t_env *env);


void			perror_and_exit(char *text, int errnum);
int				error_option(char	*inst, t_info *info, t_process *process);

void			env_lstadd_back(t_env **lst, t_env *new);
t_env			*env_lst_new(char **arr);
t_env			*env_node_exists(t_env *env, char *new_key);
void			modify_env_node(t_env *env, char *new_key, char *new_value);
void			ft_env_lstclear(t_env **lst);
void			ft_redir_lstclear(t_redirection **lst);
// t_redirection 	*redir_lst_new(char **arr);
t_redirection	*redir_lstlast(t_redirection *lst);
void			redir_lstadd_back(t_redirection **lst, t_redirection *new);

char			**ft_split_in_two(char *str, char ch);

int				exit_process(t_info *info, t_process *process, int exit_status);
int				str_is_num(char *str);
int				str_is_long(char *str);
int				parse_env(t_env **env, char **envp);
char			*get_env_value(t_env *env, char *key);
void			add_char_to_str(char **str, char character);

//inpath
char			**get_arg(t_process *process);
char			**get_env(t_env *env);

//input.c
void			set_input_fd(t_process *process, int input_fd);

//output.c
void			set_output_fd(t_process *process, int pipe_fd[2], bool is_last);
void			redirect_output_fd(t_process *process);

//heredoc.c
int				run_heredoc(t_info *info, t_process *process);

//fork.c
void			execute(t_info *info, t_process *process);

//ft_builtin.c
bool			is_builtin_ft(t_process *cur_process);

//execute.c
int				execute_single_builtin(t_info *info, t_process *process);
int				execve_command(t_info *info, t_process *cur_process);

//signal.c
void			sig_exit_handler(int sig); //자식이 죽었을 때
void			sigint_handler(void);
void			set_parent_process(t_info *info);

//terminal.c
void			change_input_mode(void);
// void 			reset_input_mode(void);
// void 			set_input_mode(void);
void	set_input_mode(struct termios *new_term);
void	reset_input_mode(struct termios *org_term);

//validate.c
int				validate_input(t_info *info, char *input);

//free.c
void			free_all(t_info *info, t_process *process, char *input);
void			free_redirection(t_redirection **redirect);
void			free_process(t_process *process);
void			free_envp(t_info *info);

#endif