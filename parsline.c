/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 18:20:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/08 10:30:04 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	counttoken_space(t_pars *parse, char *line)
{
	while (line[parse->k] == SPACE)
		parse->k++;
	if (line[parse->k])
		parse->count++;
}

int	counttoken_space_quote(t_pars *parse, char *line)
{
	parse->k++;
	while (line[parse->k])
	{
		if (line[parse->k] == QUOTE)
			parse->nbquote++;
		if ((line[parse->k] == QUOTE && (line[parse->k + 1] == SPACE
					|| !line[parse->k + 1])))
			break ;
		parse->k++;
	}
	if (!(parse->nbquote % 2))
	{
		ft_puterr("error: unclosed quotes not supported\n");
		return (-1);
	}
	parse->count++;
	return (0);
}

int	counttoken_space_dquote(t_pars *parse, char *line)
{
	parse->k++;
	while (line[parse->k])
	{
		if (line[parse->k] == DQUOTE)
			parse->nbquote++;
		if ((line[parse->k] == DQUOTE
				&& (line[parse->k + 1] == SPACE || !line[parse->k + 1])))
			break ;
		parse->k++;
	}
	if (!(parse->nbquote % 2))
	{
		ft_puterr("error: unclosed dquotes not supported\n");
		return (-1);
	}
	parse->count++;
	return (0);
}

int	counttoken(char *line)
{
	t_pars	parse;

	parse.nbquote = 0;
	parse.count = 0;
	parse.k = 0;
	if (line[parse.k] && line[parse.k] != SPACE)
		parse.count++;
	while (line[parse.k])
	{
		if (line[parse.k] == SPACE)
			counttoken_space(&parse, line);
		if (line[parse.k] == DQUOTE)
			if (counttoken_space_dquote(&parse, line) == -1)
				return (-1);
		if (line[parse.k] == QUOTE)
			if (counttoken_space_quote(&parse, line) == -1)
				return (-1);
		if (!line[parse.k])
			break ;
		parse.k++;
		parse.nbquote = 0;
	}
	return (parse.count);
}
