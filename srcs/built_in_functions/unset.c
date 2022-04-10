/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:27:30 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 19:06:30 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

static void	free_target(t_env *target)
{
	free(target->key);
	free(target->value);
	free(target);
}

void	delete_env(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*target;
	int		len;

	tmp = *env;
	len = ft_strlen(str);
	if (!ft_strncmp(tmp->key, str, len + 1))
	{
		tmp = tmp->next;
		free(*env);
		*env = tmp;
		return ;
	}
	while (tmp->next != NULL)
	{
		if (!ft_strncmp(tmp->next->key, str, len + 1))
		{
			target = tmp->next;
			tmp->next = target->next;
			free_target(target);
			return ;
		}
		tmp = tmp->next;
	}
}

int	execute_unset(t_info *info, t_process *process)
{
	t_list	*arg;
	char	*target;

	if (!info->env)
		return (exit_process(info, process, 0));
	if (process->option)
		return (error_option("unset", info, process));
	arg = process->arg;
	while (arg != NULL)
	{
		target = (char *)arg->content;
		if (env_is_valid(target))
			delete_env(&info->env, target);
		else
		{
			ft_putstr_fd("bash: unset: `", STDERR_FILENO);
			ft_putstr_fd(target, STDERR_FILENO);
			ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
		}
		arg = arg->next;
	}
	return (exit_process(info, process, 0));
}
