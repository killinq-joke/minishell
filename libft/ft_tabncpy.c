/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:36:49 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/02 17:39:07 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_tabncpy(int *tab, int size)
{
	int	*cpy;
	int	i;

	cpy = ft_calloc(size, sizeof (int));
	i = 0;
	while (i < size)
	{
		cpy[i] = tab[i];
		i++;
	}
	return (cpy);
}
