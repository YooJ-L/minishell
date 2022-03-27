/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 03:46:09 by dim               #+#    #+#             */
/*   Updated: 2022/03/28 04:01:42 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	perror_in_parsing(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
}

int		get_pipe_cnt(char *str)
{
	int	i;
	int	status;
	int	cnt;

	i = 0;
	status = 0;
	cnt = 0;
	while (str[i])
	{
		status = check_quote(str[i], status);
		if (status == 0 && str[i] == '|')
			cnt++;
		i++;
	}
	if (status != 0)
	{
		perror_in_parsing("@@@@@@");
		return (-1);
	}
	return (cnt);
}

t_process	*split_line(const char *str, t_info *info)
{
	t_process *process;

	info->process_cnt = get_pipe_cnt(str) + 1;
	if (!info->process_cnt)
		return (NULL);
	process = (t_process *)malloc(sizeof(t_process) * info->process_cnt);
	if (process == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
}