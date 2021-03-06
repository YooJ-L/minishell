/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:00:34 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 18:08:52 by dim              ###   ########.fr       */
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
		if (temp->value != NULL)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	printf("_=%s\n", address);
}

int	execute_env(t_info *info, t_process *process)
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
	return (exit_process(info, process, 0));
}
