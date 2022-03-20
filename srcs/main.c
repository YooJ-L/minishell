/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:16:40 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/20 21:32:23 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"

int	init(t_info *info, char **envp)
{
	if (!parse_env(&(info->env), envp))
		return (0);
	return (1);
}

void	test(t_info *info)
{
	t_process *process;

	process = info->process;
	process->instruction = "echo";
	process->option = ft_lstnew("-nnnnn");
	// process->option->next = ft_lstaddback();
	process->option->next->next = NULL;
	process->arg = ft_lstnew("dim");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info		info;
	t_process	*process;
	char		*input;

	(void)argc;
	(void)argv;
	process = NULL;
	info.env = NULL;
	if (!init(&info, envp))
	{
		printf("init fail\n");
		return (-1);
	}
	test(&info);
	while (1)
	{
		input = readline("tinyshell$ ");
		if (!input)
		{
			make_error();
		}
		add_history(input);
		execute_echo(&info, process);
		execute_env(&info, process);
		// save_process(&process, input);
		// execute(input, &info);
		free(input);
	}
	return (0);
}

	// while (info.env)
	// {
	// 	printf("%s=%s\n", info.env->key, info.env->value);
	// 	info.env = info.env->next;
	// }