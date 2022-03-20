/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:16:40 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/21 00:31:15 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"

int	init(t_info *info, char **envp)
{
	if (!parse_env(&(info->env), envp))
		return (0);
	return (1);
}
void	test(t_process *process)
{
	process->instruction = ft_strdup("echo");
	process->option = ft_lstnew("-nnnn\0");
	// process->option->next = ft_lstaddback();
	process->arg = ft_lstnew("dim\0");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info		info;
	t_process	*process;
	char		*input;

	(void)argc;
	(void)argv;
	// process = NULL;
	process = (t_process *)malloc(sizeof(t_process));
	info.env = NULL;
	if (!init(&info, envp))
	{
		printf("init fail\n");
		return (-1);
	}
	info.process = process;
	test(process);
	// printf("option: %s\n", process->option->content);
	// printf("arg: %s\n", process->arg->content);
	while (1)
	{
		input = readline("tinyshell$ ");
		if (!input)
		{
			make_error();
		}
		add_history(input);
		execute_echo(&info, process);
		// execute_env(&info, process);
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