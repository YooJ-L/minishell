/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:31:14 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/10 16:57:35 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"

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
