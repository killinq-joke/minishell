/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:33:17 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/16 10:50:46 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_decimalconvert(const char *deciptr)
{
	int		len;
	double	result;

	result = 0;
	len = ft_strlen(deciptr);
	while (len--)
	{
		result = result / 10 + deciptr[len] - '0';
	}
	result /= 10;
	return (result);
}

double	ft_atof(const char *nptr)
{
	double	result;
	int		sign;
	size_t	i;

	sign = 1;
	result = 0;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n' || \
	nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
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
	if (nptr[i] == '.')
		result += ft_decimalconvert(&nptr[i + 1]);
	return (sign * result);
}
