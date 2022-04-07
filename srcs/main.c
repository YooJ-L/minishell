/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:16:40 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/07 14:23:22 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"
#include "../includes/parsing.h"

void	set_inputfile_and_heredoc(t_process *process, t_redirection *redirect)
{
	process->input_file = redirect->filename;
	if (redirect->symbol == DOUBLE_IN)
	{
		process->input_file = NULL;
		process->heredoc = true;
	}
}
int		check_redirect(t_info *info, t_process *process)
{
	int				i;
	t_redirection	*cur;
	char			*last_filename;

	printf("====in check_redirect====\n");
	if (process == NULL)
		return (1);
	i = 0;
	while (i < info->process_cnt)
	{
		cur = process[i].redirect;
		while (cur != NULL)
		{
			if (cur->filename == NULL)
			{
				perror_in_parsing("newline");
				return (1);
			}
			else if (cur->symbol == SINGLE_IN || cur->symbol == DOUBLE_IN)
				set_inputfile_and_heredoc(process, cur);
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
		if (!validate_input(info, input))
			continue ;
		add_history(input);
		process = split_line(input, info);
		//heredoc먼저 처리(입력값 받아옴)
		if (!run_heredoc(info, process) || check_redirect(info, process))
		{
			printf("====in run_heredoc || check_redirect\n");
			free_all(info, process, input);
			return ;
		}
		execute(info, process);
		free_all(info, process, input);
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
		shlvl_ch = ft_itoa(shlvl_int + 1);
	}
	modify_env_node(info->env, "SHLVL", shlvl_ch);
}

int	init(t_info *info, t_process *process, char **envp)
{
	info->last_exit_status = 0;
	info->env = NULL;
	info->process_cnt = 0;
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
		free_envp(&info);
		return (-1);
	}
	loop_minishell(&info, process);
	return (0);
}
