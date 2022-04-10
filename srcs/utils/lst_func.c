/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:28:00 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 15:56:24 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

t_redirection	*redir_lstlast(t_redirection *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

void	redir_lstadd_back(t_redirection **lst, t_redirection *new)
{
	t_redirection	*tail;

	if (!(lst) || !(new))
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tail = *lst;
	while (tail->next != 0)
	{
		tail = tail->next;
	}
	tail->next = new;
}

void	ft_redir_lstclear(t_redirection **lst)
{
	t_redirection	*cur;
	t_redirection	*next;

	cur = *lst;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->filename);
		free(cur);
		cur = next;
	}
	*lst = NULL;
}