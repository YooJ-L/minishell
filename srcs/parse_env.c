/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:01:26 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/10 17:01:20 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"

int		parse_env(t_env	**env, char **envp)
{
	int	i;
	char	**arr;
	t_env	*new;

	i = -1;
	while (envp[++i])
	{
		arr = ft_split(envp[i], '=');
		new = env_lst_new(arr);
		env_lstadd_back(env, new);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = NULL;
	parse_env(&env, envp);
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env=env->next;
	}
	return (0);
}

/*
컴파일 시 명령어
gcc parse_env.c env_lst_new.c env_lstadd_back.c -L ../includes/libft/ -lft
*/