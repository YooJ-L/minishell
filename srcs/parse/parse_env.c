/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:01:26 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/06 21:14:59 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int		parse_env(t_env **env, char **envp)
{
	int	i;
	char	**arr;
	t_env	*new;

	i = -1;
	while (envp[++i])
	{//=이 여러개일 때 고려해주기
		arr = ft_split_in_two(envp[i], '='); // 첫번째 = 기준으로만 자르게 하기
		if (!arr)
		{
			printf("ft_split error\n");
			// make_error();
			return (0);
		}
		new = env_lst_new(arr);
		env_lstadd_back(env, new);
		free(arr);
	}
	return (1);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_info	info;

// 	info.env = NULL;
// 	init(&info, envp);
// 	while (info.env)
// 	{
// 		printf("%s=%s\n", info.env->key, info.env->value);
// 		info.env=info.env->next;
// 	}
// 	return (0);
// }

/*
컴파일 시 명령어
gcc parse_env.c env_lst_new.c env_lstadd_back.c -L ../includes/libft/ -lft
*/