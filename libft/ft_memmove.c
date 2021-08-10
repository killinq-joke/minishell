/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:45:55 by ztouzri           #+#    #+#             */
/*   Updated: 2021/01/22 11:55:21 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dsttmp;
	unsigned char	*srctmp;
	size_t			i;

	srctmp = (unsigned char *)src;
	dsttmp = (unsigned char *)dst;
	if (dsttmp > srctmp)
		while (len--)
			dsttmp[len] = srctmp[len];
	else if (dsttmp < srctmp)
	{
		i = 0;
		while (i < len)
		{
			dsttmp[i] = srctmp[i];
			i++;
		}
	}
	return (dst);
}
