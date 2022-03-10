/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:39:38 by deulee            #+#    #+#             */
/*   Updated: 2020/12/26 16:47:51 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	last;
	size_t	i;
	int		check;

	check = 0;
	i = 0;
	last = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			last = i;
			check = 1;
		}
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	if (check == 1)
		return ((char *)s + last);
	return (0);
}
