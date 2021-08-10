/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:30:59 by ztouzri           #+#    #+#             */
/*   Updated: 2021/02/09 11:53:09 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;

	current = *lst;
	if (del)
	{
		if (current->next)
			ft_lstclear(&current->next, del);
		ft_lstdelone(current, del);
		*lst = NULL;
	}
	return ;
}
