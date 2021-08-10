/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 08:32:21 by ztouzri           #+#    #+#             */
/*   Updated: 2021/02/09 12:22:16 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*current;

	current = *alst;
	if (!(new))
		return ;
	if (!(alst) || !(*alst))
	{
		*alst = new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new;
}
