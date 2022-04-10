/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:35:06 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 15:57:08 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	sig_exit_handler(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}

void	sigint_handler(void)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_parent_process(t_info *info)
{
	(void)info;
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	echoctl_off();
}