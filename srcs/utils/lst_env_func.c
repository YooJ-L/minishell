/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:13:41 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/07 02:52:38 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

t_env	*env_lst_new(char **arr)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	new->key = arr[0];
	new->value = arr[1];
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
		(*env)->next = NULL; //추가
		return ;
	}
	tail = *env;
	while (tail->next != 0)
	{
		tail = tail->next;
	}
	tail->next = new;
	tail->next->next = NULL; //마지막에 널 추가
}

void	ft_env_lstclear(t_env **lst)
{
	t_env	*cur;
	t_env	*next;

	cur = *lst;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->key); //?
		free(cur->value);
		free(cur);
		cur = next;
	}
	*lst = NULL;
}

t_env	*env_node_exists(t_env *env, char *new_key)
{
	t_env	*node;

	node = env;
	while (node != NULL)
	{
		if (strncmp(new_key, node->key, ft_strlen(new_key)))
			break ;
		node = node->next;
	}
	return (node);
}

void	modify_env_node(t_env *env, char *new_key, char *new_value)
{
	t_env	*node;
	t_env	*new;
	char	**arr;

	node = env_node_exists(env, new_key);
	if (node == NULL)
	{
		arr = (char **)malloc(sizeof(char *) * 2);
		if (!arr)
			perror_and_exit("cannot allocate memory\n", ENOMEM);
		arr[0] = new_key;
		arr[1] = new_value;
		new = env_lst_new(arr);
		env_lstadd_back(&env, new);
		free(arr);
	}
	else if (new_value)
	{
		free (node->value);
		node->value = new_value;
	}
}
