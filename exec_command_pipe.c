/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/08 10:29:04 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal	g_signal;

void	redirection_exec_command_pipe2(void)
{
	if (!ft_strcmp(g_signal.current->redir, ">"))
	{
		g_signal.redir = true;
		g_signal.file = open(g_signal.current->arg,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
		dup2(g_signal.file, STDOUT_FILENO);
		close(g_signal.file);
	}
	if (!ft_strcmp(g_signal.current->redir, ">>"))
	{
		g_signal.redir = true;
		g_signal.file = open(g_signal.current->arg,
				O_RDWR | O_CREAT | O_APPEND, 0644);
		dup2(g_signal.file, STDOUT_FILENO);
		close(g_signal.file);
	}
}

void	redirection_exec_command_pipe3(void)
{
	g_signal.errorleft = true;
	ft_puterr("minishell: ");
	ft_puterr(g_signal.current->arg);
	ft_puterr(": No such file or directory\n");
	close(g_signal.file);
	g_signal.file = open("/dev/null", O_RDONLY);
	g_signal.tmpp = dup(g_signal.file);
}

void	redirection_exec_command_pipe(void)
{
	g_signal.current = g_signal.actuel->redir;
	while (g_signal.current)
	{
		if ((!ft_strcmp(g_signal.current->redir, ">"))
			|| (!ft_strcmp(g_signal.current->redir, ">>")))
			redirection_exec_command_pipe2();
		if (!ft_strcmp(g_signal.current->redir, "<"))
		{
			g_signal.file = open(g_signal.current->arg, O_RDONLY);
			if (g_signal.file == -1)
			{
				redirection_exec_command_pipe3();
				break ;
			}
			g_signal.tmpp = dup(g_signal.file);
			close(g_signal.file);
		}
		g_signal.current = g_signal.current->next;
	}	
}

void	error_path_exec_command_pipe(t_all *all)
{
	g_signal.i = -1;
	g_signal.tmp = ft_getenv("PATH", all->headenv);
	g_signal.path = ft_split(g_signal.tmp, ':');
	free(g_signal.tmp);
	g_signal.tmpp = heredoc_non_pipe_command(g_signal.actuel,
			g_signal.tmpp);
	if (!g_signal.path)
	{
		ft_puterr("minishell: ");
		ft_puterr(g_signal.actuel->command[0]);
		ft_puterr(" : No such file or directory\n");
		g_signal.file = open("/dev/null", O_RDONLY);
		g_signal.tmpp = dup(g_signal.file);
	}
	else
		redirection_exec_command_pipe();
}

void	exec_command_pipe3(void)
{		
	if (g_signal.kill == 1)
			exit(0);
	dup2(g_signal.tmpp, STDIN_FILENO);
	if (!g_signal.errorleft && !g_signal.redir)
		dup2(g_signal.fd[1], STDOUT_FILENO);
	if (!g_signal.errorleft)
	{
		if (execve(g_signal.command, g_signal.actuel->command,
				g_signal.env) == -1)
		{
			free(g_signal.command);
			exit(errno);
		}
	}
	free(g_signal.command);
	exit(0);
}
