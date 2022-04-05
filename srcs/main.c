/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:16:40 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/05 20:57:29 by yoojlee          ###   ########.fr       */
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
	// process->option = ft_lstnew("-n");
	// ft_lstadd_back(&(process->option), ft_lstnew("-nnm"));
	// ft_lstadd_back(&(process->option), ft_lstnew("-----n"));
	// process->arg = ft_lstnew("dim");
	// ft_lstadd_back(&(process->arg), ft_lstnew("1234"));
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
		if (!validate_input(info, input))
		{

		}
		add_history(input);
		//프로세스 파싱
		process = parse_process(info, input);
		if (!validate_process(info, process))
		{

		}
		//heredoc먼저 처리(입력값 받아옴)
		if (!run_heredoc(&info, process))
		{
			
		}
		execute(&info, process);
		free_all(info, process, input);
	}
	return (0);
}

	// while (info.env)
	// {
	// 	printf("%s=%s\n", info.env->key, info.env->value);
	// 	info.env = info.env->next;
	// }