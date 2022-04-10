/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 02:56:12 by dim               #+#    #+#             */
/*   Updated: 2022/04/10 16:53:53 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	perror_in_parsing(char *line)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(line, STDERR_FILENO);
	ft_putstr_fd("\'", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	check_quote(const char chr, int *status)
{
	if (chr == '\'' && *status == NO_Q)
	{
		*status = SINGLE_Q;
		return (1);
	}
	else if (chr == '\'' && *status == SINGLE_Q)
	{
		*status = NO_Q;
		return (1);
	}
	else if (chr == '\"' && *status == NO_Q)
	{
		*status = DOUBLE_Q;
		return (1);
	}
	else if (chr == '\"' && *status == DOUBLE_Q)
	{
		*status = NO_Q;
		return (1);
	}
	return (0);
}
