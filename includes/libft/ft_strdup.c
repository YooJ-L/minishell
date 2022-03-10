/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 22:10:11 by deulee            #+#    #+#             */
/*   Updated: 2021/08/11 16:25:22 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		str_len;
	char	*str_tmp;

	i = 0;
	str_len = ft_strlen(str);
	str_tmp = (char *)malloc(sizeof(char) * (str_len + 1));
	if (str_tmp == NULL)
		return (0);
	while (str[i])
	{
		str_tmp[i] = str[i];
		i++;
	}
	str_tmp[i] = '\0';
	return (str_tmp);
}
