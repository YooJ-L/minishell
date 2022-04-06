/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:16:40 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/06 20:51:42 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"
#include "../includes/parsing.h"

int		check_redirect(t_info *info, t_process *process)
{
	int				i;
	t_redirection	*cur;
	char			*last_filename;

	if (process == NULL)
		return (1);
	i = 0;
	while (i < info->process_cnt)
	{
		cur = process[i].redirect;
		while (cur != NULL)
		{
			if (cur->symbol == DOUBLE_IN)
				process->heredoc = true;
			if (cur->filename == NULL)
			{
				perror_in_parsing("newline");
				return (1);
			}
			else if (cur->symbol == SINGLE_IN)
				process->input_file = cur->filename;
			cur = cur->next;
		}
		i++;
	}
	return (0);
}

void	loop_minishell(t_info *info, t_process *process)
{
	char	*input;

	while (1)
	{
		set_parent_process(info);
		input = readline("tinyshell$ ");
		// if (!validate_input(info, input))
		// 	continue ;
		add_history(input);
		process = split_line(input, info);
		//heredoc먼저 처리(입력값 받아옴)
		if (!run_heredoc(info, process) || check_redirect(info, process))
		{
			//free_all(&info, process, output);
			return ;
		}
		execute(info, process);
		// free_all(info, process, input);
	}
}

void	set_shlvl(t_info *info)
{
	int		shlvl_int;
	char	*value;
	char	*shlvl_ch;

	value = getenv("SHLVL");
	if (value == NULL)
	{
		shlvl_ch = ft_strdup("1");
	}
	else
	{
		shlvl_int = ft_atoi(value);
		shlvl_ch = ft_itoa(n + 1);
	}
	modify_env_node(info->env, "SHLVL", shlvl_ch);
}

int	init(t_info *info, t_process *process, char **envp)
{
	if (!parse_env(&(info->env), envp))
		return (0);
	set_shlvl(info);
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info		info;
	t_process	*process;

	(void)argc;
	(void)argv;
	process = NULL;
	if (!init(&info, process, envp))
	{
		printf("init fail\n");
		return (-1);
	}
	loop_minishell(&info, process);
	return (0);
}
