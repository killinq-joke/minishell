/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbuiltins5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:40:27 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/09 17:59:08 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export4(char *value, char *tmp1, t_env *current, char *name)
{
	char	*tmp;

	if (value)
	{
		tmp = current->value;
		tmp1 = value;
		current->value = ft_strjoin(tmp, tmp1);
		free(tmp);
		free(tmp1);
	}
	free(name);
}

void	export5(t_env *current, char *name, char *value)
{
	if (current->value && value)
		free(current->value);
	if (value)
		current->value = value;
	free(name);
}

void	export2(char **command, t_env *env, char *tmp1, t_env *current)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (command[++i])
	{
		name = getname(command[i]);
		current = env;
		while (current->next && ft_strcmp(current->name, name))
			current = current->next;
		if (ft_strlen(name))
		{
			value = getvalue(command[i]);
			if (envisin(name, env) && isplusequal(command[i]))
				export4(value, tmp1, current, name);
			else if (envisin(name, env))
				export5(current, name, value);
			else
				current->next = envinit(name, value);
			current = current->next;
		}
		else
			export3(command[i], name);
	}
}
