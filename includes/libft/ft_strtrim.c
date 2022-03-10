/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 15:02:58 by deulee            #+#    #+#             */
/*   Updated: 2021/08/11 16:56:27 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_find_start(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (ft_strchr(set, s1[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

size_t	ft_find_fin(const char *s1, const char *set)
{
	size_t	i;
	size_t	s1_len;

	i = 0;
	s1_len = ft_strlen(s1);
	while (s1[i])
	{
		if (ft_strchr(set, s1[s1_len - i - 1]) == 0)
			return (s1_len - i - 1);
		i++;
	}
	return (s1_len - i - 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	fin;

	if (!(s1))
		return (0);
	if (!(set))
		return (ft_strdup(s1));
	start = ft_find_start(s1, set);
	fin = ft_find_fin(s1, set);
	if ((long int)start > (long int)fin)
	{
		return (ft_strdup(""));
	}
	str = (char *)malloc(sizeof(char) * (fin - start + 2));
	if (str == NULL)
		return (0);
	ft_strlcpy(str, s1 + start, fin - start + 2);
	return (str);
}
