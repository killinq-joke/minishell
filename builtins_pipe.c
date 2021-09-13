/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/11 22:34:35 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal	g_signal;

void	redirection_builtins_pipe(void)
{
	g_signal.current = g_signal.actuel->redir;
	while (g_signal.current)
	{
		if (!ft_strcmp(g_signal.current->redir, ">"))
		{
			g_signal.redir = true;
			g_signal.file = open(g_signal.current->arg,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
		}
		if (!ft_strcmp(g_signal.current->redir, ">>"))
		{
			g_signal.redir = true;
			g_signal.file = open(g_signal.current->arg,
					O_RDWR | O_CREAT | O_APPEND, 0644);
		}
		if (!ft_strcmp(g_signal.current->redir, "<"))
		{
			g_signal.file = open(g_signal.current->arg, O_RDONLY);
			if (g_signal.file == -1)
				break ;
		}
		g_signal.current = g_signal.current->next;
	}
}

void	file_error_and_close_builtins_pipe(int nb)
{
	if (nb == 1)
	{	
		if (g_signal.file == -1)
		{
			g_signal.errorleft = true;
			g_signal.file = open("/dev/null", O_RDONLY);
			dup2(g_signal.file, STDOUT_FILENO);
			ft_puterr("minishell: ");
			ft_puterr(g_signal.current->arg);
			ft_puterr(": No such file or directory\n");
		}
	}
	else if (nb == 2)
	{
		if (g_signal.file != -1)
			close(g_signal.file);
		dup2(g_signal.out, STDOUT_FILENO);
		close(g_signal.fd[1]);
		g_signal.tmpp = g_signal.fd[0];
	}
}

void	exec_builtins_pipe(t_all *all)
{
	g_signal.childpid = fork();
	if (!g_signal.childpid)
	{
		if (g_signal.kill == 1)
			exit(0);
		dup2(g_signal.tmpp, STDIN_FILENO);
		if (!g_signal.errorleft && !g_signal.redir)
			dup2(g_signal.fd[1], STDOUT_FILENO);
		else if (g_signal.redir)
			dup2(g_signal.file, STDOUT_FILENO);
		if (ft_strcmp(g_signal.actuel->command[0], "pwd") == 0)
			pwd();
		if (ft_strcmp(g_signal.actuel->command[0], "echo") == 0)
			echo(g_signal.actuel);
		if (ft_strcmp(g_signal.actuel->command[0], "env") == 0)
			printenv(all->headenv);
		if (ft_strcmp(g_signal.actuel->command[0], "cd") == 0)
			cd(g_signal.actuel, all->headenv, all);
		if (ft_strcmp(g_signal.actuel->command[0], "export") == 0)
			export(g_signal.actuel->command, all->headenv);
		if (ft_strcmp(g_signal.actuel->command[0], "unset") == 0)
			unset(g_signal.actuel->command, all);
		exit(0);
	}
}
