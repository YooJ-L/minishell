/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 23:06:56 by deulee            #+#    #+#             */
/*   Updated: 2021/08/11 16:56:44 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str_sub;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s)
		return (0);
	if ((unsigned int)s_len < start)
		return (ft_strdup(""));
	str_sub = (char *)malloc(sizeof(char) * (len + 1));
	if (str_sub == NULL)
		return (0);
	ft_strlcpy(str_sub, s + start, len + 1);
	return (str_sub);
}
