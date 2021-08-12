/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 20:46:33 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/12 21:29:04 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*envinit(char *name, char *value)
{
	t_env	*new;

	new = calloc(1, sizeof (t_env));
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

char	*getname(char *envstr)
{
	int		i;

	if (!envstr)
		return (NULL);
	i = 0;
	while (envstr[i] && envstr[i] != '=')
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
		current->value = getenv(current->name);
		i++;
		if (!env[i])
			break ;
		current->next = envinit(NULL, NULL);
		current = current->next;
	}
	return (head);
}

void	printenv(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}
