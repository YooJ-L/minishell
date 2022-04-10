/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_etc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:15:54 by dim               #+#    #+#             */
/*   Updated: 2022/04/10 15:49:12 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

char	*find_inst_in_path(char *path, char *instruction, \
		size_t begin, size_t end)
{
	char	*route;
	char	*ret;
	int		size;

	size = end - begin;
	route = (char *)malloc(sizeof(char) * (size + 2));
	if (route == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	ft_strlcpy(route, &path[begin], size + 1);
	route[size] = '/';
	route[size + 1] = '\0';
	ret = ft_strjoin(route, instruction);
	free(route);
	if (ret == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	return (ret);
}

void	execute_with_path(char *path, t_process *process, \
							char **arg, char **env)
{
	char		*instruction;
	size_t		begin;
	size_t		end;

	begin = 0;
	end = 0;
	while (begin < ft_strlen(path))
	{
		while (path[end] != ':' && path[end] != '\0')
			end++;
		instruction = find_inst_in_path(path, process->instruction, \
				begin, end);
		execve(instruction, arg, env);
		end++;
		begin = end;
	}
}

void	execute_etc_instruction(t_info *info, t_process *process)
{
	char	*instruction;
	char	*path;
	char	**arg;
	char	**env;

	instruction = process->instruction;
	arg = get_arg(process);
	env = get_env(info->env);
	if (process->instruction[0] == '.' || process->instruction[0] == '/')
		execve(instruction, arg, env);
	else if (get_env_value(info->env, "PATH"))
	{
		path = get_env_value(info->env, "PATH");
		execute_with_path(path, process, arg, env);
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(process->instruction, STDERR_FILENO);
		perror_and_exit(": command not found", 127);
	}
	else
		execve(instruction, arg, env);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(process->instruction, STDERR_FILENO);
	perror_and_exit(": No such file or directory", 127);
}
