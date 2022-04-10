/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:01:26 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 15:49:32 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	parse_env(t_env **env, char **envp)
{
	int		i;
	char	**arr;
	t_env	*new;

	i = -1;
	while (envp[++i])
	{
		arr = ft_split_in_two(envp[i], '=');
		if (!arr)
			return (0);
		new = env_lst_new(arr);
		env_lstadd_back(env, new);
		free(arr);
	}
	return (1);
}