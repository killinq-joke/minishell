/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_non_pipe2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/08 10:29:01 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal	g_signal;

void	exec_null_path(void)
{
	ft_puterr("minishell: ");
	ft_puterr(g_signal.actuel->command[0]);
	ft_puterr(" : No such file or directory\n");
	dup2(g_signal.out, STDOUT_FILENO);
}

void	exec_command_non_pipe(t_all *all)
{
	g_signal.tmp = ft_getenv("PATH", all->headenv);
	g_signal.path = ft_split(g_signal.tmp, ':');
	free(g_signal.tmp);
	if (g_signal.file == -1)
	{
	}
	if (!g_signal.path)
		exec_null_path();
	else
	{
		exec_command_non_pipe2(all);
		if (g_signal.file != -1)
			dup2(g_signal.out, STDOUT_FILENO);
		if (g_signal.co == 0)
		{
			all->exit_status = 127;
			ft_puterr("minishell: ");
			ft_puterr(g_signal.actuel->command[0]);
			ft_puterr(": command not found\n");
		}
	}
}
