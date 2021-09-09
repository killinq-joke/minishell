/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbuiltins2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:40:27 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/09 17:59:08 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getvalue(const char *name)
{
	int	i;
	int	len;

	if (!name)
		return (NULL);
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

t_bool	envisin(const char *name, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->name, name))
			return (true);
		current = current->next;
	}
	return (false);
}

void	export3(char *command, char *name)
{
	ft_puterr("minishell: export: `");
	ft_puterr(command);
	ft_puterr("': not a valid identifier\n");
	free(name);
}

t_bool	isplusequal(char *envstr)
{
	int	i;

	i = -1;
	while (envstr[++i])
	{
		if (!ft_strncmp(&envstr[i], "+=", 2))
			return (true);
		if (envstr[i] == '=')
			return (false);
	}
	return (false);
}

void	export2(char **command, t_env *env)
{
	int		i;
	t_env	*current;
	char	*name;
	char	*value;
	char	*tmp;
	char	*tmp1;

	i = 1;
	while (command[i])
	{
		name = getname(command[i]);
		current = env;
		while (current->next && ft_strcmp(current->name, name))
			current = current->next;
		if (ft_strlen(name))
		{
			value = getvalue(command[i]);
			if (envisin(name, env) && isplusequal(command[i]))
			{
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
			else if (envisin(name, env))
			{
				if (current->value && value)
					free(current->value);
				if (value)
					current->value = value;
				free(name);
			}
			else
				current->next = envinit(name, value);
			current = current->next;
		}
		else
			export3(command[i], name);
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
