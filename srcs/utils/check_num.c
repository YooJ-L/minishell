/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dim <dim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:05:40 by dim               #+#    #+#             */
/*   Updated: 2022/03/27 01:16:50 by dim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structure.h"

int	str_is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != 0)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	str_is_long(char *str)
{
	int		i;
	int		len;
	int		minus;

	i = 0;
	len = 0;
	minus = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = 1;
		i++;
	}
	len = ft_strlen(str + i);
	if ((ft_strncmp("9223372036854775808", str + i, len) > 0) \
	|| (ft_strncmp("9223372036854775808", str + i, len) == 0 \
	&& minus == 1))
		return (0);
	else
		return (1);
}