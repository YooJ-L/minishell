/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 16:25:37 by deulee            #+#    #+#             */
/*   Updated: 2021/08/11 16:57:08 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_t;
	unsigned char	*s2_t;

	i = 0;
	s1_t = (unsigned char *)s1;
	s2_t = (unsigned char *)s2;
	while (i < n)
	{
		if (s1_t[i] != s2_t[i] || !(s1_t[i]) || !(s2_t[i]))
			return (s1_t[i] - s2_t[i]);
		i++;
	}
	return (0);
}
