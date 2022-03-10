/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 14:57:14 by deulee            #+#    #+#             */
/*   Updated: 2020/12/29 23:00:02 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*fin;

	if (!(lst) || !(new))
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	fin = ft_lstlast(*lst);
	new->next = fin->next;
	fin->next = new;
}
