/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:17:39 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/26 20:42:28 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "../../includes/structure.h"

void	make_error(void)
{
	printf("make error\n");
	exit(-1);
}

void	perror_and_exit(char *text, int	errnum)
{
	ft_putstr_fd(text, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(errnum);
}