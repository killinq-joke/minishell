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

void	error_path_exec_command(t_all *all)
{
	if (opendir(g_signal.actuel->command[0]))
	{
		all->exit_status = 126;
		ft_puterr("minishell: ");
		ft_puterr(g_signal.actuel->command[0]);
		ft_puterr(" : is a Directory \n");
	}
}	

void	redirection_exec_command_non_pipe2(void)
{
	if (!ft_strcmp(g_signal.current->redir, ">"))
	{
		g_signal.file = open(g_signal.current->arg,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
		dup2(g_signal.file, STDOUT_FILENO);
		close(g_signal.file);
	}
	if (!ft_strcmp(g_signal.current->redir, ">>"))
	{
		g_signal.file = open(g_signal.current->arg,
				O_RDWR | O_CREAT | O_APPEND, 0644);
		dup2(g_signal.file, STDOUT_FILENO);
		close(g_signal.file);
	}
}

void	redirection_exec_command_non_pipe(void)
{
	g_signal.current = g_signal.actuel->redir;
	while (g_signal.current)
	{
		if ((!ft_strcmp(g_signal.current->redir, ">"))
			|| (!ft_strcmp(g_signal.current->redir, ">>")))
			redirection_exec_command_non_pipe2();
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

void	exec_command_non_pipe3(void)
{
	dup2(g_signal.tmpp, STDIN_FILENO);
	if (g_signal.file != -1)
		close(g_signal.file);
	if (execve(g_signal.command,
			g_signal.actuel->command, g_signal.env) == -1)
		exit(errno);
	free(g_signal.command);
}

void	exec_command_non_pipe2(t_all *all)
{
	g_signal.i = -1;
	while (g_signal.path[++g_signal.i])
	{
		g_signal.tmp = ft_joinchar(g_signal.path[g_signal.i], '/');
		g_signal.command = ft_strjoin(g_signal.tmp,
				g_signal.actuel->command[0]);
		free(g_signal.tmp);
		g_signal.fdd = open(g_signal.command, O_RDONLY);
		if (g_signal.fdd != -1 && ft_strlen(g_signal.actuel->command[0]))
		{
			g_signal.co = 1;
			g_signal.childpid = fork();
			if (!g_signal.childpid)
				exec_command_non_pipe3();
			waitpid(g_signal.childpid, &all->exit_status, 0);
			if (WEXITSTATUS(all->exit_status))
				all->exit_status = 1;
			else if (WTERMSIG(all->exit_status))
				all->exit_status = 128 + WTERMSIG(all->exit_status);
			free(g_signal.command);
			break ;
		}
		free(g_signal.command);
	}
}
