/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:56:32 by ztouzri           #+#    #+#             */
/*   Updated: 2021/05/26 16:16:42 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*duplicate;
	size_t	i;

	duplicate = malloc(ft_strlen(s1) + 1);
	if (!duplicate)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		duplicate[i] = s1[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
