/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:26:20 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/17 01:49:42 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	counttoken(char *line)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	printf("%s\n", line);
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

char	*parsenv(char *line, t_env *env)
{
	int		i;
	int		j;
	char	*res;
	char	*tmp;
	char	*tmp1;
	char	*name;
	int		status;
	t_bool	indquote;

	res = calloc(1, sizeof (char));
	i = 0;
	indquote = false;
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
				name = ft_substr(&line[1], i, j);
				if (!ft_strcmp(name, "?"))
				{
					//a modifier
					WEXITSTATUS(status);
					tmp = res;
					tmp1 = ft_itoa(status);
					res = ft_strjoin(tmp, tmp1);
					printf("%d\n", status);
					free(tmp1);
					free(tmp);
				}
				else
				{
					tmp = res;
					res = ft_strjoin(tmp, ft_getenv(name, env));
					free(tmp);
				}
				i += j;
			}
		}
		else
		{
			if (line[i] == DQUOTE)
				indquote = !indquote;
			if ((!ft_strncmp(">>", &line[i], 2) || !ft_strncmp("<<", &line[i], 2)) && !indquote)
			{
				tmp = res;
				res = ft_joinchar(tmp, ' ');
				free(tmp);
				tmp = res;
				res = ft_joinchar(tmp, line[i++]);
				free(tmp);
				tmp = res;
				res = ft_joinchar(tmp, line[i]);
				free(tmp);
				tmp = res;
				res = ft_joinchar(tmp, ' ');
				free(tmp);
			}
			else if (ft_isin("><|", line[i]) && !indquote)
			{
				tmp = res;
				res = ft_joinchar(tmp, ' ');
				free(tmp);
				tmp = res;
				res = ft_joinchar(tmp, line[i]);
				free(tmp);
				tmp = res;
				res = ft_joinchar(tmp, ' ');
				free(tmp);
			}
			else
			{
				tmp = res;
				res = ft_joinchar(tmp, line[i]);
				free(tmp);
			}
		}
		i++;
	}
	printf("----%s\n", res);
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
	return (split);
}

void	printlink(t_link *cmd)
{
	int		i;
	t_link	*current;

	current = cmd;
	while (current)
	{
		i = 0;
		while (current->command[i])
		{
			printf("%s\n", current->command[i]);
			i++;
		}
		printf("-------------------------------\n");
		current = current->next;
	}
}

int	main(int ac, char **av, char **ev)
{
	char	*line;
	char	*tmp;
	char	**tokens;
	t_all	all;

	(void)ac;
	(void)av;
	all.headenv = envmaker(ev);
	while (1)
	{
		line = readline("minishell> ");
		add_history(line);
		tmp = line;
		line = ft_strtrim(line, " ");
		free(tmp);
		if (checkerror(line) == true)
		{
			tmp = line;
			line = parsenv(tmp, all.headenv);
			free(tmp);
			tokens = parstoken(line);
			if (tokens && splitlen(tokens))
			{
				all.headcmd = parspipe(tokens);
				all.headcmd->path_bis = ft_getenv("PATH", all.headenv);
				printlink(all.headcmd);
				//give_good_path(&all);
				//minishell(&all, all.headcmd);
			}
		}
	}
	return (0);
}
