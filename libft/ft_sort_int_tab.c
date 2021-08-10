/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 19:59:57 by ztouzri           #+#    #+#             */
/*   Updated: 2021/05/31 15:29:15 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_sort_int_tab(int *tab, int size)
{
	int	*dup;
	int	i;
	int	tmp;

	dup = ft_calloc(size, sizeof (int));
	i = -1;
	while (++i < size)
		dup[i] = tab[i];
	i = -1;
	while (++i + 1 < size)
	{
		if (dup[i] > dup[i + 1])
		{
			tmp = dup[i];
			dup[i] = dup[i + 1];
			dup[i + 1] = tmp;
			i = -1;
		}
	}
	return (dup);
}
