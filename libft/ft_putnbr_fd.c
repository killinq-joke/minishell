/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 08:28:42 by ztouzri           #+#    #+#             */
/*   Updated: 2021/05/26 16:20:35 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n <= 9)
		ft_putchar_fd(n % 10 + '0', fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}
