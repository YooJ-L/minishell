/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:39:49 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 15:48:07 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int	execute_pwd(t_info *info, t_process *process)
{
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	if (!process->option)
	{
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (exit_process(info, process, 0));
	}
	else
		return (error_option("pwd", info, process));
}
