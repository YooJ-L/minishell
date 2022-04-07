/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:30:45 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/07 21:23:52 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

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

void	execute(t_info *info, t_process *process)
{
	int	last_exit_status;
	int	first_exit_status;

	if (info->process_cnt == 1 && is_builtin_ft(&process[0]))
		info->last_exit_status = execute_single_builtin(info, &process[0]);
	else
	{
		reset_input_mode(&(info->org_term));
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
