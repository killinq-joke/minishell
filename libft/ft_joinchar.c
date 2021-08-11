/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 20:55:02 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/11 19:47:38 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_joinchar(char *str, char c)
{
	char	*join;
	int		i;

	join = ft_calloc(ft_strlen(str) + 2, sizeof (char));
	i = 0;
	while (str && str[i])
	{
		join[i] = str[i];
		i++;
	}
	join[i] = c;
	return (join);
}
