/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:26:34 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/09 18:35:15 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)))
	}
}

int	excute_cd(t_info *info, t_process *process)
{
	char	*to_dir;

	if (process->option)
		return (error_option());
	if (process->arg)
		to_dir = (char *)(process->arg->content);
	else
		to_dir = get_env_value(info->env, "HOME");
}