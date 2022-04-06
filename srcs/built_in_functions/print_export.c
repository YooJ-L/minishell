/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 00:45:06 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/07 01:56:30 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

t_env	sort_env(t_env *env)
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
		
	}
}

void	print_export(t_env *env)
{
	t_env	*sorted;
	t_env	*temp;

	sorted = sort_env(env);
	while (temp != NULL)
	{
		temp = sorted;
		printf("declare -x");
		if (sorted->value != NULL)
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
