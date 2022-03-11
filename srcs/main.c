/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:16:40 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/11 14:03:49 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"

int	init(t_info *info, const char **envp)
{
	parse_env(&info->env, envp);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info	info;
	char	*input;

	(void)argc;
	(void)argv;
	if (!init(&info, envp))
		return (-1);
	while (1)
	{
		input = readline("tinyshell$ ");
		if (!input)
		{
			make_error();
		}
		add_history(input);
		// save_process(&process, input);
		execute(input, env);
		free(input);
	}
	return (0);
}
