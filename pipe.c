/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/08 10:30:18 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal	g_signal;

int	heredoc_non_pipe_command2(int tmpp, char *line)
{
	free(line);
	tmpp = open("/tmp/hd", O_RDONLY);
	unlink("/tmp/hd");
	return (tmpp);
}

int	heredoc_non_pipe_command(t_link *actuel, int tmpp)
{
	t_redir	*current;
	char	*line;
	char	*tmp;

	current = actuel->redir;
	while (current)
	{
		if (!ft_strcmp(current->redir, "<<"))
		{
			tmpp = open("/tmp/hd", O_CREAT | O_TRUNC | O_WRONLY, 0600);
			line = readline("> ");
			while (line && ft_strcmp(line, current->arg))
			{
				write(tmpp, line, ft_strlen(line));
				write(tmpp, "\n", 1);
				tmp = line;
				line = readline("> ");
				free(tmp);
			}
			tmpp = heredoc_non_pipe_command2(tmpp, line);
		}
		current = current->next;
	}
	return (tmpp);
}

void	fill_structure(t_link *cmd, t_all *all)
{
	g_signal.co = 0;
	g_signal.taille = linklen(cmd);
	g_signal.tmpp = STDIN_FILENO;
	g_signal.out = dup(STDOUT_FILENO);
	g_signal.file = -2;
	g_signal.errorleft = false;
	g_signal.redir = false;
	g_signal.env = envtab(all->headenv);
	g_signal.actuel = cmd;
	all->exit_status = 0;
	echo_control_seq(true);
}

void	minishell(t_all *all, t_link *cmd)
{
	fill_structure(cmd, all);
	while (g_signal.actuel)
	{
		if (g_signal.actuel->next)
			all_pipe_execution(all);
		else
			all_non_pipe_execution(all);
		g_signal.actuel = g_signal.actuel->next;
	}
	freetokens(g_signal.env);
}
