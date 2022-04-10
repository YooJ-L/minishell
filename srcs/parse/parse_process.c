/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:55:31 by dim               #+#    #+#             */
/*   Updated: 2022/04/10 18:02:52 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	skip_front_space(char *str)
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
	int		cnt;
	int		status;
	char	*ret;

	cnt = 0;
	status = 0;
	while ((str[cnt] != ' ' && str[cnt] != '\0' \
			&& str[cnt] != '<' && str[cnt] != '>') \
			|| (status != NO_Q && str[cnt] != '\0'))
	{
		check_quote(str[cnt], &status);
		cnt++;
	}
	if (status != NO_Q)
	{
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

int	parse_process(t_process *process, t_info *info, const char *line, int len)
{
	int		i;
	int		tag;
	char	*new_line;
	char	*cur_token;

	cur_token = NULL;
	tag = 0;
	new_line = replace_env_to_value(info, line, len);
	i = skip_front_space(new_line);
	while (i >= 0 && new_line[i])
	{
		cur_token = get_one_token(&new_line[i]);
		i += ft_strlen(cur_token);
		if (check_token(process, &new_line, &cur_token, &tag))
			return (258);
		save_token(process, cur_token, tag);
		while (new_line[i] == ' ')
			i++;
	}
	free(new_line);
	if (i == -1)
		return (1);
	return (0);
}
