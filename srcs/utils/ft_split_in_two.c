/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_in_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 21:07:33 by yoojlee           #+#    #+#             */
/*   Updated: 2022/04/06 22:37:53 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

char	**ft_split_in_two(char *str, char ch)
{
	int	i;
	char	**arr;
	char	*temp;

	i = -1;
	arr = (char **)malloc(sizeof(char *) * 2);
	if (arr == NULL)
		perror_and_exit("cannot allocate memory\n", ENOMEM);
	while (str[++i])
	{
		if (str[i] == ch)
		{
			arr[0] = ft_strndup(str, i);
			arr[1] = ft_strdup(str + i + 1);
		}
	}
	return (arr);
}