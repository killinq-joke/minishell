/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_pipe2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/16 00:48:24 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal	g_signal;

void	exec_command_pipe2(void)
{
	if (g_signal.path)
	{
		g_signal.co = 0;
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
				free(g_signal.command);
				break ;
			}
			free(g_signal.command);
		}
	}
}	

void	exec_command_pipe(void)
{
	exec_command_pipe2();
	close(g_signal.fd[1]);
	if (g_signal.tmpp != STDIN_FILENO)
		close(g_signal.tmpp);
	if (g_signal.path)
		g_signal.tmpp = g_signal.fd[0];
	if ((g_signal.co == 0 && g_signal.path
			&& ft_strlen(g_signal.actuel->command[0]))
		|| (!ft_strlen(g_signal.actuel->command[0]) && !g_signal.heredocuse))
	{
		ft_puterr("minishell: ");
		ft_puterr(g_signal.actuel->command[0]);
		ft_puterr(": command not found\n");
	}
	freetokens(g_signal.path);
}
