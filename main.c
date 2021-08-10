/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:26:20 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/10 16:51:34 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_link	*linkinit(char **cmd, char **env)
{
	t_link	*new;

	new = calloc(1, sizeof (t_link));
	new->env = env;
	new->command = cmd;
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
		j += spacecount(&line[j]);
		len = wordlen(&line[j]);
		split[i] = ft_substr(line, j, len);
		j += len;
		i++;
	}
	split[i] = NULL;
	printf("count == %d\n", wordcount);
	return (split);
}

int	main(int ac, char **av, char **ev)
{
	char	*line;
	char	**tokens;
	t_link	*head;
	t_link	*current;
	int		i;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
		tokens = parstoken(line);
		if (tokens)
		{
			head = parspipe(tokens, ev);
			current = head;
			while (current)
			{
				printf("--------------------------------------------------------------------------------\n");
				i = 0;
				while (current->command[i])
				{
					printf("%s\n", current->command[i]);
					i++;
				}
				current = current->next;
			}
			//interpret
		}
	}
	return (0);
}
