/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbuiltins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:40:27 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/06 15:46:53 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getvalue(const char *name)
{
	int	i;
	int	len;

	if (!name)
		return (ft_strdup(""));
	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	if (name[i] == '=')
		i++;
	else
		return (NULL);
	len = i;
	while (name[len])
		len++;
	return (ft_substr(name, i, len));
}

void	export2(char **command, t_env *env)
{
	int		i;
	t_env	*current;

	current = env;
	while (current->next)
		current = current->next;
	i = 1;
	while (command[i])
	{
		current->next = envinit(getname(command[i]), getvalue(command[i]));
		current = current->next;
		i++;
	}
}

void	export(char **command, t_env *env)
{
	t_env	*current;

	current = env;
	if (splitlen(command) == 1)
	{
		while (current)
		{
			if (current->value)
				printf("declare -x %s=\"%s\"\n", current->name, current->value);
			else
				printf("declare -x %s\n", current->name);
			current = current->next;
		}
	}
	else
		export2(command, env);
}
