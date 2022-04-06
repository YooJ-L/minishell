/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:07:35 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/06 18:57:31 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

//heredoc.c 에서 \n 붙여줄 때 사용
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