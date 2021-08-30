/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 18:32:43 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/30 18:32:48 by ztouzri          ###   ########.fr       */
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
	t_link	*current;	

	current = cmd;
	while (current)
	{
		current->command = redirremover(current->command);
		trimtokens(current->command);
		current = current->next;
	}
}