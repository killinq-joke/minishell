/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 19:11:38 by ztouzri           #+#    #+#             */
/*   Updated: 2021/05/28 19:12:02 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	long	result;
	int		sign;
	size_t	i;

	sign = 1;
	result = 0;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (sign * result);
}
