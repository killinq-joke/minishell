/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:42:18 by ztouzri           #+#    #+#             */
/*   Updated: 2021/05/26 16:18:28 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	space;
	void	*ptr;

	space = count * size;
	ptr = malloc(space);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, space);
	return (ptr);
}
