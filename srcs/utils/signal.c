/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:35:06 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/07 14:09:08 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	sig_exit_handler(int sig) //자식이 죽었을 때
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
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	set_parent_process(t_info *info)
{
	(void)info;
	signal(SIGINT, (void *)sigint_handler); //원래 sigint는 실행 중지인데, 이걸 sigint_handler라는 함수를 줘서 하는 행동을 바꿈.
	signal(SIGQUIT, SIG_IGN); //SIG_IGN : 신호 무시
	set_input_mode();
}