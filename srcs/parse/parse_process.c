/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:55:31 by dim               #+#    #+#             */
/*   Updated: 2022/04/03 03:58:06 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	add_char_to_str(char **str, char ch)
{
	int		strlen;
	char	*new_str;

	strlen = ft_strlen(*str);
	new_str = (char *)malloc(sizeof(char) * (strlen + 2));
	if (new_str == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	if (*str)
	{
		ft_strlcpy(new_str, *str, strlen + 1);
		free(*str);
	}
	new_str[strlen] = ch;
	new_str[strlen + 1] = '\0';
	*str = new_str;
}

char	*find_key_in_str(const char *str)
{
	int		i;
	char	*ret;

	i = 0;
	if (str[0] == '?')
	{
		ret = (char *)malloc(sizeof(char) * 2);
		if (ret == NULL)
			perror_and_exit("cannot allocate memory\n", ENOMEM);
		ret = "?\0";
		return (ret);
	}
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i == 0)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	ft_strlcpy(ret, str, i + 1);
	return (ret);
}

void	add_env_value(t_info *info, const char *key, \
											char **str, int status)
{
	char	*value;

	if (key == NULL)
	{
		add_char_to_str(str, '$');
		return ;
	}
	if (*key == '?')
	{
		add_last_exit_status()//추가해야됨
		return ;
	}
	value = get_env_value(info->env, key);
	if (value == NULL)
		return ;
	// quote가 있는 경우는 어떤경우..?
	if (status == NO_Q)
		add_char_to_str(str, '\"');
	while (*value)
	{
		add_char_to_str(str, *value);
		value++;
	}
	if (status == NO_Q)
		add_char_to_str(str, '\"');
}

char 	*replace_env_to_value(t_info *info, const char *line, int len)
{
	int		i;
	int		status;
	char	*key;
	char	*ret;

	i = 0;
	status = NO_Q;
	ret = NULL;
	while (i < len)
	{
		check_quote(line[i], &status);
		// 현재 문자가 $가 아닌 문자이거나 ' 안에 있는 $문자인 경우 문자열에 추가
		if (line[i] != '$' || status == SINGLE_Q)
			add_char_to_str(&ret, line[i++]);//i++됨
		// $인데 뒤에 '나 "가 옴($빼고 quote 안에 있는 문자 출력)
		else if (line[i + 1] == '\'' || line[i + 1] == '\"')
			i++;
		// $인 문자인데 바로 뒤에 '나 "가 없음
		else
		{
			key = find_key_in_str(&line[i + 1]);
			add_env_value(info, key, &ret, status);
			i += ft_strlen(key) + 1;
			free(key);
		}
	}
	return (ret);
}

int		skip_space(char *str)
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
	i = skip_space(new_line);
	while (i >= 0 && new_str[i])
	{
		cur_token = get_one_token(&new_str[i]);
		i += ft_strlen(cur_token);
		//check_token();
		//save_token();
	}
	free(new_str);
	if (i == -1)
		return (1);
	return (0);
}