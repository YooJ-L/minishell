/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:39:49 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 12:14:34 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int	execute_pwd(t_info *info, t_process *process)
{
	char	buf[PATH_MAX];

	getcwd(buf, PATH_MAX); //작업중인 디렉토리의 이름을 buf에 담아서 가져오는 함수
	if (!process->option)
	{
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (exit_process(info, process, 0));
	}
	else
		return (error_option("pwd", info, process));
}
