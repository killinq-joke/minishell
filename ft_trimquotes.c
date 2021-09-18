/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimquotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:43:14 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/18 17:19:31 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

extern t_signal	g_signal;

char	*ft_trimquotes2(char *str, char *tmp, char *trimmed)
{
	g_signal.u++;
	while (str[g_signal.u] && str[g_signal.u] != '\'')
	{
		tmp = trimmed;
		trimmed = ft_joinchar(tmp, str[g_signal.u]);
		free(tmp);
		g_signal.u++;
	}
	if (str[g_signal.u] == '\'')
		g_signal.u++;
	return (trimmed);
}

char	*ft_trimquotes3(char *str, char *tmp, char *trimmed)
{
	g_signal.u++;
	while (str[g_signal.u] && str[g_signal.u] != '"')
	{
		tmp = trimmed;
		trimmed = ft_joinchar(tmp, str[g_signal.u]);
		free(tmp);
		g_signal.u++;
	}
	if (str[g_signal.u] == '"')
		g_signal.u++;
	return (trimmed);
}

char	*ft_trimquotes(char *str)
{
	char	*tmp;
	char	*trimmed;

	trimmed = ft_calloc(1, sizeof (char));
	g_signal.u = 0;
	if (str)
	{
		while (str[g_signal.u])
		{
			if (str[g_signal.u] == '\'')
				trimmed = ft_trimquotes2(str, tmp, trimmed);
			else if (str[g_signal.u] == '"')
				trimmed = ft_trimquotes3(str, tmp, trimmed);
			else
			{
				tmp = trimmed;
				trimmed = ft_joinchar(tmp, str[g_signal.u]);
				free(tmp);
				g_signal.u++;
			}
		}
		return (trimmed);
	}
	free(trimmed);
	return (NULL);
}
