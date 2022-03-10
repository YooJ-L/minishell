/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:24:51 by deulee            #+#    #+#             */
/*   Updated: 2021/08/11 16:58:46 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buff	*find_fd_or_make(int fd, t_buff **header)
{
	t_buff		*ltr;

	ltr = *header;
	while (ltr != NULL)
	{
		if (ltr->fd == fd)
			break ;
		ltr = ltr->next;
	}
	if (ltr != NULL)
		return (ltr);
	ltr = (t_buff *)malloc(sizeof(t_buff));
	if (ltr == NULL)
		return (NULL);
	ltr->fd = fd;
	ltr->backup = NULL;
	ltr->buff_size = 0;
	ltr->next = *header;
	*header = ltr;
	return (ltr);
}

int	backup_update(t_buff *list, unsigned int len)
{
	char				*new_backup;
	unsigned int		size;
	unsigned int		i;

	size = list->buff_size - len - 1;
	new_backup = NULL;
	if (size != 0)
	{
		new_backup = (char *)malloc(sizeof(char) * size);
		if (new_backup == NULL)
			return (0);
	}
	i = 0;
	while (++len < list->buff_size)
	{
		new_backup[i] = list->backup[len];
		i++;
	}
	free(list->backup);
	list->backup = new_backup;
	list->buff_size = size;
	return (1);
}

void	clear_fd(t_buff **header)
{
	t_buff		*ptr;
	t_buff		*temp;

	ptr = *header;
	while (ptr != NULL)
	{
		temp = ptr->next;
		free(ptr->backup);
		free(ptr);
		ptr = temp;
	}
	*header = NULL;
}

void	del_fd(int fd, t_buff **header)
{
	t_buff		*ptr;
	t_buff		*before;

	ptr = *header;
	before = *header;
	if (ptr->fd == fd)
	{
		*header = ptr->next;
		free(ptr->backup);
		free(ptr);
		return ;
	}
	while (ptr != NULL)
	{
		if (ptr->fd == fd)
		{
			before->next = ptr->next;
			free(ptr->backup);
			free(ptr);
			break ;
		}
		before = ptr;
		ptr = ptr->next;
	}
}
