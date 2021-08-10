/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:26:20 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/10 12:00:05 by ztouzri          ###   ########.fr       */
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
	if (line[i])
		count++;
	while (line[i])
	{
		if (line[i] == SPACE)
		{
			while (line[i] == SPACE)
				i++;
			count++;
		}
		if (line[i] == DQUOTE)
		{
			i++;
			while (line[i] != DQUOTE && line[i])
				i++;
			if (line[i])
				i++;
			else
				ft_puterr("error: unclosed dquotes not supported\n");
			count++;
		}
		if (line[i] == QUOTE)
		{
			i++;
			while (line[i] != QUOTE && line[i])
				i++;
			if (line[i])
				i++;
			else
				ft_puterr("error: unclosed quotes not supported\n");
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
	return (i);
}

char	**commandsplit(char *line)
{
	char			**split;
	unsigned int	i;
	unsigned int	j;
	unsigned int	wordcount;

	wordcount = counttoken(line);
	j = 0;
	i = 0;
	while (i < wordcount && j < ft_strlen(line))
	{
		split[i] = ft_substr(line, j, wordlen(&line[j]));
		printf("%u\n", wordlen(&line[j]));
		j += wordlen(&line[j]) + 1;
		i++;
	}
	printf("count == %d\n", counttoken(line));
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
		basepars(line);
	}
	return (0);
}
