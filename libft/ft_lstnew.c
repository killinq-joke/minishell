/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 10:04:59 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/12 18:51:11 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = malloc(sizeof (t_list));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
