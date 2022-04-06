/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:20:59 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/06 21:57:51 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	validate_input(t_info *info, char *input)
{
	if (!input)
	{
		write(1, "\033[1A", 5); //?
		write(1, "\033[9C", 5);
		write(1, "exit\n", 5);
		reset_input_mode(&(info->org_term));
		free_envp(info);
		exit(0);
	}
	if (input[0] == '\0')
		return (0);
	return (1);
}
