/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 06:24:17 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 15:51:31 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static void	exec_heredoc(const char *eof_str, int output_fd)
{
	char	*save;
	char	*input;

	save = (char *)malloc(sizeof(char) * 1);
	if (!save)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	save[0] = '\0';
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		if (input && input[0] == '\0')
			continue ;
		if (!ft_strncmp(input, eof_str, ft_strlen(eof_str) + 1))
		{
			free(input);
			break ;
		}
		save_str(&save, input);
		free(input);
	}
	add_char_to_str(&save, '\n');
	ft_putstr_fd(save, output_fd);
	free(save);
	// system("leaks minishell");
	exit(0);
}

static void	read_heredoc_str(t_process *process, int input_fd)
{
	char	*save;
	char	*temp;

	while (get_next_line(input_fd, &save) > 0)
	{
		if (!(process->heredoc_str))
		{
			process->heredoc_str = ft_strdup(save);
		}
		else
		{
			temp = process->heredoc_str;
			process->heredoc_str = ft_strjoin(temp, save);
			if (temp)
				free(temp);
		}
		add_char_to_str(&(process->heredoc_str), '\n');
		free(save);
	}
	free(save);
}

int	fork_heredoc_process(t_process *process, char *eof)
{
	pid_t	pid;
	int		exit_status;
	int		pipe_fd[2];

	if (process->heredoc_str)
	{
		free(process->heredoc_str);
		process->heredoc_str = NULL;
	}
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipe_fd[0]);
		exec_heredoc(eof, pipe_fd[1]);
	}
	signal(SIGINT, SIG_IGN);
	close(pipe_fd[1]);
	waitpid(pid, &exit_status, 0);
	read_heredoc_str(process, pipe_fd[0]);
	close(pipe_fd[0]);
	return (exit_status);
}

int	get_heredoc_input(t_process *process)
{
	char			*eof_str;
	int				exit_status;
	t_redirection	*redirect;

	redirect = process->redirect;
	while (redirect)
	{
		if (redirect->symbol == DOUBLE_IN)
		{
			if (redirect->filename == NULL)
			{
				perror_in_parsing("newline");
				return (0);
			}
			eof_str = redirect->filename;
			exit_status = fork_heredoc_process(process, eof_str);
			if (exit_status != 0)
			{
				sig_exit_handler(exit_status);
				return (0);
			}
		}
		redirect = redirect->next;
	}
	return (1);
}

int	run_heredoc(t_info *info, t_process *process)
{
	int	i;

	i = 0;
	if (!info)
		return (0);
	while (i < info->process_cnt)
	{
		if (!&process[i] || !get_heredoc_input(&process[i]))
			return (0);
		i++;
	}
	return (1);
}