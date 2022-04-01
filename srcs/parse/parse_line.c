/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:55:31 by dim               #+#    #+#             */
/*   Updated: 2022/04/02 03:57:48 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char 	*replace_env_value(t_info *info, const char *line, int len)
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
			add_char_to_str();
		else if (line[i + 1] == '\'' || line[i + 1] == '\"')
			i++;
		else
		{
			//?????
			key = find_key_in_line(&line[i + 1]);
			
		}
	}

}

int		parse_line(t_process *process, t_info *info, const char *line, int len)
{
	int		i;
	int		tag;
	char	*new_line;
	char	*cur_token;

	cur_token = NULL;
	tag = 0;
	new_line = replace_env_value(info, line, len);
}