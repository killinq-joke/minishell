/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parspipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:28:27 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/10 13:47:28 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_link	*parspipe(char *line)
{
	char	**args;
	int		i;

	args = commandsplit(line);
	if (args == NULL)
		return (NULL);
	i = 0;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	return NULL;
}
