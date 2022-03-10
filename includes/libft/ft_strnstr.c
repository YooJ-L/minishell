/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 16:59:13 by deulee            #+#    #+#             */
/*   Updated: 2020/12/30 02:50:24 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	full_len;

	if (!(*little))
		return ((char *)big);
	if (ft_strlen(big) < ft_strlen(little) || len < ft_strlen(little))
		return (0);
	if (ft_strlen(big) > len)
		full_len = len;
	else
		full_len = ft_strlen(big);
	while (full_len-- >= ft_strlen(little))
	{
		if (ft_memcmp(big, little, ft_strlen(little)) == 0)
			return ((char *)big);
		big++;
	}
	return (0);
}
