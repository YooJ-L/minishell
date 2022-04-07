/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:17:06 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/07 11:50:15 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	set_child_process(t_process *process, int pipe_fd[2], int input_fd, bool is_last)
{
	signal(SIGQUIT, SIG_DFL);
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
		else if (process[i].pid > 0) // processp[i]였음
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

void	execute(t_info *info, t_process *process)
{
	int	last_exit_status;
	int	first_exit_status;

	printf("=====@@@@@in execute.c\n");
	if (info->process_cnt == 1 && is_builtin_ft(&process[0]))
		info->last_exit_status = execute_single_builtin(info, &process[0]);
	else
	{
		reset_input_mode();
		fork_processes(info, process);
		signal(SIGINT, SIG_IGN);
		//첫번째 명령어와 마지막 명령어를 실행하는 자식들은 무조건 끝날 때까지 기다림.
		waitpid(process[info->process_cnt - 1].pid, &last_exit_status, 0);
		waitpid(process[0].pid, &first_exit_status, 0);
		if (info->process_cnt == 1)
			sig_exit_handler(last_exit_status);
		else
			sig_exit_handler(first_exit_status);
		while (wait(NULL) > 0)
			;
		info->last_exit_status = last_exit_status / 256;
	}
}