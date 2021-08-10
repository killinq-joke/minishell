/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:26:20 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/10 13:59:11 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_link	*linkinit(char *cmd, char **args, t_bool operator, char **env)
{
	t_link	*new;

	new = calloc(1, sizeof (t_link));
	new->env = env;
	new->command = cmd;
	new->args = args;
	new->operator = operator;
	new->next = NULL;
	return (new);
}

int	counttoken(char *line)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (line[i] && line[i] != SPACE && line[i] != DQUOTE && line[i] != QUOTE)
		count++;
	while (line[i])
	{
		if (line[i] == SPACE)
		{
			while (line[i] == SPACE)
				i++;
			if (line[i])
				count++;
		}
		if (line[i] == DQUOTE)
		{
			i++;
			while (line[i] != DQUOTE && line[i])
				i++;
			if (line[i] == DQUOTE)
				i++;
			else
			{
				ft_puterr("error: unclosed dquotes not supported\n");
				return (-1);
			}
			count++;
		}
		if (line[i] == QUOTE)
		{
			i++;
			while (line[i] != QUOTE && line[i])
				i++;
			if (line[i] == QUOTE)
				i++;
			else
			{
				ft_puterr("error: unclosed quotes not supported\n");
				return (-1);
			}
			count++;
		}
		i++;
	}
	return (count);
}

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
		while (line[i] != SPACE && line[i])
			i++;
	printf("%u <-- len\n", i);
	return (i);
}

int	spacecount(char *line)
{
	int	nb;

	nb = 0;
	while (line[nb] && line[nb] == SPACE)
		nb++;
	return (nb);
}

char	**commandsplit(char *line)
{
	char	**split;
	int		i;
	size_t	j;
	int		wordcount;
	int		len;

	wordcount = counttoken(line);
	if (wordcount == -1)
		return (NULL);
	split = calloc(wordcount + 1, sizeof (char *));
	j = 0;
	i = 0;
	while (i < wordcount && j < ft_strlen(line))
	{
		len = wordlen(&line[j]);
		split[i] = ft_substr(line, j, len);
		//printf("%u\n", wordlen(&line[j]));
		j += len;
		j += spacecount(&line[j]);
		i++;
	}
	split[i] = NULL;
	printf("count == %d\n", wordcount);
	return (split);
}

int	main(int ac, char **av, char **ev)
{
	char	*line;

	(void)ac;
	(void)av;
	(void)ev;
	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
		if (parspipe(line))
		{
			//interpret
		}
	}
	return (0);
}
