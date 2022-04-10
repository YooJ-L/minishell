/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:21:52 by dim               #+#    #+#             */
/*   Updated: 2022/04/10 13:19:32 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	merge_arg(char **dest_arg, t_process *process)
{
	int		i;
	t_list	*option;
	t_list	*arg;

	i = 1;
	option = process->option;
	arg = process->arg;
	while (option)
	{
		dest_arg[i] = option->content;
		i++;
		option = option->next;
	}
	while (arg)
	{
		dest_arg[i] = arg->content;
		i++;
		arg = arg->next;
	}
}

char	**get_arg(t_process *process)
{
	char	**arg;
	int		size;

	size = 0;
	size = 1 + ft_lstsize(process->option) + ft_lstsize(process->arg);
	arg = (char **)malloc(sizeof(char *) * (size + 1));
	if (arg == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	ft_bzero(arg, sizeof(char *) * (size + 1));
	merge_arg(arg, process);
	arg[0] = process->instruction;
	return (arg);
}
