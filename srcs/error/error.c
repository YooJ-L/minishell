/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:17:39 by yoojlee           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/04/06 22:28:00 by yoojlee          ###   ########.fr       */
=======
/*   Updated: 2022/04/06 21:57:37 by dim              ###   ########.fr       */
>>>>>>> 41ad51c788ad6756fb42c15c6132237bd7bb9d96
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
