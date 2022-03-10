/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 12:08:56 by deulee            #+#    #+#             */
/*   Updated: 2021/08/11 17:11:28 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static t_buff		*saving = NULL;
	t_buff				*list;
	int					flag;

	if (BUFFER_SIZE < 1 || line == NULL)
		return (-1);
	list = find_fd_or_make(fd, &saving);
	if (list == NULL)
	{
		clear_fd(&saving);
		return (-1);
	}
	*line = NULL;
	flag = find_next_line(line, list);
	if (flag == 0)
		del_fd(fd, &saving);
	else if (flag == -1)
	{
		clear_fd(&saving);
		free(*line);
	}
	return (flag);
}

int	find_next_line(char **line, t_buff *list)
{
	int		readsize;
	int		flag;

	flag = make_line(line, list);
	if (flag == -1 || flag == 1)
		return (flag);
	readsize = read(list->fd, list->buffer, BUFFER_SIZE);
	while (readsize > 0)
	{
		if (!(make_backup(list->buffer, list, readsize)))
			return (-1);
		flag = make_line(line, list);
		if (flag == -1 || flag == 1)
			return (flag);
		readsize = read(list->fd, list->buffer, BUFFER_SIZE);
	}
	if (readsize == -1)
		return (-1);
	*line = ft_strndup(list->backup, list->buff_size);
	if (*line == NULL)
		return (-1);
	return (0);
}

int	make_line(char **line, t_buff *list)
{
	unsigned int	len;

	if (list->buff_size == 0)
		return (0);
	len = 0;
	while (len < list->buff_size)
	{
		if (list->backup[len] == '\n')
		{
			*line = ft_strndup(list->backup, len);
			if (*line == NULL)
				return (-1);
			if (!(backup_update(list, len)))
				return (-1);
			return (1);
		}
		len++;
	}
	return (0);
}

int	make_backup(char *backupline, t_buff *list, unsigned int nsize)
{
	char			*backup;
	unsigned int	size;
	unsigned int	i;
	unsigned int	j;

	size = list->buff_size + nsize;
	backup = (char *)malloc(sizeof(char) * size);
	i = 0;
	while (i < list->buff_size)
	{
		backup[i] = list->backup[i];
		i++;
	}
	j = 0;
	while (j < nsize)
	{
		backup[i] = backupline[j];
		i++;
		j++;
	}
	free(list->backup);
	list->buff_size = size;
	list->backup = backup;
	return (1);
}

char	*ft_strndup(char *src, unsigned int size)
{
	char			*str;
	unsigned int	i;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
