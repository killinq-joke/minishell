/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 18:30:45 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/30 18:30:52 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printredir(t_redir *redir)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		printf("redir == %s | arg == %s | %p\n", current->redir, current->arg, current->next);
		current = current->next;
	}
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
		printredir(current->redir);
		printf("-------------------------------\n");
		current = current->next;
	}
}

void	printsplit(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}
