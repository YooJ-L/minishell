/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoojlee <yoojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:49:08 by yoojlee           #+#    #+#             */
/*   Updated: 2022/03/14 18:57:52 by yoojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int                ft_isexecutable(char *file)
{
    struct stat    test;

    if (stat(file, &test) != -1)
        return (1);
    else
        return (0);
}