/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 18:32:43 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/01 11:43:15 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trimtokens(char **tokens)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tokens && tokens[i])
	{
		tmp = tokens[i];
		tokens[i] = ft_trimquotes(tmp);
		free(tmp);
		i++;
	}
}

void	cleancommand(t_link *cmd)
{
	char	**tmp;	
	t_link	*current;	

	current = cmd;
	while (current)
	{
		tmp = current->command;
		current->command = redirremover(tmp);
		freetokens(tmp);
		trimtokens(current->command);
		current = current->next;
	}
}
