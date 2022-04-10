/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:35:06 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 14:32:13 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

/*
ctrl+d 는 시그널로 처리하는 게 아니라 Readline에 eof가 들어오는 것.
ctrl+c를 누르면 새로운 프롬프트가 떠야 함.
ctrl+\를 누르면 아무일도 일어나지 않아야 함.

SIGINT : ctrl+c 입력 시 보내지는 인터럽트 시그널로, 실행을 중지.
SIGQUIT : ctrl+\ 입력 시 보내지는 실행 중지 시그널, 프로세스 종료하고 코어 덤프 함.
코어 덤프란? 비정상적으로 종료됐을 때 특정 시점에 작업중이던 메모리 상태를 기록.
*/

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
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_parent_process(t_info *info)
{
	(void)info;
	signal(SIGINT, (void *)sigint_handler); //원래 sigint는 실행 중지인데, 이걸 sigint_handler라는 함수를 줘서 하는 행동을 바꿈.
	signal(SIGQUIT, SIG_IGN); //SIG_IGN : 신호 무시
	echoctl_off();
}
