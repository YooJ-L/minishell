/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:38:17 by dim               #+#    #+#             */
/*   Updated: 2022/03/21 00:33:05 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

// void	print_env(char *env)
// {
// 	//env 찾아서 프린트
// }

// char 	*verify_env(t_list *arg)
// {
// 	// $ 있으면 환경변수 반환
// 	// "" 안의 환경변수는 o, ''안의 환경변수는 x
	
// }

void	print_echo(t_list *list)
{
	t_list *temp;

	temp = list;
	while (temp)
	{
		ft_putstr_fd(temp->content, /*fd*/STDOUT_FILENO);
		temp = temp->next;
		if (temp)
			ft_putchar_fd(' ', /*fd*/STDOUT_FILENO);
	}
}

bool	check_opt(char *str)
{
	int	i;

	i = 1;
	while (str[i] != 0)
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

bool	verify_and_print_opt(t_list *opt_list)
{
	//하나의 '-'와 하나 이상의 'n'의 조합이면 플래그 인정, -n -n -n 인정
	//---n | -nm 은 안됨
	t_list	*temp;
	bool	opt;

	temp = opt_list;
	opt = false;
	while (temp)
	{
		if (check_opt((char *)temp->content))
		{
			opt = true;
			temp = temp->next;
			continue;
		}
		else
		{
			print_echo(temp);
			return (opt);
		}
	}
	return (opt);
}

void	execute_echo(t_info *info, t_process *process)
{
	// 고려해야할것: $?, $, '$환경변수'는 환경변수로x, ;, | 
	bool	flag;
	char	*env;

	//option에 저장된게 -n 플래그 맞나 확인
	flag = verify_and_print_opt(process->option);
	// env를 파싱에서 가져오면 env확인부분 없애고 여기서 확인하는거면 살리기
	// env = verify_env(process->arg);
	// if (env != NULL)
	// 	print_env(env);
	// else
		print_echo(process->arg);
	if (!flag)
		ft_putstr_fd("\n", /*fd값*/STDOUT_FILENO);
}