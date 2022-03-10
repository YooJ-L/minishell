/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:04:36 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/09 17:51:11 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef
# define STRUCTURE_H

# include <stdio.h>
# include <dirent.h> //opendir
# include <readline/readline.h> //readline
# include <readline/history.h> //add_history
# include <sys/stat.h> //stat
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
