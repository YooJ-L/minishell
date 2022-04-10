/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:39:09 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 17:38:50 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	check_file_exists_exit(char *file_name)
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
{
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
		close(pipe_fd[1]);
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
	t_redirection	*temp;

	temp = process->redirect;
	while (temp)
	{
		check_file_exists_exit(process->redirect->filename);
		temp = temp->next;
	}
	if (process->input_file == NULL && process->heredoc)
	{
		connect_heredoc(process->heredoc_str);
		return ;
	}
	if (process->input_file != NULL)
	{
		check_file_exists_exit(process->input_file);
		input_fd = open(process->input_file, O_RDONLY);
	}
	if (input_fd != 0)
	{
		close(STDIN_FILENO);
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
}
