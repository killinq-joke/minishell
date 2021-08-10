/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:56:04 by ztouzri           #+#    #+#             */
/*   Updated: 2021/05/26 16:45:57 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped;
	t_list	*new;

	mapped = NULL;
	if (f && del)
	{
		while (lst)
		{
			new = ft_lstnew(f(lst->content));
			if (!new)
			{
				ft_lstclear(&mapped, del);
				return (NULL);
			}
			ft_lstadd_back(&mapped, new);
			lst = lst->next;
		}
		return (mapped);
	}
	return (NULL);
}
