/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 18:33:09 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/18 17:19:19 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	wordlen1(char *line)
{
	unsigned int	i;

	i = 0;
	while (line[i] != SPACE && line[i])
	{
		if (line[i] == QUOTE)
		{
			i++;
			while (line[i] != QUOTE && line[i])
				i++;
		}
		else if (line[i] == DQUOTE)
		{
			i++;
			while (line[i] != DQUOTE && line[i])
				i++;
		}
		i++;
	}
	return (i);
}

unsigned int	wordlen_quotes(char *line)
{
	int	i;
	int	nbquotes;

	i = 1;
	nbquotes = 0;
	while (line[i])
	{
		if (line[i] == QUOTE)
			nbquotes++;
		if (nbquotes % 2 && (line[i + 1] == SPACE || !line[i + 1]))
			break ;
		i++;
	}
	if (line[i])
		i++;
	return (i);
}

unsigned int	wordlen(char *line)
{
	unsigned int	i;
	int				nbquotes;

	nbquotes = 0;
	i = 0;
	if (line[0] == QUOTE)
		i = wordlen_quotes(line);
	else if (line[0] == DQUOTE)
	{
		i++;
		while (line[i])
		{
			if (line[i] == DQUOTE)
				nbquotes++;
			if (nbquotes % 2 && (line[i + 1] == SPACE || !line[i + 1]))
				break ;
			i++;
		}
		if (line[i])
			i++;
	}
	else
		i = wordlen1(line);
	return (i);
}

char	**commandsplit(char *line)
{
	char	**split;
	int		i;
	size_t	j;
	int		wordcount;
	int		len;

	wordcount = counttoken(line);
	if (wordcount == -1 || !wordcount)
		return (NULL);
	split = ft_calloc(wordcount + 1, sizeof (char *));
	j = 0;
	i = 0;
	while (i < wordcount && j < ft_strlen(line))
	{
		j += ft_spacecount(&line[j]);
		len = wordlen(&line[j]);
		split[i] = ft_substr(line, j, len);
		j += len;
		i++;
	}
	split[i] = NULL;
	return (split);
}
