/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:00:34 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/06 22:48:54 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	print_env(t_env *env)
{
	t_env	*temp;
	char	*address;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, "_", 2) == 0)
		{
			address = temp->value;
			temp = temp->next;
			continue ;
		}
		if (temp->value == NULL)
			continue ;
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	printf("_=%s\n", address);
}

int		execute_env(t_info *info, t_process *process)
{
	void	*option;
	
	if (process->arg)
	{
		ft_putstr_fd("bash: env: too many arguments\n", STDERR_FILENO);
		return (exit_process(info, process, 1));
	}
	else if (process->option)
	{
		option = (char *)(process->option->content);
		ft_putstr_fd("env : illegal option -- ", STDERR_FILENO);
		ft_putstr_fd(&(option[1]), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (exit_process(info, process, 1));
	}
	else
		print_env(info->env);
	return (1);
	// return (exit_process(info, process, 0));
}