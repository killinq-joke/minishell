/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:56:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/10 12:05:49 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	check_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (true);
	return (false);
}

int	check_double_or_simple_quotes(char *str, int i, char c)
{
	i++;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

t_bool	checkerror(char *line)
{
	int	i;

	i = 0;
	if (!line || (check_space(line) == false))
		return (false);
	while (line[i])
	{
		if (line[i] == ';' || line[i] == '\\')
			return (false);
		if (line[i] == '"')
		{
			if (check_double_or_simple_quotes(line, i, '"') == false)
				return (false);
			i = check_double_or_simple_quotes(line, i, '"');
		}
		if (line[i] == 39)
		{
			if (check_double_or_simple_quotes(line, i, 39) == false)
				return (false);
			i = check_double_or_simple_quotes(line, i, 39);
		}
		i++;
	}
	return (true);
}
