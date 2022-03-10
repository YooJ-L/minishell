/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 15:02:44 by deulee            #+#    #+#             */
/*   Updated: 2020/12/23 16:27:44 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;

	if (n == 0 || dest == src)
		return (dest);
	if (dest < src)
	{
		dst_tmp = (unsigned char *)dest;
		src_tmp = (unsigned char *)src;
		while (n--)
			*dst_tmp++ = *src_tmp++;
	}
	else
	{
		dst_tmp = (unsigned char *)dest;
		src_tmp = (unsigned char *)src;
		dst_tmp += (n - 1);
		src_tmp += (n - 1);
		while (n--)
			*dst_tmp-- = *src_tmp--;
	}
	return (dest);
}
