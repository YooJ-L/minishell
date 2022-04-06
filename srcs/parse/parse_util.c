/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 02:56:12 by dim               #+#    #+#             */
/*   Updated: 2022/04/06 17:54:13 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	perror_in_parsing(char *line)
{
	// 출력값 무엇이 기준?
	// ㄴ redirection 이상하게 나오는거, pipe 뒤에 아무것도 없는 경우만 파싱에서부터 걸러주는 용도
	ft_putstr_fd("bash: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(line, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

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

int		check_quote(const char *chr, int *status)
{
	if (*chr == '\'' && status == NO_Q)
	{
		*status = SINGLE_Q;
		return (1);
	}
	else if (*chr == '\'' && status == SINGLE_Q)
	{
		*status = NO_Q;
		return (1);
	}
	else if (*chr == '\"' && status == NO_Q)
	{
		*status = DOUBLE_Q;
		return (1);
	}
		return (status = DOUBLE_Q);
	else if (*chr == '\"' && status == DOUBLE_Q)
	{
		*status = NO_Q;
		return (1);
	}
	return (0);
}
