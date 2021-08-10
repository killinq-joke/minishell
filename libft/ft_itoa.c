/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:46:39 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/12 18:51:07 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_char(int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		i;
	int		symbole;

	symbole = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		symbole++;
	}
	i = nb_char(n) + symbole;
	itoa = ft_calloc(sizeof (char), i + 1);
	if (itoa == 0)
		return (0);
	while (i > 0)
	{
		i--;
		itoa[i] = n % 10 + 48;
		n /= 10;
	}
	if (symbole == 1)
		itoa[i] = '-';
	return (itoa);
}
