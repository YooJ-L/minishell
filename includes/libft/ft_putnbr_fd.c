/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deulee <deulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 21:25:36 by deulee            #+#    #+#             */
/*   Updated: 2020/12/25 21:54:52 by deulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_recursive(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putnbr_recursive(n / 10, fd);
		write(fd, &("0123456789"[-(n % 10)]), 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_recursive(-n, fd);
		return ;
	}
	if (n > 0)
	{
		ft_putnbr_recursive(n / 10, fd);
		write(fd, &("0123456789"[n % 10]), 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == 0)
		write(fd, "0", 1);
	else
		ft_putnbr_recursive(n, fd);
}
