/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:26:20 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/13 02:04:45 by ztouzri          ###   ########.fr       */
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
	(void)c;
	ioctl(ttyslot(), TIOCGETA, &conf);
	if (c == true)
		conf.c_lflag |= ECHOCTL;
	else if (c == false)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCSETA, &conf);
}

int	is_a_num(char *c)
{
	int	i ;
	int	count;

	count = 0;
	i = -1;
	while (c[++i])
		if (c[i] == '-')
			count++;
	if (count > 1)
		return (0);
	if ((c[0] == '-' || c[0] == '+')
		&& (c[1] >= '0' && c[1] <= '9'))
		return (1);
	return (0);
}
