/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:17:06 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/03 18:53:42 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int	execute_program(t_info *info, t_process *cur_process)
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

void	heredoc_str_to_pipe(t_process *process, int pipe_fd[2])
{
	if (process->heredoc)
	{
		ft_putstr_fd(process->heredoc_str, pipe_fd[1]);
	}
}

void	check_file_exists(char *file_name)
{
	int	fd;

	fd = open(file_name, 0);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(file_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(ENOENT), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		exit(ENOENT);
	}
	close(fd);
}

void	set_input_fd(t_process *process, int pipe_fd[2], int idx)
{
	if (process->input_file != NULL)
	{
		check_file_exists(process->input_file);
	}
}

void	child_process(t_info *info, t_process *process, int pipe_fd[2], int idx)
{
	signal(SIGQUIT, SIG_DFL);
	set_input_fd(process, pipe_fd, idx);
	set_output_fd(process, pipe_fd, idx);
	execve_command(info, process);
}

void	fork_processes(t_info *info, t_process *process)
{
	int	i;
	int	pipe_fd[2];

	i = -1;
	while (++i < info->process_cnt)
	{
		if (i < info->process_cnt - 1)
			pipe(pipe_fd);
		heredoc_str_to_pipe(pipe_fd, process[i]);
		(&process[i])->pid = fork();
		if (process[i].pid < 0)
		//	error();
		if (process[i].pid == 0)
			child_process(info, process, pipe_fd, i);
		else if (process[i] > 0)
		
	}
}

void	execute(t_info *info, t_process *process)
{
	int	last_exit_status;
	int	first_exit_status;

	if (info->process_cnt == 1 && is_builtin_ft(&process[0]))
		info->last_exit_status = execute_single_builtin(info, &process[0]);
	else
	{
		//reset_output_mode
		fork_processes(info, process);
		signal(SIGINT, SIG_IGN);
		//첫번째 명령어와 마지막 명령어를 실행하는 자식들은 무조건 끝날 때까지 기다림.
		waitpid(process[info->process_cnt - 1].pid, &last_exit_status, 0);
		waitpid(process[0].pid, &first_exit_status, 0);
		if (info->process_count == 1)
			sig_exit_handler(last_exit_status);
		else
			sig_exit_handler(first_exit_status);
		while (wait(NULL) > 0)
			;
		info->last_exit_status = last_exit_status / 256;
	}
}