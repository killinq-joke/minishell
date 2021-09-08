/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_pipe2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/08 10:29:06 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal	g_signal;

void	exec_command_pipe2(t_all *all)
{
	if (g_signal.path)
	{
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
					exec_command_pipe3();
				dup2(g_signal.out, STDOUT_FILENO);
				waitpid(g_signal.childpid, &all->exit_status, 0);
				if (WEXITSTATUS(all->exit_status))
					all->exit_status = 1;
				free(g_signal.command);
				break ;
			}
			free(g_signal.command);
		}
	}
}	

void	exec_command_pipe(t_all *all)
{
	exec_command_pipe2(all);
	close(g_signal.fd[1]);
	if (!g_signal.errorleft)
		g_signal.tmpp = g_signal.fd[0];
	if (g_signal.co == 0 && g_signal.path)
	{
		all->exit_status = 127;
		ft_puterr("minishell: ");
		ft_puterr(g_signal.actuel->command[0]);
		ft_puterr(": command not found\n");
	}
	freetokens(g_signal.path);
}
