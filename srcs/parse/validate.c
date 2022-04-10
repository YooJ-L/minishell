/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:20:59 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 17:12:20 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	validate_input(t_info *info, char *input)
{
	if (!input)
	{
		write(1, "\033[1A", 5);
		write(1, "\033[11C", 6);
		write(1, "exit\n", 6);
		echoctl_on();
		free_envp(info);
		// system("leaks minishell");
		exit(0);
	}
	if (input[0] == '\0')
	{
		free(input);
		return (0);
	}
	return (1);
}

void	validate_input_heredoc(char **input)
{
	if (*input && *input[0] == '\0')
	{
		free(*input);
		*input = ft_strdup("\n");
	}
}
