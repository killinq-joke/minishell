/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 20:46:33 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/09 17:10:28 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*envinit(char *name, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof (t_env));
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

char	*getname(char *envstr)
{
	int		i;

	if (!envstr)
		return (ft_strdup(""));
	i = -1;
	while (envstr[++i])
	{
		if (envstr[i] == '+')
		{
			if (envstr[i + 1] == '=')
				return (ft_substr(envstr, 0, i));
			else
				return (ft_strdup(""));
		}
	}
	i = 0;
	while (envstr[i] && envstr[i] != SPACE && envstr[i] != '=')
		i++;
	return (ft_substr(envstr, 0, i));
}

t_env	*envmaker(char **env)
{
	int		i;
	t_env	*head;
	t_env	*current;

	if (!env)
		return (NULL);
	head = envinit(NULL, NULL);
	current = head;
	i = 0;
	while (env[i])
	{
		current->name = getname(env[i]);
		current->value = ft_strdup(getenv(current->name));
		i++;
		if (!env[i])
			break ;
		current->next = envinit(NULL, NULL);
		current = current->next;
	}
	return (head);
}

void	freeenv(t_env *node)
{
	if (node->value && ft_strlen(node->value))
		free(node->value);
	if (node->name)
		free(node->name);
	free(node);
}

void	printenv(t_env *env)
{
	t_env	*current;

	if (env)
	{
		current = env;
		while (current)
		{
			if (current->value)
				printf("%s=%s\n", current->name, current->value);
			current = current->next;
		}
	}
}
