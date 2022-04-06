/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 12:10:03 by deulee            #+#    #+#             */
/*   Updated: 2022/04/07 02:16:23 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_buff
{
	int				fd;
	unsigned int	buff_size;
	char			buffer[BUFFER_SIZE];
	char			*backup;
	struct s_buff	*next;
}					t_buff;

int					get_next_line(int fd, char **line);
int					find_next_line(char **line, t_buff *list);
int					make_line(char **line, t_buff *list);
int					make_backup(char *backupline, t_buff *list,
						unsigned int nsize);
int					backup_update(t_buff *list, unsigned int len);
void				clear_fd(t_buff **header);
void				del_fd(int fd, t_buff **header);
t_buff				*find_fd_or_make(int fd, t_buff **header);

#endif
