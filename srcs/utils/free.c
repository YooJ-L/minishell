/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:26:09 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/08 12:46:28 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	free_envp(t_info *info)
{
	t_env	*cur;
	t_env	*next;

	cur = info->env;
	while (cur)
	{
		free(cur->key);
		free(cur->value);
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void	free_redirection(t_redirection **redirect)
{
	t_redirection *temp;

	while (temp)
	{
		free (temp->filename);
		temp->filename = NULL;
		temp = temp->next;
	}
	ft_redir_lstclear(redirect);
}

void	free_process(t_process *process)
{
	if (process->instruction)
		free(process->instruction);
	if (process->heredoc_str)
		free(process->heredoc_str);
	if (process->input_file)
		// free(process->input_file); //redirect->filename그대로 주소 복사?
	if (process->option)
		ft_lstclear(&process->option, free);
	if (process->arg)
		ft_lstclear(&process->arg, free);
	if (process->redirect)
		ft_redir_lstclear(&process->redirect);
}

void	free_all(t_info *info, t_process *process, char *input)
{
	int	i;

	i = 0;
	free(input);
	if (process)
	{
		while (i < info->process_cnt)
		{
			free_process(&process[i]);
			i++;
		}
		free(process);
	}
}