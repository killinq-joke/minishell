/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 18:33:09 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/30 18:36:40 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	wordlen(char *line)
{
	unsigned int	i;

	i = 0;
	if (line[0] == QUOTE)
	{
		i++;
		while (line[i] != QUOTE && line[i])
			i++;
		if (line[i])
			i++;
	}
	else if (line[0] == DQUOTE)
	{
		i++;
		while (line[i] != DQUOTE && line[i])
			i++;
		if (line[i])
			i++;
	}
	else
	{
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
	}
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
	line = ft_trimquotes(line);
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
