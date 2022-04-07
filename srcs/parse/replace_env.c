/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 02:51:38 by dim               #+#    #+#             */
/*   Updated: 2022/04/07 14:54:18 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h" //add_char_to_str함수 쓰려고

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

void	add_last_exit_status(char **str, int last_exit_status)
{
	int		i;
	char	*num;

	num = ft_itoa(last_exit_status);
	if (!num)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	i = 0;
	while (num[i])
	{
		add_char_to_str(str, num[i]);
		i++;
	}
	free(num);
}

void	add_env_value(t_info *info, char *key, \
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
		add_last_exit_status(str, info->last_exit_status);
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