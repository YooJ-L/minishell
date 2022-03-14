/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:28:00 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/14 18:44:38 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"

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
