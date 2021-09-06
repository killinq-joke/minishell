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

void	redirection_builtins_non_pipe(void)
{
	g_signal.current = g_signal.actuel->redir;
	while (g_signal.current)
	{
		if (!ft_strcmp(g_signal.current->redir, ">"))
		{
			g_signal.redir = true;
			g_signal.file = open(g_signal.current->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(g_signal.file, STDOUT_FILENO);
		}
		if (!ft_strcmp(g_signal.current->redir, ">>"))
		{
			g_signal.redir = true;
			g_signal.file = open(g_signal.current->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(g_signal.file, STDOUT_FILENO);
		}
		if (!ft_strcmp(g_signal.current->redir, "<"))
		{
			g_signal.errorleft = true;
			g_signal.file = open(g_signal.current->arg, O_RDONLY);
			if (g_signal.file == -1)
				break ;
		}
		g_signal.current = g_signal.current->next;
	}	
}

void	exec_builtins_non_pipe(t_all *all)
{
	if (g_signal.file == -1)
	{
		ft_puterr("minishell: ");
		ft_puterr(g_signal.current->arg);
		ft_puterr(": No such file or directory\n");
	}
	else if ((ft_strcmp(g_signal.actuel->command[0], "unset") == 0)
		&& (g_signal.taille == 1))
		unset(g_signal.actuel->command, all);
	else if (ft_strcmp(g_signal.actuel->command[0], "exit") == 0
		&& (g_signal.taille == 1))
	{
		ft_putstr("exit\n");
		if (g_signal.actuel->command[1])
		{
			if (ft_strisnum(g_signal.actuel->command[1]) == 1)
				exit(ft_atoi(g_signal.actuel->command[1]));
			else
			{
				ft_puterr("minishell: ");
				ft_puterr(g_signal.actuel->command[1]);
				ft_puterr(": numeric argument required\n");
			}
		}
		exit(0);
	}
}

void	exec_builtins_non_pipe_2(t_all *all)
{
	if (ft_strcmp(g_signal.actuel->command[0], "cd") == 0)
		cd(g_signal.actuel, all->headenv, all);
	else if (ft_strcmp(g_signal.actuel->command[0], "export") == 0)
		export(g_signal.actuel->command, all->headenv);
	else
	{
		g_signal.childpid = fork();
		if (!g_signal.childpid)
		{
			if (g_signal.file != -1)
				close(g_signal.file);
			dup2(g_signal.tmpp, STDIN_FILENO);
			if (ft_strcmp(g_signal.actuel->command[0], "echo") == 0)
				echo(g_signal.actuel);
			if (ft_strcmp(g_signal.actuel->command[0], "env") == 0)
				printenv(all->headenv);
			if (ft_strcmp(g_signal.actuel->command[0], "pwd") == 0)
				pwd();
			if (g_signal.file != -1)
				close(g_signal.file);
			exit(1);
		}
		if (g_signal.file != -1)
			close(g_signal.file);
	}
	dup2(g_signal.out, STDOUT_FILENO);
}
