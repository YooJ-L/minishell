/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:16:40 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/22 19:10:28 by dim              ###   ########.fr       */
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
	process->instruction = NULL;
	process->option = NULL;
	process->arg = NULL;
	process->instruction = ft_strdup("exit");
	process->option = ft_lstnew("-n");
	// ft_lstadd_back(&(process->option), ft_lstnew("-nnm"));
	// ft_lstadd_back(&(process->option), ft_lstnew("-----n"));
	process->arg = ft_lstnew("dim");
	ft_lstadd_back(&(process->arg), ft_lstnew("1234"));
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
	info.process_cnt = 1;
	process = (t_process *)malloc(sizeof(t_process));
	if (!init(&info, envp))
	{
		printf("init fail\n");
		return (-1);
	}
	info.process = process;
	test(process);
	while (1)
	{
		input = readline("tinyshell$ ");
		if (!input)
		{
			make_error();
		}
		add_history(input);
		execute_exit(&info, process);
		// execute_echo(&info, process);
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