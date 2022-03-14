/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:27:30 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/14 19:08:23 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"
/*
1. arg o, option x
2. option 여러개도 가능 ex) unset a b c
3. Unsetting a variable or function that was not previously set
       shall not be considered an error and does not cause the shell to
       abort.
4. unset 숫자 x ex) unset 12a(x)
5. unset 문자+숫자 o ex) unset a999, unset abcd123
6. unset @ 들어가면 X 앞뒤에 뭐가 오든 안됨.
7. unset 1a(안되는 것) a(지울 것) b(지울 것) => a b 지워지고 bash: unset: `1a': not a valid identifier 나옴.
*/

void	delete_content(t_env *env, char *key)
{
	t_env	*node_to_link;

	while (env->next)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
		{
			free(env->key);
			free(env->value);
			node_to_link->next = env->next;
			env->next = NULL;
			free(env);
		}
		node_to_link = env;
		env = env->next;
	}
}

bool	validate_unset_arg(char *content)
{
	return (true);
}

int		execute_unset(t_info *info, t_process *process)
{
	bool	success_flag;

	success_flag = 1;
	if (!process->arg)
	{
		//unset: not enough arguments
	}
	if (process->option)
	{

	}
	while (process->arg->next)
	{
		if (!validate_unset_arg(process->arg->content))
		{
			success_flag = 0;
			process->arg = process->arg->next;
			continue ;
		}
		delete_content(info->env, process->arg->content);
		process->arg = process->arg->next;
	}
	return (1);
}