/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:34:21 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 15:57:17 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"
#include "../includes/parsing.h"

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
		if (!run_heredoc(info, process) || check_redirect(info, process))
		{
			free_all(info, process, input);
			// system("leaks minishell");
			continue ;
		}
		echoctl_on();
		execute(info, process);
		free_all(info, process, input);
	}
}

void	set_shlvl(t_info *info)
{
	char	*key;
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
	key = ft_strdup("SHLVL");
	modify_env_node(info->env, key, shlvl_ch);
}

int	init(t_info *info, char **envp)
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
	if (!init(&info, envp))
	{
		free_envp(&info);
		return (-1);
	}
	loop_minishell(&info, process);
	return (0);
}