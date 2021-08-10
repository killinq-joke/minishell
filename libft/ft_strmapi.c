/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:14:23 by ztouzri           #+#    #+#             */
/*   Updated: 2021/05/26 16:15:45 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*res;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
