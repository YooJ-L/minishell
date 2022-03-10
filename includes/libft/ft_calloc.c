/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 19:43:30 by deulee            #+#    #+#             */
/*   Updated: 2021/08/11 16:29:41 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memarr;

	memarr = malloc(nmemb * size);
	if (memarr == NULL)
		return (0);
	ft_bzero(memarr, (nmemb * size));
	return (memarr);
}
