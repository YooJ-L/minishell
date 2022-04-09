/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:20:59 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/08 16:07:25 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	validate_input(t_info *info, char *input)
{
	if (!input)
	{
		write(1, "exit\n", 6);
		echoctl_on();
		free_envp(info);
		exit(0);
	}
	if (input[0] == '\0')
		return (0);
	return (1);
}
