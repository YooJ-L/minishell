/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:13:30 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/14 18:57:59 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void set_input_mode(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term); // STDIN으로부터 터미널 속성을 받아온다
	term.c_lflag &= ~(ICANON | ECHO);  // ICANON, ECHO 속성을 off
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // 변경된 속성의 터미널을 STDIN에 바로 적용
}

// 기존의 터미널 세팅으로 다시 변경
void reset_input_mode(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);  // STDIN에 기존의 터미널 속성을 바로 적용
}

void	change_input_mode(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag ^= (ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}