/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:08:31 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 15:02:41 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	set_inputfile_and_heredoc(t_process *process, t_redirection *redirect)
{
	process->input_file = redirect->filename;
	if (redirect->symbol == DOUBLE_IN)
	{
		process->input_file = NULL;
		process->heredoc = true;
	}
}

int	check_redirect(t_info *info, t_process *process)
{
	int				i;
	t_redirection	*cur;

	if (process == NULL)
		return (1);
	i = 0;
	while (i < info->process_cnt)
	{
		cur = process[i].redirect;
		while (cur != NULL)
		{
			if (cur->filename == NULL)
			{
				perror_in_parsing("newline");
				return (1);
			}
			else if (cur->symbol == SINGLE_IN || cur->symbol == DOUBLE_IN)
				set_inputfile_and_heredoc(&process[i], cur);
			cur = cur->next;
		}
		i++;
	}
	return (0);
}
