/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimquotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:43:14 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/12 17:42:44 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trimquotes(char *str)
{
	int		i;
	char	*tmp;
	char	*trimmed;

	trimmed = calloc(1, sizeof (char));
	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] != '\'' && str[i] != '"')
			{
				tmp = trimmed;
				trimmed = ft_joinchar(tmp, str[i]);
				free(tmp);
			}
			i++;
		}
	}
	else
		return (str);
	return (trimmed);
}
