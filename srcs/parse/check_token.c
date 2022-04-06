/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 04:08:32 by dim               #+#    #+#             */
/*   Updated: 2022/04/06 18:58:12 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../inlcudes/structure.h"

void	remove_outside_quotes_in_str(char **str)
{
	// quote 제거하고 문자들만 저장
	int		cnt;
	int		status;
	char	*new_str;

	cnt = 0;
	status = NO_Q;
	new_str = NULL;
	while ((*str)[cnt])
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
	if (token[0] == '-' && process->arg == NULL)
	{
		i = 1;
		while (token[i] == '\"' || token[i] == '\'')
			i++;
		if (ft_isalpha(token[i]))
			return (OPTION);
	}
	return (ARG);
}

int		check_token(t_porcess *process, char **new_str, char **token, int *tag)
{
	*tag = classify_token(process, *token, *tag);
	if (*tag == 258)
	{
		free(*token);
		free(*new_str);
		return (258);
	}
	remove_outside_quotes_in_str(token);
	return (0);
}