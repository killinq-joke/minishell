/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbuiltins4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:40:27 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/13 01:41:19 by ztouzri          ###   ########.fr       */
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

t_bool	ft_isinlist(char *list, char *name)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (ft_isin(name, list[i]))
			return (true);
		i++;
	}
	return (false);
}

void	unseterror(char *name)
{
	ft_puterr("minishell: unset: `");
	ft_puterr(name);
	ft_puterr("': not a valid identifier\n");
}

char	**cleanlist(char **namelist)
{
	char	**res;
	char	**tmp;
	int		i;

	res = ft_calloc(1, sizeof (char *));
	i = 0;
	while (namelist[i])
	{
		if (ft_isinlist("@#./%^*[]{}?+=", namelist[i]))
			unseterror(namelist[i]);
		else
		{
			tmp = res;
			res = joinstr(res, namelist[i]);
			freetokens(tmp);
		}
		i++;
	}
	return (res);
}

void	unset2(t_all *all, char **namelist, t_env *current)
{
	int		i;
	int		isfirst;
	t_env	*tmp;
	char	**list;

	list = cleanlist(namelist);
	isfirst = true;
	while (current)
	{
		i = 0;
		while (list[++i])
		{
			if (!ft_strcmp(current->name, list[i]))
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
	freetokens(list);
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
