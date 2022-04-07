/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 03:46:09 by dim               #+#    #+#             */
/*   Updated: 2022/04/07 14:53:46 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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
		check_quote(line[i], &status);
		if (status == NO_Q && line[i] == '|')
			cnt++;
		i++;
	}
	if (status != 0)
	{
		perror_in_parsing("newline");
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
		check_quote(line[cnt], &status);
		if (line[cnt] == '|' && status == NO_Q)
			return (cnt);
		cnt++;
	}
	return (cnt);
}

t_process	*parse_split_error(int ret, t_info *info)
{
	if (ret != 258 && info->process_cnt != 1)
		perror_in_parsing("|");
	return (NULL);
}

void		init_process(t_process *process, int process_cnt)
{
	int	i;

	i = 0;
	while (i < process_cnt)
	{
		process[i].heredoc = false;
		// process.->pid = //???
		process[i].instruction = NULL;
		process[i].option = NULL;
		process[i].arg = NULL;
		process[i].redirect = NULL;
		process[i].input_file = NULL;
		process[i].heredoc_str = NULL;
		i++;
	}
}

t_process	*split_line(const char *line, t_info *info)
{
	// 라인을 파이프마다 나누어서 프로세스 개수만큼 리스트로 할당한 후 각 프로세스 정보 채워서 반환
	t_process	*process;
	int			ps_cnt;
	int			len;
	int			ret;

	info->process_cnt = get_pipe_cnt(line) + 1;
	if (!info->process_cnt)
		return (NULL);
	process = (t_process *)malloc(sizeof(t_process) * info->process_cnt);
	if (process == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	init_process(process, info->process_cnt);
	ps_cnt = info->process_cnt;
	//문제있을경우 cnt 확인해보기!
	while (ps_cnt--)
	{
		// 파이프 단위로 나눈 후 파싱
		len = strlen_each_process(line);
		ret = parse_process(process, info, line, len);
		if (ret)
			return (parse_split_error(ret, info));
		line += len + 1;
	}
	return (process);
}