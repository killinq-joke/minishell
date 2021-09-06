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

void	error_path_exec_command_pipe(t_all *all)
{
	g_signal.i = -1;
	g_signal.tmp = ft_getenv("PATH", all->headenv);
	g_signal.path = ft_split(g_signal.tmp, ':');
	free(g_signal.tmp);
	if (!g_signal.path)
	{
		ft_puterr("minishell:");
		ft_puterr(g_signal.actuel->command[0]);
		ft_puterr(" : No such file or directory\n");
	}
	else
	{
		g_signal.tmpp = heredoc_non_pipe_command(g_signal.actuel, g_signal.tmpp);
		g_signal.current = g_signal.actuel->redir;
		while (g_signal.current)
		{
			if (!ft_strcmp(g_signal.current->redir, ">"))
			{
				g_signal.redir = true;
				g_signal.file = open(g_signal.current->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
				dup2(g_signal.file, STDOUT_FILENO);
				close(g_signal.file);
			}
			if (!ft_strcmp(g_signal.current->redir, ">>"))
			{
				g_signal.redir = true;
				g_signal.file = open(g_signal.current->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
				dup2(g_signal.file, STDOUT_FILENO);
				close(g_signal.file);
			}
			if (!ft_strcmp(g_signal.current->redir, "<"))
			{
				g_signal.file = open(g_signal.current->arg, O_RDONLY);
				if (g_signal.file == -1)
				{
					g_signal.errorleft = true;
					ft_puterr("minishell: ");
					ft_puterr(g_signal.current->arg);
					ft_puterr(": No such file or directory\n");
					close(g_signal.file);
					g_signal.file = open("/dev/null", O_RDONLY);
					g_signal.tmpp = dup(g_signal.file);
					close(g_signal.file);
					break ;
				}
				g_signal.tmpp = dup(g_signal.file);
				close(g_signal.file);
			}
			g_signal.current = g_signal.current->next;
		}	
	}
}

void	exec_command_pipe(t_all *all)
{
	while (g_signal.path[++g_signal.i])
	{
		g_signal.tmp = ft_joinchar(g_signal.path[g_signal.i], '/');
		g_signal.command = ft_strjoin(g_signal.tmp, g_signal.actuel->command[0]);
		free(g_signal.tmp);
		g_signal.fdd = open(g_signal.command, O_RDONLY);
		if (g_signal.fdd != -1 && ft_strlen(g_signal.actuel->command[0]))
		{
			g_signal.co = 1;
			g_signal.childpid = fork();
			if (!g_signal.childpid)
			{
				dup2(g_signal.tmpp, STDIN_FILENO);
				if (!g_signal.errorleft && !g_signal.redir)
					dup2(g_signal.fd[1], STDOUT_FILENO);
				if (!g_signal.errorleft)
				{
					if (execve(g_signal.command, g_signal.actuel->command, g_signal.env) == -1)
					{
						free(g_signal.command);
						exit(errno);
					}
				}
				free(g_signal.command);
				exit(0);
			}
			dup2(g_signal.out, STDOUT_FILENO);
			waitpid(g_signal.childpid, &all->exit_status, 0);
			if (WEXITSTATUS(all->exit_status))
				all->exit_status = 1;
			free(g_signal.command);
			break ;
		}
		free(g_signal.command);
	}
	close(g_signal.fd[1]);
	if (!g_signal.errorleft)
		g_signal.tmpp = g_signal.fd[0];
	if (g_signal.co == 0)
	{
		all->exit_status = 127;
		ft_puterr("minishell: ");
		ft_puterr(g_signal.actuel->command[0]);
		ft_puterr(": command not found\n");
	}
	freetokens(g_signal.path);
}