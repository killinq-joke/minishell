/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parspipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:28:27 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/31 15:55:23 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_link	*linkinit(char **cmd)
{
	t_link	*new;

	new = ft_calloc(1, sizeof (t_link));
	new->command = cmd;
	new->next = NULL;
	return (new);
}

char	**parstoken(char *line)
{
	char	**tokens;
	int		i;

	tokens = commandsplit(line);
	i = 0;
	while (tokens && tokens[i])
		i++;
	return (tokens);
}

void	freetokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

char	**parscmd(char **tokens, size_t *i)
{
	size_t	len;
	size_t	j;
	char	**command;

	len = 0;
	while (tokens[*i + len] && ft_strcmp(tokens[*i + len], "|"))
		len++;
	command = ft_calloc(len + 1, sizeof (char *));
	j = 0;
	while (j < len)
	{
		command[j] = ft_strdup(tokens[*i]);
		j++;
		(*i)++;
	}
	command[j] = NULL;
	return (command);
}

t_link	*parspipe(char **tokens)
{
	t_link	*head;
	t_link	*current;
	size_t	i;

	i = 0;
	head = linkinit(NULL);
	current = head;
	while (tokens[i])
	{
		current->command = parscmd(tokens, &i);
		if (tokens[i] && !ft_strcmp(tokens[i], "|"))
			i++;
		if (!tokens[i])
			break ;
		current->next = linkinit(NULL);
		current = current->next;
	}
	freetokens(tokens);
	return (head);
}

void	freelinknode(t_link *node)
{
	t_redir	*tmp;
	t_redir	*current;

	freetokens(node->command);
	freetokens(node->path);
	free(node->path_bis);
	current = node->redir;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

void	freelink(t_link *cmd)
{
	t_link	*tmp;
	t_link	*current;

	current = cmd;
	while (current)
	{
		tmp = current;
		current = current->next;
		freelinknode(tmp);
	}
}
