/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:01:27 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/07 00:45:12 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../../includes/structure.h"
 /*
1. export a122 => a122=
2. export 1a => export: not an identifier: 1a
 */

int	execute_export(t_info *info, t_process *process)
{
	if (process->option)
	{
		return (error_option("export", info, process));
	}
	else if (!process->arg)
	{
		print_export(info->env);
	}
	else
	{
		// add_new_env(info->env, process->arg);
	}
	return (exit_process(info, process, 0));
}