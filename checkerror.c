/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:56:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/31 12:05:29 by ztouzri          ###   ########.fr       */
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

t_bool	checkerror1(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ';' || line[i] == '\\' || !ft_strncmp(">|", &line[i], 2)
			|| !ft_strncmp("<|", &line[i], 2) || !ft_strncmp("<>", &line[i], 2)
			|| !ft_strncmp("><", &line[i], 2) || !ft_strncmp(">>>", &line[i], 3)
			|| !ft_strncmp("<<<", &line[i], 3))
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
	}
	return (true);
}

t_bool	checkerror(char *line)
{
	if (!line)
		return (false);
	if (ft_strlen(line))
	{	
		if (ft_isin("|><", line[ft_strlen(line) - 1]))
			return (false);
	}
	if (checkerror1(line) == false)
		return (false);
	else
		return (true);
}
