/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parspipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:28:27 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/02 14:56:32 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free(tmp->arg);
		free(tmp->redir);
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
		free(tmp);
	}
}
