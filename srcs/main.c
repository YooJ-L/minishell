/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:34:21 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/09 00:34:04 by dim              ###   ########.fr       */
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
				set_inputfile_and_heredoc(&process[i], cur);
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
		input = readline("\033[0;36mtinyshell$ \033[0m");
		if (!validate_input(info, input))
			continue ;
		add_history(input);
		process = split_line(input, info);
		//heredoc먼저 처리(입력값 받아옴)
		// printf("process->inst : %s\n", process->instruction);
		if (!run_heredoc(info, process) || check_redirect(info, process))
		{
			printf("====in run_heredoc || check_redirect\n");
			free_all(info, process, input);
			continue ;
		}
		reset_input_mode(&(info->org_term));
		execute(info, process);
		free_all(info, process, input);
		// system("leaks minishell");
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
