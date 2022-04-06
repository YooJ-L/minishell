/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:28:00 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/06 19:14:45 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

t_redirection *redir_lst_new(char **arr)
{
	t_redirection	*new;

	new = (t_redirection *)malloc(sizeof(t_redirection));
	if (new == NULL)
		return (NULL);
	new->symbol = arr[0];
	new->filename = arr[1];
	new->next = NULL;
	return (new);
}

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