/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:26:20 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/24 14:11:37by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signal	g_signal;

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

void	signalhandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		if (!g_signal.childpid)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (sig == SIGQUIT && !g_signal.childpid)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		printf("Quit: 3\n");
}

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

int	main(int ac, char **av, char **ev)
{
	char	*line;
	char	*tmp;
	char	**tokens;
	t_all	all;

	(void)ac;
	(void)av;
	all.headenv = envmaker(ev);
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
	while (1)
	{
		echo_control_seq(false);
		g_signal.childpid = 0;
		g_signal.all = &all;
		line = readline("minishell> ");
		if (!line)
		{
			ft_putstrnl("exit");
			close(STDIN_FILENO);
			exit(0);
		}
		add_history(line);
		tmp = line;
		line = ft_strtrim(line, " ");
		free(tmp);
		if (checkerror(line))
		{
			tmp = line;
			line = parsenv(&all, tmp, all.headenv);
			free(tmp);
			tmp = line;
			line = ft_trimquotes(line);
			free(tmp);
			tokens = commandsplit(line);
			free(line);
			if (tokens && splitlen(tokens))
			{
				all.headcmd = parspipe(tokens);
				redirmaker(all.headcmd);
				all.headcmd->path_bis = ft_getenv("PATH", all.headenv);
				cleancommand(all.headcmd);
				minishell(&all, all.headcmd);
				while (wait(NULL) > 0)
					;
				freelink(all.headcmd);
			}
		}
		else
			ft_puterr("parse error\n");
	}
	freeenv(all.headenv);
	return (0);
}
