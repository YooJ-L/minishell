/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:14:06 by dim               #+#    #+#             */
/*   Updated: 2022/04/10 16:51:45 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] == ' ')
		i++;
	if (!str_is_num(arg + i))
		return (0);
	if (!str_is_long(arg + i))
		return (0);
	return (1);
}

char	*get_arg_in_exit(t_info *info, t_process *process)
{
	if (process->option)
		return (process->option->content);
	else if (process->arg)
		return (process->arg->content);
	else
	{
		if (info->process_cnt == 1)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		// system("leaks minishell");
		exit (0);
	}
}

void	print_exit(t_info *info, int fd)
{
	if (info->process_cnt == 1)
		ft_putstr_fd("exit\n", fd);
}

void	exit_find_and_perror(t_info *info, int errnum, char *arg)
{
	if (errnum == 1)
	{
		print_exit(info, STDERR_FILENO);
		ft_putstr_fd("bash: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	if (errnum == 2)
	{
		print_exit(info, STDERR_FILENO);
		ft_putstr_fd("bash: exit", STDERR_FILENO);
		ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	}
}

int	execute_exit(t_info *info, t_process *process)
{
	unsigned char	exit_status;
	char			*arg;

	arg = get_arg_in_exit(info, process);
	if (!check_arg(arg))
	{
		exit_find_and_perror(info, 1, arg);
		free_process(process);
		free_envp(info);
		// system("leaks minishell");
		exit(255);
	}
	exit_status = ft_atoi(arg);
	if (process->arg->next)
	{
		exit_find_and_perror(info, 2, arg);
		return (exit_process(info, process, 1));
	}
	else
	{
		print_exit(info, STDOUT_FILENO);
		free_process(process);
		free_envp(info);
		// system("leaks minishell");
		exit(exit_status);
	}
	return (1);
}
