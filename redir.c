/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 18:31:32 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/31 12:16:21 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*redirinit(char *redir, char *arg)
{
	t_redir	*node;

	node = ft_calloc(1, sizeof (t_redir));
	node->redir = ft_strdup(redir);
	node->arg = ft_strdup(arg);
	node->next = NULL;
	return (node);
}

void	rediradd(t_redir **head, t_redir *new)
{
	t_redir	*current;

	if (!head || !(*head))
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	redirmaker(t_link *cmd)
{
	int		i;
	t_link	*current;

	current = cmd;
	while (current)
	{
		current->redir = NULL;
		i = -1;
		while (current->command[++i])
		{
			if (!ft_strcmp(current->command[i], ">")
				|| !ft_strcmp(current->command[i], ">>")
				|| !ft_strcmp(current->command[i], "<")
				|| !ft_strcmp(current->command[i], "<<"))
			{
				rediradd(&current->redir,
					redirinit(current->command[i], current->command[i + 1]));
				i++;
			}
		}
		current = current->next;
	}
}

char	**redirremover(char **tokens)
{
	int		i;
	int		count;
	char	**tmp;
	char	**res;

	res = ft_calloc(1, sizeof (char *));
	count = 0;
	i = 0;
	while (tokens && tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") && ft_strcmp(tokens[i], ">>")
			&& ft_strcmp(tokens[i], "<") && ft_strcmp(tokens[i], "<<"))
		{
			tmp = res;
			res = joinstr(tmp, tokens[i]);
			free(tmp);
		}
		else
			i++;
		i++;
	}
	return (res);
}
