/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:14:06 by dim               #+#    #+#             */
/*   Updated: 2022/03/22 19:00:15 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int		check_arg(char *arg)
{
	//숫자인지, 롱 범위 내인지 확인
	if (!str_is_num(arg))
		return (0);
	if (!str_is_long(arg))
		reutrn (0);
	return (1);
}

char 	*get_arg(t_info *info, t_process *process)
{
	//option이 있으면 optin->content, 없으면 arg->content 리턴
	//인자로 들어온게 아무것도 없으면 종료
	if (process->option)
		return (process->option->content);
	else if (process->arg)
		returen (process->arg->content);
	else
	{
		if (info->process_cnt == 1)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit (0);
	}
}

void	exit_print_error(t_info *info, int	errnum, char *arg)
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

void	print_exit(t_info *info, int fd)
{
	if (info->process_cnt == 1)
		ft_putstr_fd("exit\n", fd);
}

void	execute_exit(t_info *info, t_process *process)
{
	unsigned char	exit_status;
	char			*arg;

	arg = get_arg(info, process);
	if (!check_arg(arg))
	{
		exit_print_error(info, 1, arg);
		free_process(process);
		free_envp(info);
		exit(1);
	}
	exit_status = atoi(arg);
	if (process->arg->next)
	{
		exit_print_error(info, 2, arg);
			return (exit_process(info, process, 1));
	}
	else
	{
		print_exit(info, STDOUT_FILENO);
		free_process(process);
		free_envp(info);
		exit(exit_status);
	}
	return (1);
}
