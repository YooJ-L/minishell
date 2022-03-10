/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:43:13 by deulee            #+#    #+#             */
/*   Updated: 2021/08/11 16:28:57 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t n)
{
	size_t			i;
	unsigned char	*b1_t;
	unsigned char	*b2_t;

	i = 0;
	b1_t = (unsigned char *)b1;
	b2_t = (unsigned char *)b2;
	while (i < n)
	{
		if (b1_t[i] != b2_t[i])
			return (b1_t[i] - b2_t[i]);
		i++;
	}
	return (0);
}
