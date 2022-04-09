/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:13:30 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/08 16:06:42 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

/*
터미널 함수가 뭐냐면 Ctrl+c눌렀을 때 ^c 이거 안뜨게 하는건데,
부모에서는 안떠야 하고
자식 프로세스에서는 떠야 하니까 
껐다 켰다 하는 것.

Set_input_mode는 set_parent_process할 때만 불러지는데,
set_parent_process는
1. fork_heredoc_process 에서 마지막에
2. run하자마자 바로. 무한반복문 계속 돌면서 제일 먼저 해줌.

reset_input_mode는 
1. loop_minishell에서 execute하기 전에 
2. fork_processes 하기 전에
3. quit_handler에서 (validate_output에 null들어온 경우)
*/

void	echoctl_off(void)
{
	struct termios	term;

//tcgetattr: 터미널의 속성을 받아와서 term에 저장
	tcgetattr(STDIN_FILENO, &term); // STDIN으로부터 터미널 속성을 받아온다
	term.c_lflag &= ~(ECHOCTL);  // ICANON, ECHO 속성을 off
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // 변경된 속성의 터미널을 STDIN에 바로 적용
}

// void	set_input_mode(struct termios *new_term)
// {
// 	tcgetattr(STDOUT_FILENO, new_term);
// 	new_term->c_lflag &= ~(ECHOCTL);
// 	tcsetattr(STDOUT_FILENO, TCSANOW, new_term);
// }


// 기존의 터미널 세팅으로 다시 변경
void	echoctl_on(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);  // STDIN에 기존의 터미널 속성을 바로 적용
}

// void	reset_input_mode(struct termios *org_term)
// {
// 	tcgetattr(STDOUT_FILENO, org_term);
// 	org_term->c_lflag |= (ECHOCTL);
// 	tcsetattr(STDOUT_FILENO, TCSANOW, org_term);
// }

// void	change_input_mode(void)
// {
// 	struct termios	term;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag ^= (ECHO);
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }