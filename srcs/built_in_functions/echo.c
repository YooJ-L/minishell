/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:38:17 by dim               #+#    #+#             */
/*   Updated: 2022/04/10 15:46:45 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	print_echo(t_list *list, int flag)
{
	t_list	*temp;

	if (list == NULL)
		return ;
	temp = list;
	if ((flag == 2 || flag == 3) && temp != NULL)
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

int	verify_and_print_opt(t_list *opt_list)
{
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
			continue ;
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

int	execute_echo(t_info *info, t_process *process)
{
	int		flag;

	flag = 0;
	if (process->option != NULL)
		flag = verify_and_print_opt(process->option);
	print_echo(process->arg, flag);
	if (flag == 0 || flag == 2)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (exit_process(info, process, 0));
}
