/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slash_command_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/11 22:36:07 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal	g_signal;

void	exec_slash_command(void)
{
	g_signal.fdd = open(g_signal.actuel->command[0], O_RDONLY);
	if (g_signal.fdd != -1)
	{
		g_signal.childpid = fork();
		if (!g_signal.childpid)
		{
			close(g_signal.fd[0]);
			if (g_signal.kill == 1)
				exit(0);
			dup2(g_signal.tmpp, STDIN_FILENO);
			if (!g_signal.errorleft && !g_signal.redir)
				dup2(g_signal.fd[1], STDOUT_FILENO);
			close(g_signal.fd[1]);
			if (g_signal.errorleft)
			{
				dup2(g_signal.fd[1], g_signal.tmpp);
				exit(0);
			}
			if (execve(g_signal.actuel->command[0],
					g_signal.actuel->command, g_signal.env) == -1)
				exit(errno);
			exit(0);
		}
		dup2(g_signal.out, STDOUT_FILENO);
	}
}

void	file_error_and_close_slash_command_pipe(void)
{
	close(g_signal.fd[1]);
	if (g_signal.tmpp != 0)
		close (g_signal.tmpp);
	g_signal.tmpp = g_signal.fd[0];
	if (WIFEXITED(g_signal.childpid))
	{
		ft_puterr("minishell: ");
		ft_puterr(g_signal.actuel->command[0]);
		ft_puterr(": No such file or directory\n");
	}
}

void	redirection_slash_command_pipe_2(void)
{
	if (!ft_strcmp(g_signal.current->redir, ">"))
	{
		g_signal.redir = true;
		g_signal.file = open(g_signal.current->arg,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(g_signal.file, STDOUT_FILENO);
		close(g_signal.file);
	}
	if (!ft_strcmp(g_signal.current->redir, ">>"))
	{
		g_signal.redir = true;
		g_signal.file = open(g_signal.current->arg,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(g_signal.file, STDOUT_FILENO);
		close(g_signal.file);
	}	
}

void	redirection_slash_command_pipe_3(void)
{
	g_signal.errorleft = true;
	ft_puterr("minishell: ");
	ft_puterr(g_signal.current->arg);
	ft_puterr(": No such file or directory\n");
	close(g_signal.file);
	g_signal.file = open("/dev/null", O_RDONLY);
	g_signal.tmpp = dup(g_signal.file);
	close(g_signal.file);
}

void	redirection_slash_command_pipe(void)
{
	g_signal.current = g_signal.actuel->redir;
	while (g_signal.current)
	{
		if ((!ft_strcmp(g_signal.current->redir, ">"))
			|| (!ft_strcmp(g_signal.current->redir, ">>")))
			redirection_slash_command_pipe_2();
		if (!ft_strcmp(g_signal.current->redir, "<"))
		{
			g_signal.file = open(g_signal.current->arg, O_RDONLY);
			if (g_signal.file == -1)
			{
				redirection_slash_command_pipe_3();
				break ;
			}
			g_signal.tmpp = dup(g_signal.file);
			close(g_signal.file);
		}
		g_signal.current = g_signal.current->next;
	}	
}
