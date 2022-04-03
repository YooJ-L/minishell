/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:55:31 by dim               #+#    #+#             */
/*   Updated: 2022/04/03 21:23:03 by dim              ###   ########.fr       */
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

char	*redirection_token(const char *str)
{
	int		cnt;
	char	*ret;

	cnt = 0;
	while (str[0] == str[cnt] && cnt < 2)
		cnt++;
	// >일때는..? cnt가 0이라 빈문자열만 저장..?
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
	// quote가 짝이 안맞았는데 빈문자열을 만나는 조건에 걸림
	if (status != NO_Q)
	{
		// cnt는 1로 초기화 후에 다시 1번 문자열부터 검사
		// ?????
		cnt = 1;
		// space이거나 빈문자열이 올때까지 카운트
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

int		classify_token(t_process *process, const char *token, int tag)
{
	int		i;

	if (token[0] == '<' || token[0] == '>')
	{
		if (tag == REDIRECTION)
		{
			perror_in_parsing((char *)token);
			return (258);
		}
		else
			return (REDIRECTION);
	}
	if (tag == REDIRECTION)
		return (FILENAME);
	if (process->instruction == NULL)
		return (INSTRUCTION);
	if (token[0] == '-' && process->arg)
	{
		i = 1;
		while (token[i] == '\"' || token[i] == '\'')
			i++;
		if (ft_isalpha(token[i]))
			return (OPTION);
	}
	return (ARG);
}

void	remove_outside_quotes_in_str(char **str)
{
	int		cnt;
	int		status;
	char	*new_str;

	cnt = 0;
	status = NO_Q;
	new_str = NULL;
	while ((*str)[i])
	{
		if (check_quote((*str)[cnt], &status))
		{
			cnt++;
			continue ;
		}
		add_char_to_str(&new_str, (*str)[cnt]);
		cnt++;
	}
	free(*str);
	*str = new_str;
}

int		check_token(t_porcess *process, char **new_str, char **cur_token, int *tag)
{
	*tag = classify_token(process, *cur_token, *tag);
	if (*tag == 258)
	{
		free(*cur_token);
		free(*new_str);
		return (258);
	}
	remove_outside_quotes_in_str(cur_token);
	return (0);
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
		cur_token = get_one_token(&new_line[i]);
		i += ft_strlen(cur_token);
		if (check_token(process, &new_line, &cur_token, &tag));
			return (258);
		//save_token();
	}
	free(new_str);
	if (i == -1)
		return (1);
	return (0);
}