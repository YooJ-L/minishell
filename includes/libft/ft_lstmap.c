/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 23:34:38 by deulee            #+#    #+#             */
/*   Updated: 2021/08/11 16:38:45 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*output;
	t_list	*tmp;

	if (lst == 0 || f == 0)
		return (0);
	output = NULL;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (tmp != 0)
		{
			ft_lstadd_back(&output, tmp);
			tmp = tmp->next;
			lst = lst->next;
			continue ;
		}
		ft_lstclear(&output, del);
		return (NULL);
	}
	return (output);
}
