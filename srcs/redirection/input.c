/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:39:09 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 13:11:47 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

static void	check_file_exists(char *file_name) //ft_isexecutable함수로도 되는지 해보기
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
		// system("leaks minishell");
		exit(ENOENT);
	}
	close(fd);
}

void	connect_heredoc(char *heredoc_str)
{//파이프 하나 더 만들어주고, fork한 후 heredoc_str [1]에 쓰고, 손자 죽음.
//자식프로세스에서 STDIN을 [0]으로 dup해줌.
	pid_t	pid;
	int		pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (heredoc_str == NULL)
		return ;
	if (pid == 0)
	{
		close(pipe_fd[0]);
		ft_putstr_fd(heredoc_str, pipe_fd[1]);
		close(pipe_fd[1]); //자식에서도 닫고 부모에서도 닫고
		// system("leaks minishell");
		exit(0);
	}
	else
	{
		close(pipe_fd[1]);
		close(STDIN_FILENO);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

void	set_input_fd(t_process *process, int input_fd)
{
	// printf("set_input_fd> heredoc_str:%s\n", process->heredoc_str);
	if (process->input_file == NULL && process->heredoc)
	{
		connect_heredoc(process->heredoc_str);
		return ;
	}
	// if (process->input_file != NULL && !process->heredoc)
	if (process->input_file != NULL)
	{
		check_file_exists(process->input_file);
		input_fd = open(process->input_file, O_RDONLY);
	}
	if (input_fd != 0)
	{
		close(STDIN_FILENO);
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
}
