/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:27:36 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/13 00:47:49 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	splitlen(char **split)
{
	size_t	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

size_t	linklen(t_link *head)
{
	size_t	i;
	t_link	*current;

	i = 0;
	current = head;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}
