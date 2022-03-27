/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:04:36 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/28 03:34:03 by dim              ###   ########.fr       */
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

#define PATH_MAX 1024

typedef struct s_process
{
	pid_t	pid;
	char	*instruction;
	t_list	*option;
	t_list	*arg;
	// t_list	*redirect;
	// char	*heredoc_str;
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

void	make_error(void);
void	perror_and_exit(char *text, int errnum);

void	env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_lst_new(char **arr);
char	**ft_split_in_two(char *str, char ch);

int		exit_process(t_info *info, t_process *process, int exit_status);
int		str_is_num(char *str);
int		str_is_long(char *str);
int		parse_env(t_env **env, char **envp);
char	*get_env_value(t_env *env, char *key);
#endif