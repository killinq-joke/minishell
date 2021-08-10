/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:44:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/05/26 16:20:00 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*stmp;

	stmp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (stmp[i] == (unsigned char)c)
			return (&stmp[i]);
		i++;
	}
	return (NULL);
}
