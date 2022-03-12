/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:16:40 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/12 21:42:46 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"

int	init(t_info *info, char **envp)
{
	if (!parse_env(&(info->env), envp))
		return (0);
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info	info;
	char	*input;

	(void)argc;
	(void)argv;
	info.env = NULL;
	if (!init(&info, envp))
	{
		printf("init fail\n");
		return (-1);
	}
	while (info.env)
	{
		printf("%s=%s\n", info.env->key, info.env->value);
		info.env = info.env->next;
	}
	while (1)
	{
		input = readline("tinyshell$ ");
		if (!input)
		{
			make_error();
		}
		add_history(input);
		// save_process(&process, input);
		// execute(input, &info);
		free(input);
	}
	return (0);
}
