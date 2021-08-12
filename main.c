/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mout <mout@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:26:20 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/12 12:03:55 by mout             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			while (line[i] && line[i] != DQUOTE)
				i++;
			if (line[i] != DQUOTE)
			{
				ft_puterr("error: unclosed dquotes not supported\n");
				return (-1);
			}
			count++;
		}
		if (line[i] == QUOTE)
		{
			i++;
			while (line[i] && line[i] != QUOTE)
				i++;
			if (line[i] != QUOTE)
			{
				ft_puterr("error: unclosed quotes not supported\n");
				return (-1);
			}
			count++;
		}
		if (!line[i])
			break ;
		i++;
	}
	return (count);
}

char	*parsenv(char *line)
{
	int		i;
	int		j;
	char	*res;
	char	*tmp;
	char	*env;

	res = calloc(1, sizeof (char));
	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == QUOTE)
		{
			tmp = res;
			res = ft_joinchar(tmp, line[i]);
			free(tmp);
			i++;
			while (line[i] && line[i] != QUOTE)
			{
				tmp = res;
				res = ft_joinchar(tmp, line[i]);
				free(tmp);
				i++;
			}
			if (line[i] && line[i] == QUOTE)
			{
				tmp = res;
				res = ft_joinchar(tmp, line[i]);
				free(tmp);
			}
		}
		else if (line[i] && line[i] == '$')
		{
			if (line[i] && line[i + 1] != SPACE)
			{
				j = 0;
				while (line[i + j + 1] && line[i + j + 1] != SPACE
					&& line[i + j + 1] != QUOTE && line[i + j + 1] != DQUOTE)
					j++;
				env = ft_substr(&line[1], i, j);
				//printf("%s\n", env);
				tmp = res;
				res = ft_strjoin(tmp, getenv(env));
				free(tmp);
				free(env);
				i += j;
			}
		}
		else
		{
			tmp = res;
			res = ft_joinchar(tmp, line[i]);
			free(tmp);
		}
		//printf("%s\n", res);
		//ft_putstr(res);
		i++;
		//{
		//	printf("%s\n", res);
		//}
	}
	return (res);
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
	if (wordcount == -1 || !wordcount)
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
	//printf("count == %d\n", wordcount);
	return (split);
}

int	main(int ac, char **av)//, char **ev)
{
	char	*line;
	char	*tmp;
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
		tmp = line;
		line = parsenv(tmp);
		free(tmp);
		tokens = parstoken(line);
		if (tokens && splitlen(tokens))
		{
			head = parspipe(tokens);
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
