/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 18:58:04 by dim               #+#    #+#             */
/*   Updated: 2022/03/24 06:04:06 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int		exit_process(t_info *info, t_process *process, int exit_status)
{
	if (info->process_cnt == 1)
		return (exit_status);
	else
	{
	// 	free_process(process);
	// 	free_envp(info);
		exit(exit_status);
	}
}