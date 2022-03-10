/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 12:16:30 by deulee            #+#    #+#             */
/*   Updated: 2020/12/30 02:40:03 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;
	size_t			i;

	i = 0;
	dst_tmp = (unsigned char *)dest;
	src_tmp = (unsigned char *)src;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		*dst_tmp++ = *src_tmp++;
		i++;
	}
	return (dest);
}
