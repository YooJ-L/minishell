/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:01:27 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/16 18:21:35 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../../includes/structure.h"
 /*
1. export a122 => a122=
2. export 1a => export: not an identifier: 1a
 */

void	print_export(t_env *env)
{
	
}

int	execute_export(t_info *info, t_process *process)
{
	if (process->option)
	{
		//옵션 있으면 에러
	}
	if (!process->arg)
	{
		print_export(info->env);
		//끝내기
	}
	return (1);
}