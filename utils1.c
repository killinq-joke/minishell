/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:04:53 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/13 15:19:07 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	checkquotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == QUOTE)
		{
			i++;
			while (str[i] && str[i] != QUOTE)
				i++;
			if (!str[i])
				return (false);
		}
		if (str[i] == DQUOTE)
		{
			i++;
			while (str[i] && str[i] != DQUOTE)
				i++;
			if (!str[i])
				return (false);
		}
		i++;
	}
	return (true);
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

void	quit(void)
{
	ft_putstrnl("exit");
	echo_control_seq(true);
	exit(0);
}
