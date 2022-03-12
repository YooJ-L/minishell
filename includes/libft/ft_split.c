/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 15:18:54 by deulee            #+#    #+#             */
/*   Updated: 2022/03/12 21:24:27 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_memerror(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}

size_t	ft_tmemerror(char *s_tmp)
{
	free(s_tmp);
	return (0);
}

size_t	ft_cal_size(const char *s, char c)
{
	size_t	size;
	size_t	i;
	char	*s_tmp;
	char	set[2];

	set[0] = c;
	set[1] = '\0';
	size = 1;
	i = 0;
	s_tmp = ft_strtrim(s, set);
	if (s_tmp == 0 || s_tmp[i] == '\0')
		return (ft_tmemerror(s_tmp));
	while (s_tmp[i])
	{
		if (c == s_tmp[i])
		{
			while (s_tmp[i] && c == s_tmp[i])
				i++;
			size++;
		}
		i++;
	}
	free(s_tmp);
	return (size);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	k;
	size_t	len;

	i = 0;
	k = 0;
	arr = (char **)malloc(sizeof(char *) * (ft_cal_size(s, c) + 1));
	while (s[i] && k < ft_cal_size(s, c))
	{
		len = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c)
		{
			len++;
			i++;
		}
		arr[k] = (char *)malloc(sizeof(char) * len + 1);
		if (arr[k] == NULL)
			return (ft_memerror(arr));
		ft_strlcpy(arr[k++], &s[i - len], len + 1);
	}
	arr[k] = 0;
	return (arr);
}
