/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/16 09:43:51by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal	g_signal;

void	exec_slash_command_non_pipe(t_all *all)
{
	g_signal.fdd = open(g_signal.actuel->command[0], O_RDONLY);
	if (g_signal.file == -1)
	{
	}
	else if (g_signal.fdd == -1)
	{
		all->exit_status = 127;
		ft_puterr("minishell: ");
		ft_puterr(g_signal.actuel->command[0]);
		ft_puterr(": No such file or directory\n");
	}
	else
	{
		g_signal.childpid = fork();
		if (!g_signal.childpid)
		{
			dup2(g_signal.tmpp, STDIN_FILENO);
			if (execve(g_signal.actuel->command[0],
					g_signal.actuel->command, g_signal.env) == -1)
				exit(errno);
		}
		if (g_signal.file != -1)
			dup2(g_signal.out, STDOUT_FILENO);
		waitpid(g_signal.childpid, &all->exit_status, 0);
		if (WEXITSTATUS(all->exit_status))
			all->exit_status = 1;
	}
}

void	redirection_slash_command_non_pipe(void)
{
	g_signal.current = g_signal.actuel->redir;
	while (g_signal.current)
	{
		if (!ft_strcmp(g_signal.current->redir, ">"))
		{
			g_signal.file = open(g_signal.current->arg,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(g_signal.file, STDOUT_FILENO);
			close(g_signal.file);
		}
		if (!ft_strcmp(g_signal.current->redir, ">>"))
		{
			g_signal.file = open(g_signal.current->arg,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(g_signal.file, STDOUT_FILENO);
			close(g_signal.file);
		}
		if (!ft_strcmp(g_signal.current->redir, "<"))
		{
			g_signal.tmpp = dup(STDIN_FILENO);
			g_signal.redir = true;
			g_signal.file = open(g_signal.current->arg, O_RDONLY);
			if (g_signal.file == -1)
			{
				ft_puterr("minishell: ");
				ft_puterr(g_signal.current->arg);
				ft_puterr(": No such file or directory\n");
				break ;
			}
			g_signal.tmpp = dup(g_signal.file);
			close(g_signal.file);
		}
		g_signal.current = g_signal.current->next;
	}
}

void	error_path_slash_command(t_all *all)
{
	all->exit_status = 126;
	ft_puterr("minishell: ");
	ft_puterr(g_signal.actuel->command[0]);
	ft_puterr(" : is a Directory \n");
}
