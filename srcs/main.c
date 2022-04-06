/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:16:40 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/06 18:06:18 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"
#include "../includes/parsing.h"

int	init(t_info *info, char **envp)
{
	if (!parse_env(&(info->env), envp))
		return (0);
	return (1);
}

int	validate_input(t_info *info, char *input)
{
	if (!input)
		quit_program(info);
	if (input[0] == '\0')
		return (0);
	return (1);
}

void	loop_minishell(t_info *info, t_process *process)
{
	char	*input;

	while (1)
	{
		set_parent_process(&info);
		input = readline("tinyshell$ ");
		if (!validate_input(info, input))
			continue ;
		add_history(input);
		if (!parse_process(process, &info, input, strlen(input)); //?
		{

		}
		if (!validate_process(info, process))
		{

		}
		//heredoc먼저 처리(입력값 받아옴)
		if (!run_heredoc(&info, process))
		{
			//free_all(&info, process, output);
			return (-1);
		}
		execute(&info, process);
		// free_all(info, process, input);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info		info;
	t_process	*process;
	char		*input;

	(void)argc;
	(void)argv;
	process = NULL;
	process = (t_process *)malloc(sizeof(t_process));
	if (!init(&info, envp))
	{
		printf("init fail\n");
		return (-1);
	}
	loop_minishell(&info, process);
	return (0);
}

	// while (info.env)
	// {
	// 	printf("%s=%s\n", info.env->key, info.env->value);
	// 	info.env = info.env->next;
	// }