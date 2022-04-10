/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:13:41 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 15:56:15 by yoojlee          ###   ########.fr       */
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

t_env	*env_lstlast(t_env *env)
{
	t_env	*temp;

	if (env == NULL)
	{
		return (NULL);
	}
	temp = env;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}

void	env_lstadd_back(t_env **env, t_env *new)
{
	t_env	*tail;

	if (!(env) || !(new))
		return ;
	if (*env == NULL)
	{
		*env = new;
		(*env)->next = NULL;
		return ;
	}
	tail = env_lstlast(*env);
	new->next = tail->next;
	tail->next = new;
}

t_env	*env_node_exists(t_env *env, char *new_key)
{
	t_env	*node;

	node = env;
	if (!new_key || !env)
		return (NULL);
	while (node != NULL)
	{
		if (ft_strncmp(new_key, node->key, ft_strlen(new_key) + 1) == 0)
			break ;
		node = node->next;
	}
	return (node);
}

void	modify_env_node(t_env *env, char *new_key, char *new_value)
{
	t_env	*node;

	node = env_node_exists(env, new_key);
	if (node == NULL)
	{
		node = env;
		while (node->next != NULL)
			node = node->next;
		node->next = (t_env *)malloc(sizeof(t_env));
		if (!node->next)
			perror_and_exit("cannot allocate memory\n", ENOMEM);
		node->next->key = new_key;
		node->next->value = new_value;
		node->next->next = NULL;
	}
	else if (new_value != NULL)
	{
		free(new_key);
		free(node->value);
		node->value = new_value;
	}
	else
		free(new_key);
}