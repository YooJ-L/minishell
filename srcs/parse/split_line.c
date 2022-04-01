/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 03:46:09 by dim               #+#    #+#             */
/*   Updated: 2022/04/02 03:47:48 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	perror_in_parsing(char *line)
{
	// 출력값 무엇이 기준?
	ft_putstr_fd(line, STDERR_FILENO);
}

int		check_quote(const char *chr, int *status)
{
	if (*chr == '\'' && status == NO_Q)
		return (status = SINGLE_Q);
	else if (*chr == '\'' && status == SINGLE_Q)
		return (status = NO_Q);
	else if (*chr == '"' && status == NO_Q)
		return (status = DOUBLE_Q);
	else if (*chr == '"' && status == DOUBLE_Q)
		return (status = NO_Q);
	return (0);
}

int		get_pipe_cnt(const char *line)
{
	int	i;
	int	status;
	int	cnt;

	i = 0;
	status = 0;
	cnt = 0;
	while (line[i])
	{
		status = check_quote(line[i], status);
		if (status == 0 && line[i] == '|')
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

int			strlen_each_process(const char *line)
{
	int		cnt;
	int		status;

	cnt = 0;
	status = 0;
	while (line[cnt])
	{
		check_quote(line[cnt], status);
		if (line[cnt] != '|' && status == NO_Q)
			return (cnt);
		cnt++;
	}
	return (cnt);
}

t_process	*split_line(const char *line, t_info *info)
{
	t_process	*process;
	int			ps_cnt;
	int			len;

	info->process_cnt = get_pipe_cnt(line) + 1;
	if (!info->process_cnt)
		return (NULL);
	process = (t_process *)malloc(sizeof(t_process) * info->process_cnt);
	if (process == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	ps_cnt = info->process_cnt;
	while (ps_cnt--)
	{
		len = strlen_each_process(line);
		if (!parse_line(process, info, line, len))
			parse_error();//error 함수 만들기
		line += len + 1;
	}
	return (process);
}