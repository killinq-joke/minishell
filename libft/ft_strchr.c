/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:56:11 by ztouzri           #+#    #+#             */
/*   Updated: 2021/05/26 16:17:12 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			res = (char *)&s[i];
			return (res);
		}
		i++;
	}
	if (s[i] == (char)c)
	{
		res = (char *)&s[i];
		return (res);
	}
	return (NULL);
}
