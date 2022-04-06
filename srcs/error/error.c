/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:17:39 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/06 22:28:00 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	perror_and_exit(char *text, int	errnum)
{
	ft_putstr_fd(text, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(errnum);
}

int		error_option(char	*inst, t_info *info, t_process *process)
{
	char	*option;

	option = (char *)(process->option->content);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(inst, STDERR_FILENO);
	ft_putstr_fd(": -", STDERR_FILENO);
	ft_putchar_fd(option[1], STDERR_FILENO);
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	return (exit_process(info, process, 1));
}

void	quit_program(t_info *info)
{
	write(1, "\033[1A", 5);
	write(1, "\033[9C", 5);
	write(1, "exit\n", 5);
	reset_input_mode();
	free_envp(info);
	exit(0);
}
