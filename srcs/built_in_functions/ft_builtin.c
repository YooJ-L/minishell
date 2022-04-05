/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:04:21 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/04 19:19:28 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

bool	is_builtin_function(t_process *cur_process)
{
	if ((!cur_process->instruction) || \
		(!ft_strncmp("cd", cur_process->instruction, 3)) || \
		(!ft_strncmp("exit", cur_process->instruction, 5)) || \
		(!ft_strncmp("env", cur_process->instruction, 4)) || \
		(!ft_strncmp("export", cur_process->instruction, 7)) || \
		(!ft_strncmp("unset", cur_process->instruction, 6)) || \
		(!ft_strncmp("pwd", cur_process->instruction, 4)) || \
		(!ft_strncmp("echo", cur_process->instruction, 5)))
		return (true);
	else
		return (false);
}

int	execute_single_builtin(t_info *info, t_process *process)
{
	int	ret;
	int	save_stdin;
	int	save_stdout;

	ret = 0;
	(void)info;
	if (check_file_is_exist(process->redirect) == -1)
		return (ENOENT);
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (process->input_file != NULL || process->heredoc)
		set_input_fd(process);
	set_output_fd(process);
	ret = execute_program(info, process);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
	return (ret);
}