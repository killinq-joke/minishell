/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:26:20 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/08 10:30:23 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_signal;

char	**joinstr(char **split, char *str)
{
	int		i;
	char	**join;

	join = ft_calloc(splitlen(split) + 2, sizeof (char *));
	i = 0;
	while (split[i])
	{
		join[i] = ft_strdup(split[i]);
		i++;
	}
	join[i] = ft_strdup(str);
	return (join);
}

char	**envtab(t_env	*env)
{
	int		i;
	char	**tab;
	char	*tmp;
	t_env	*current;

	tab = ft_calloc(envlen(env) + 1, sizeof (char *));
	i = 0;
	current = env;
	while (current)
	{
		tab[i] = ft_strjoin(current->name, "=");
		tmp = tab[i];
		tab[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		current = current->next;
		i++;
	}
	return (tab);
}

void	echo_control_seq(t_bool c)
{
	struct termios	conf;

	ioctl(ttyslot(), TIOCGETA, &conf);
	if (c == true)
		conf.c_lflag |= ECHOCTL;
	else if (c == false)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCSETA, &conf);
}
