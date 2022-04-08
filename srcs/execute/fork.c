/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:17:06 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/08 12:44:23 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int	execve_command(t_info *info, t_process *cur_process)
{
	printf("execve_command\n");
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

void	set_child_process(t_process *process, int pipe_fd[2], int input_fd, bool is_last)
{
	signal(SIGQUIT, SIG_DFL); //sig_dfl: 기본 행동 하게 한다.(원래 상태로)
	set_input_fd(process, input_fd);
	set_output_fd(process, pipe_fd, is_last);
}

void	fork_processes(t_info *info, t_process *process)
{
	int	i;
	int	input_fd;
	int	pipe_fd[2];

	i = -1;
	input_fd = 0;
	while (++i < info->process_cnt)
	{
		if (i < info->process_cnt - 1)
			pipe(pipe_fd);
		(&process[i])->pid = fork();
		// if (process[i].pid < 0)
		//	error();
		if (process[i].pid == 0)
		{
			set_child_process(&process[i], pipe_fd, input_fd, i == info->process_cnt - 1);
			execve_command(info, &process[i]);
		}
		else if (process[i].pid > 0)
		{
			if (input_fd != 0)
				close(input_fd);
			if (i < info->process_cnt - 1)
			{
				close(pipe_fd[1]);
				input_fd = pipe_fd[0];
			}
		}
	}
}
