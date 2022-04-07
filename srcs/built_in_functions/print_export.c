/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 00:45:06 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/07 20:16:08 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

static t_env *ft_env_lst_new(t_env *temp)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	new->key = temp->key;
	new->value = temp->value;
	new->next = NULL;
	return (new);
}

void	insert_new_node(t_env *sorted, t_env *new)
{
	t_env	*previous_node;
	t_env	*compare_node;

	previous_node = sorted;
	compare_node = previous_node->next;
	while (compare_node != NULL)
	{
		if (ft_strncmp(compare_node->key, new->key, \
			ft_strlen(compare_node->key) + 1) > 0)
		{
			previous_node->next = new;
			new->next = compare_node;
			return ;
		}
		previous_node = compare_node;
		compare_node = compare_node->next;
	}
	if (compare_node == NULL)
		previous_node->next = new;
}

t_env	*sort_env(t_env *env)
{
	t_env	*ret;
	t_env	*temp;
	t_env	*new;
	t_env	*sorted;

	temp = env;
	sorted = (t_env *)malloc(sizeof(t_env));
	if (!sorted)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	sorted->next = NULL;
	while (temp != NULL)
	{
		new = ft_env_lst_new(temp);
		if (sorted->next == NULL)
			sorted->next = new;
		else
			insert_new_node(sorted, new);
		temp = temp->next;
	}
	ret = sorted->next; //다 sort하고 나서도 맨 앞에꺼가 비어있나?
	free(sorted);
	return (ret);
}

void	print_export(t_env *env)
{
	t_env	*sorted;
	t_env	*temp;

	sorted = sort_env(env);
	while (sorted != NULL)
	{
		temp = sorted;
		printf("declare -x ");
		if (sorted != NULL && sorted->value != NULL)
		{
			printf("%s=", sorted->key);
			printf("\"%s\"\n", sorted->value);
		}
		else
			printf("%s\n", sorted->key);
		sorted = sorted->next;
		free(temp);
	}
	free(sorted);
}
