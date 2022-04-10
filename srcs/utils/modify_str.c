/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:07:35 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/10 16:58:27 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

void	add_char_to_str(char **str, char character)
{
	int		str_size;
	char	*new_str;

	str_size = ft_strlen(*str);
	new_str = (char *)malloc(sizeof(char) * (str_size + 2));
	if (!new_str)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	if (*str)
	{
		ft_strlcpy(new_str, *str, str_size + 1);
		free(*str);
	}
	new_str[str_size] = character;
	new_str[str_size + 1] = '\0';
	*str = new_str;
}

void	save_str(char **save, char *input)
{
	char	*temp;

	if (ft_strlen(*save) > 0)
		add_char_to_str(save, '\n');
	temp = *save;
	*save = ft_strjoin(*save, input);
	free(temp);
}
