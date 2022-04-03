/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:28:00 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/03 19:24:19 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

t_env	*env_lst_new(char **arr)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = arr[0];
	new->value = arr[1];
	new->next = NULL;
	return (new);
}

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

void	env_lstadd_back(t_env **env, t_env *new)
{
	t_env	*tail;

	if (!(env) || !(new))
		return ;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	tail = *env;
	while (tail->next != 0)
	{
		tail = tail->next;
	}
	tail->next = new;
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