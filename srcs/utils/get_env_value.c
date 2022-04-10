/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 03:31:34 by dim               #+#    #+#             */
/*   Updated: 2022/04/10 16:57:53 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (!(ft_strncmp(env->key, key, ft_strlen(key) + 1)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
