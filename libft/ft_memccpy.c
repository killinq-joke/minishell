/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:54:22 by ztouzri           #+#    #+#             */
/*   Updated: 2021/05/26 16:19:55 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*srctmp;
	unsigned char	*desttmp;
	unsigned char	ctmp;

	srctmp = (unsigned char *)src;
	desttmp = (unsigned char *)dest;
	ctmp = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		desttmp[i] = srctmp[i];
		if (srctmp[i] == ctmp)
			return (&desttmp[i + 1]);
		i++;
	}
	return (NULL);
}
