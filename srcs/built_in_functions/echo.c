/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:38:17 by dim               #+#    #+#             */
/*   Updated: 2022/03/19 04:41:58 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	print_env(char *env)
{
	//env 찾아서 프린트
}

char 	*if_env(t_list *arg)
{
	// $ 있으면 환경변수 반환
	// "" 안의 환경변수는 o, ''안의 환경변수는 x
}

bool	verify_and_print_opt(t_list *option)
{
	//하나의 '-'와 하나 이상의 'n'의 조합이면 플래그 인정
	//---n | -nm 은 안됨
}

void	execute_echo(t_info *info, t_process *process)
{
	// 고려해야할것: $?, $, '$환경변수'는 환경변수로x, ;, | 
	bool flag;
	char *env;

	//option에 저장된게 -n 플래그 맞나 확인
	flag = verify_and_print_opt(process->option);
	env = if_env();
	if (env != NULL)
		print_env(env);
	else
		ft_putstr_fd((char *)process->arg->content, /*fd값*/);
	if (flag)
		ft_putstr_fd("\n", /*fd값*/);
}