/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:57:49 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/27 12:56:36 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1tmp;
	unsigned char	*s2tmp;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	s1tmp = (unsigned char *)s1;
	s2tmp = (unsigned char *)s2;
	i = 0;
	if (!n)
		return (0);
	while (i < n - 1 && s1tmp[i] == s2tmp[i] && s1tmp[i])
		i++;
	return (s1tmp[i] - s2tmp[i]);
}
