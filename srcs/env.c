/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:00:34 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/13 21:12:46 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"

void	print_env(t_env *env)
{
	while (env->next) //질문: env->next == NULL일 때 while문 안들어가면 마지막 key는 출력이 안되는거 아닌가..?
	{
		if (ft_strncmp(env->key, "_", 2) == 0)
		{
			continue ;
		}
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	// t_env *temp;

	// while (temp)
	// {
	// 	if (ft_strncmp(env->key, "_", 2) == 0)
	// 	{
	// 		continue ;
	// 	}
	// 	printf("%s=%s\n", env->key, env->value);
	// 	temp = temp->next;
	// }
	printf("_=/usr/bin/env\n"); //여기 끝에 개행 넣어줘야 하나?
}

int		execute_env(t_info *info, t_process *process)
{
	// if (process->arg)
	// {
	// 	// ft_putstr_fd("bash: env: too many arguments\n", STDERR_FILENO);
	// 	// return (exit_process(info, process, 1));
	// }
	// else if (process->option)
	// {
	// 	// option = (char *)(process->option->content);
	// 	// ft_putstr_fd("env : illegal option -- ", STDERR_FILENO);
	// 	// ft_putstr_fd(&(option[1]), STDERR_FILENO);
	// 	// ft_putstr_fd("\n", STDERR_FILENO);
	// 	// return (exit_process(info, process, 1));
	// }
	// else
		print_env(info->env);
	return (1);
	// return (exit_process(info, process, 0));
}