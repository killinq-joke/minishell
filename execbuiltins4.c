/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbuiltins4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:40:27 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/09 23:32:26 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset3(t_all *all, t_env *current)
{
	all->headenv = current->next;
	freeenv(current);
}

void	unset4(t_env *current, t_env *tmp)
{
	tmp->next = current->next;
	freeenv(current);
}

void	unset2(t_all *all, char **namelist, t_env *current)
{
	int		i;
	int		isfirst;
	t_env	*tmp;

	isfirst = true;
	while (current)
	{
		i = 0;
		while (namelist[++i])
		{
			if (!ft_strcmp(current->name, namelist[i]))
			{
				if (isfirst)
					unset3(all, current);
				else
					unset4(current, tmp);
				current = all->headenv;
				isfirst = true;
				break ;
			}
		}
		tmp = current;
		current = current->next;
		isfirst = false;
	}
}

void	unset(char **namelist, t_all *all)
{
	t_env	*current;

	current = all->headenv;
	if (!namelist || !all->headenv)
		return ;
	if (envlen(all->headenv) == 1)
		freeenv(all->headenv);
	unset2(all, namelist, current);
}
