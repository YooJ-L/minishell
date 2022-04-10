/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 02:51:38 by dim               #+#    #+#             */
/*   Updated: 2022/04/10 16:56:12 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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
		ret[0] = '?';
		ret[1] = '\0';
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

char	*replace_env_to_value(t_info *info, const char *line, int len)
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
		if (line[i] != '$' || status == SINGLE_Q)
			add_char_to_str(&ret, line[i++]);
		else if (line[i + 1] == '\'' || line[i + 1] == '\"')
			i++;
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
