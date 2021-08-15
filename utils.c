/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:27:36 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/15 15:37:59 by ztouzri          ###   ########.fr       */
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

size_t	envlen(t_env *head)
{
	size_t	i;
	t_env	*current;

	i = 0;
	current = head;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

char	*ft_getenv(const char *name, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(name, current->name))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
