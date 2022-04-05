/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:04:21 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/05 17:42:42 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

bool	is_builtin_ft(t_process *cur_process)
{
	if ((!cur_process->instruction) || \
		(!ft_strncmp("cd", cur_process->instruction, 3)) || \
		(!ft_strncmp("exit", cur_process->instruction, 5)) || \
		(!ft_strncmp("env", cur_process->instruction, 4)) || \
		(!ft_strncmp("export", cur_process->instruction, 7)) || \
		(!ft_strncmp("unset", cur_process->instruction, 6)) || \
		(!ft_strncmp("pwd", cur_process->instruction, 4)) || \
		(!ft_strncmp("echo", cur_process->instruction, 5)))
		return (true);
	else
		return (false);
}
