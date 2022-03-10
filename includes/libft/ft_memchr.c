/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:52:53 by deulee            #+#    #+#             */
/*   Updated: 2021/08/11 16:55:54 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t n)
{
	unsigned char	*s_tmp;

	s_tmp = (unsigned char *)b;
	while (n--)
	{
		if (*s_tmp == (unsigned char)c)
			return ((void *)s_tmp);
		s_tmp++;
	}
	return (0);
}
