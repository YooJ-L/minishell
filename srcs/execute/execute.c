/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:30:45 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/07 01:05:05 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int	execve_command(t_info *info, t_process *cur_process)
{
	if (!cur_process->instruction)
		return (exit_process(info, cur_process, info->last_exit_status));
	if (!ft_strncmp("cd", cur_process->instruction, 3))
		return (execute_cd(info, cur_process));
	else if (!ft_strncmp("exit", cur_process->instruction, 5))
		return (execute_exit(info, cur_process));
	else if (!ft_strncmp("env", cur_process->instruction, 4))
		return (execute_env(info, cur_process));
	else if (!ft_strncmp("export", cur_process->instruction, 7))
		return (execute_export(info, cur_process));
	else if (!ft_strncmp("unset", cur_process->instruction, 6))
		return (execute_unset(info, cur_process));
	else if (!ft_strncmp("pwd", cur_process->instruction, 4))
		return (execute_pwd(info, cur_process));
	else if (!ft_strncmp("echo", cur_process->instruction, 5))
		return (execute_echo(info, cur_process));
	else
		execute_etc_instruction(info, cur_process);
	return (0);
}

static int	check_file_exists(t_redirection *redirect)
{
	int				fd;

	while (redirect)
	{
		if (redirect->symbol == SINGLE_IN)
		{
			fd = open(redirect->filename, 0);
			if (fd < 0)
			{
				ft_putstr_fd("bash: ", STDERR_FILENO);
				ft_putstr_fd(redirect->filename, STDERR_FILENO);
				ft_putstr_fd(": ", STDERR_FILENO);
				ft_putstr_fd(strerror(ENOENT), STDERR_FILENO);
				ft_putchar_fd('\n', STDERR_FILENO);
				return (-1);
			}
			close(fd);
		}
		redirect = redirect->next;
	}
	return (0);
}

int	execute_single_builtin(t_info *info, t_process *process)
{
	int	ret;
	int	save_stdin;
	int	save_stdout;

	ret = 0;
	(void)info;
	if (check_file_exists(process->redirect) == -1)
		return (ENOENT);
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (process->input_file != NULL || process->heredoc)
		set_input_fd(process, 0);
	redirect_output_fd(process);
	ret = execve_command(info, process);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdout);
	return (ret);
}
