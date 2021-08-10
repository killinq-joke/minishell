/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:07:57 by ztouzri           #+#    #+#             */
/*   Updated: 2021/02/02 13:21:22 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	i = -1;
	while (set[++i])
	{
		if (s1[start] == set[i])
		{
			start++;
			i = -1;
		}
		if (s1[end] == set[i])
		{
			end--;
			i = -1;
		}
	}
	return (ft_substr(s1, start, end - start + 1));
}
