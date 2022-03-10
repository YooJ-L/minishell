/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:12:55 by deulee            #+#    #+#             */
/*   Updated: 2021/08/11 16:33:53 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

double	ft_atof(const char *num)
{
	double	real;
	double	sign;
	double	decimal;

	sign = 1.0f;
	real = 0.0f;
	decimal = 0.1f;
	while (is_space(*num))
		num++;
	if (*num == '+' || *num == '-')
		if (*num++ == '-')
			sign = -1.0f;
	while (ft_isdigit(*num))
	{
		real = real * 10 + (double)(*num - '0');
		num++;
	}
	if (*num++ != '.')
		return (real * sign);
	while (ft_isdigit(*num))
	{
		real = real + (decimal * (double)(*num++ - '0'));
		decimal *= 0.1;
	}
	return (real * sign);
}
