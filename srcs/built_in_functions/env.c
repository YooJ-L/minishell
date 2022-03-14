/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:00:34 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/14 19:09:43 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	print_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, "_", 2) == 0)
		{
			temp = temp->next;
			continue ;
		}
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	printf("_=/usr/bin/env\n"); //여기 끝에 개행 넣어줘야 하나?
}

int		execute_env(t_info *info, t_process *process)
{
	//arg x, option x 일 때만 실행.
	// if (process->arg)
	// {

	// }
	// else if (process->option)
	// {

	// }
	// else
		print_env(info->env);
	return (1);
	// return (exit_process(info, process, 0));
}