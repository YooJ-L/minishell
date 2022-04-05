/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:39:14 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/04 18:57:18 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int	find_last_output_index(t_redirection *redirect)
{
	int				i;
	int				last;

	i = 0;
	last = -1;
	while (redirect)
	{
		if (redirect->symbol == SINGLE_OUT || redirect->symbol == DOUBLE_OUT)
			last = i;
		i++;
		redirect = redirect->next;
	}
	return (last);
}

void	set_file(t_redirection *redirect)
{
	int				fd;

	while (redirect)
	{
		if (redirect->symbol == DOUBLE_OUT)
		{//append가 아니라 excl?
			fd = open(redirect->filename, O_CREAT | O_EXCL, 0644); //없으면 만들고, 있으면 열지 않고
			close(fd);
		}
		else if (redirect->symbol == SINGLE_OUT)
		{
			fd = open(redirect->filename, O_CREAT | O_TRUNC, 0644); //없으면 만들고, 있으면 내용 지우고
			close(fd);
		}
		redirect = redirect->next;
	}
}

void	connect_last_file(t_list *redirect, int last)
{
	int				fd;
	int	i;

	i = 0;
	while (i < last)
	{
		redirect = redirect->next;
		i++;
	}
	fd = open(redirect->file_name, O_RDWR | O_APPEND);
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirect_output_fd(t_process *process)
{
	int		last;
	t_list	*redirect;

	redirect = process->redirect;
	last = find_last_output_index(redirect);
	if (last == -1)
		return ;
	set_file(redirect);
	connect_last_file(redirect, last);
}

void	set_output_fd(t_process *process, int pipe_fd[2], bool is_last)
{
	if (!is_last)
	{
		close(pipe_fd[0]);
		close(STDOUT_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	redirect_output_fd(process);
}
