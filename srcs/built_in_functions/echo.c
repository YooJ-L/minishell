/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:38:17 by dim               #+#    #+#             */
/*   Updated: 2022/04/07 00:24:50 by dim              ###   ########.fr       */
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

void	print_echo(t_list *list, int flag)
{
	t_list *temp;

	if (list == NULL)
		return ;
	temp = list;
	if ((flag == 2 || flag == 3)&& temp != NULL)
		ft_putchar_fd(' ', STDOUT_FILENO);
	while (temp)
	{
		ft_putstr_fd(temp->content, STDOUT_FILENO);
		temp = temp->next;
		if (temp)
			ft_putchar_fd(' ', STDOUT_FILENO);
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

int		verify_and_print_opt(t_list *opt_list)
{
	//하나의 '-'와 하나 이상의 'n'의 조합이면 플래그 인정, -n -n -n 인정
	//---n | -nm 은 안됨
	// [ret 값] (arg 출력 전 스페이스 삽입때문에 필요)
	// 0: 옵션x 출력x, 1: 옵션o 출력x
	// 2: 옵션x출력o   3: 옵션o 출력o
	t_list	*temp;
	int		ret;

	temp = opt_list;
	ret = 0;
	while (temp)
	{
		if (check_opt((char *)temp->content))
		{
			ret = 1;
			temp = temp->next;
			continue;
		}
		else
		{
			if (ret == 1 || ret == 3)
				ret = 3;
			else
				ret = 2;
			print_echo(temp, 0);
			return (ret);
		}
	}
	return (ret);
}

int		execute_echo(t_info *info, t_process *process)
{
	// 고려해야할것: $?, $, '$환경변수'는 환경변수로x, ;, | 
	int		flag;
	char	*env;

	//option에 저장된게 -n 플래그 맞나 확인
	flag = 0;
	if (process->option != NULL)
		flag = verify_and_print_opt(process->option);
	// env를 파싱에서 가져오면 env확인부분 없애고 여기서 확인하는거면 살리기
	// env = verify_env(process->arg);
	// if (env != NULL)
	// 	print_env(env);
	// else
		print_echo(process->arg, flag);
	if (flag == 0 || flag == 2)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (exit_process(info, process, 0));
}