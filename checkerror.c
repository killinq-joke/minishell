/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:56:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/13 15:05:10 by ztouzri          ###   ########.fr       */
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

int	check_redir_pipe(char *str, int i)
{
	i++;
	while (str[i] && ft_isin(" |", str[i]))
	{
		if (str[i] == '|')
			return (0);
		i++;
	}
	return (i);
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
		if (ft_isin("><", line[i]))
		{
			if (!check_redir_pipe(line, i))
				return (false);
			i = check_redir_pipe(line, i);
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
	if (!checkquotes(line))
		return (false);
	if (!checkerror1(line))
		return (false);
	else
		return (true);
}
