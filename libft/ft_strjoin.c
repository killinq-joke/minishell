/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:55:35 by ztouzri           #+#    #+#             */
/*   Updated: 2021/05/26 16:34:38 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	error_check(char **join, const char *s1, const char *s2)
{
	*join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s1 || !s2 || !join)
		return (0);
	return (1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!error_check(&join, s1, s2))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}
