/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:55:31 by dim               #+#    #+#             */
/*   Updated: 2022/04/04 17:33:38 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int		skip_front_space(char *str)
{
	int	cnt;

	cnt = 0;
	if (str == NULL)
		return (-1);
	while (str[cnt] == ' ' || str[cnt] == '\t')
		cnt++;
	if (str[cnt] == '\0')
		return (-1);
	else
		return (cnt);
}

char	*redirection_token(const char *str)
{
	int		cnt;
	char	*ret;

	cnt = 0;
	while (str[0] == str[cnt] && cnt < 2)
		cnt++;
	ret = (char *)malloc(sizeof(char) * (cnt + 1));
	if (ret == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	ft_strlcpy(ret, str, cnt + 1);
	return (ret);
}

char	*other_token(const char *str)
{
	// 결론은 space 단위로 토큰을 내는것
	int		cnt;
	int		status;
	char	*ret;

	cnt = 0;
	stauts = 0;
	// space나 빈문자열, 리다이렉션이 아닌 문자이거나 quote 안에 있는 빈문자열이 아닌 문자들을 체크하고 카운트함
	while ((str[cnt] != ' ' && str[cnt] != '\0' \
			&& str[cnt] != '<' && str[cnt] != '>') \
			|| (status != NO_Q && str[cnt] != '\0'))
	{
		check_quote(str[cnt], &status);
		cnt++;
	}
	// quote가 짝이 안맞았는데 빈문자열을 만나는 조건에 걸리는 경우 다시 세줌
	// 위 while문에선 앞에 quote가 있으면 띄어쓰기도 다 저장하지만
	// quote가 짝이 안맞는 경우엔 띄어쓰기나 빈문자열 전까지만 밑에서 다시 카운트해줌
	if (status != NO_Q)
	{
		// cnt는 1로 초기화 후에 다시 1번 문자열부터 검사
		// ?????
		cnt = 0;
		while (str[cnt] != ' ' && str[cnt] != '\0')
			cnt++;
	}
	ret = (char *)malloc(sizeof(char) * (cnt + 1));
	if (ret == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	ft_strlcpy(ret, str, cnt + 1);
	return (ret);
}

char	*get_one_token(const char *str)
{
	if (str[0] == '<' || str[0] == '>')
		return (redirection_token(str));
	else
		return (other_token(str));
}

int		parse_process(t_process *process, t_info *info, const char *line, int len)
{
	// 파이프단위로 프로세스 파싱
	int		i;
	int		tag;
	char	*new_line;
	char	*cur_token;

	cur_token = NULL;
	tag = 0;
	new_line = replace_env_to_value(info, line, len);
	i = skip_front_space(new_line);
	while (i >= 0 && new_str[i])
	{
		cur_token = get_one_token(&new_line[i]);
		i += ft_strlen(cur_token);
		if (check_token(process, &new_line, &cur_token, &tag));
			return (258);
		save_token(process, cur_token, tag);
		while (new_str[i] == ' ')
			i++;
	}
	free(new_str);
	if (i == -1)
		return (1);
	return (0);
}