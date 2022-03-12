/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_in_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 21:07:33 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/12 21:35:53 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/structure.h"

char	**ft_split_in_two(char *str, char ch)
{
	int	i;
	char	**arr;
	char	*temp;

	i = -1;
	arr = (char **)malloc(sizeof(char *) * 2);
	if (arr == NULL)
		return (0);
	while (str[++i])
	{
		if (str[i] == ch)
		{
			arr[0] = ft_strndup(str, i + 1);
			arr[1] = ft_strdup(str + i + 1);
		}
	}
	return (arr);
}