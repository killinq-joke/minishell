/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimquotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:43:14 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/06 15:42:59 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_trimquotes2(char *str, int i, char *tmp, char *trimmed)
{
	i++;
	while (str[i] && str[i] != '\'')
	{
		tmp = trimmed;
		trimmed = ft_joinchar(tmp, str[i]);
		free(tmp);
		i++;
	}
	return (i);
}

char	*ft_trimquotes(char *str)
{
	int		i;
	char	*tmp;
	char	*trimmed;

	trimmed = ft_calloc(1, sizeof (char));
	i = -1;
	if (str)
	{
		while (str[++i])
		{
			if (str[i] == '\'')
				i = ft_trimquotes2(str, i, tmp, trimmed);
			else if (str[i] == '"')
				i = ft_trimquotes2(str, i, tmp, trimmed);
			else
			{
				tmp = trimmed;
				trimmed = ft_joinchar(tmp, str[i]);
				free(tmp);
			}
		}
		return (trimmed);
	}
	free(trimmed);
	return (NULL);
}
