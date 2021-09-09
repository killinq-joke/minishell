/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:26:20 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/09 02:08:11 by ztouzri          ###   ########.fr       */
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
		if (g_signal.heredoc)
		{
			g_signal.interrupt = true;
			printf("\n");
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			printf("\n");
			if (!g_signal.childpid)
			{
				rl_on_new_line();
				rl_replace_line("", 0);
				rl_redisplay();
			}
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

void	minishell2(char *tmp, char *line, t_all *all)
{
	char	**tokens;

	tmp = line;
	line = parsenv(all, tmp, all->headenv);
	free(tmp);
	tokens = commandsplit(line);
	free(line);
	if (tokens && splitlen(tokens))
	{
		all->headcmd = parspipe(tokens);
		redirmaker(all->headcmd);
		all->headcmd->path_bis = ft_getenv("PATH", all->headenv);
		cleancommand(all->headcmd);
		minishell(all, all->headcmd);
		while (wait(NULL) > 0)
			;
		freelink(all->headcmd);
	}
}

void	complete_minishell(t_all *all)
{
	char	*line;
	char	*tmp;	

	while (1)
	{
		echo_control_seq(false);
		g_signal.childpid = 0;
		g_signal.all = all;
		line = readline("minishell> ");
		if (!line)
		{
			ft_putstrnl("exit");
			close(STDIN_FILENO);
			exit(0);
		}
		if (ft_strlen(line))
			add_history(line);
		tmp = line;
		line = ft_strtrim(line, " ");
		free(tmp);
		if (checkerror(line))
			minishell2(tmp, line, all);
		else
			ft_puterr("parse error\n");
	}
}

int	main(int ac, char **av, char **ev)
{
	t_all	all;

	(void)ac;
	(void)av;
	all.headenv = envmaker(ev);
	signal(SIGINT, signalhandler);
	signal(SIGQUIT, signalhandler);
	complete_minishell(&all);
	freeenv(all.headenv);
	return (0);
}
