/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_execution_non_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/08 10:27:52 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal	g_signal;

void	all_builtin_execution_non_pipe(t_all *all)
{
	g_signal.tmpp = heredoc_non_pipe_command(g_signal.actuel, g_signal.tmpp);
	redirection_builtins_non_pipe();
	exec_builtins_non_pipe(all);
	exec_builtins_non_pipe_2(all);
}	

void	all_slash_command_non_pipe(t_all *all)
{
	g_signal.tmpp = heredoc_non_pipe_command(g_signal.actuel, g_signal.tmpp);
	if (opendir(g_signal.actuel->command[0]))
		error_path_slash_command(all);
	else
	{
		redirection_slash_command_non_pipe();
		exec_slash_command_non_pipe(all);
	}
}

void	all_exec_command_non_pipe(t_all *all)
{
	g_signal.tmpp = heredoc_non_pipe_command(g_signal.actuel, g_signal.tmpp);
	error_path_exec_command(all);
	redirection_exec_command_non_pipe();
	exec_command_non_pipe(all);
}

void	all_non_pipe_execution(t_all *all)
{
	if (!ft_strcmp(g_signal.actuel->command[0], "echo")
		|| !ft_strcmp(g_signal.actuel->command[0], "cd")
		|| !ft_strcmp(g_signal.actuel->command[0], "pwd")
		|| !ft_strcmp(g_signal.actuel->command[0], "exit")
		|| !ft_strcmp(g_signal.actuel->command[0], "export")
		|| !ft_strcmp(g_signal.actuel->command[0], "unset")
		|| !ft_strcmp(g_signal.actuel->command[0], "env"))
		all_builtin_execution_non_pipe(all);
	else if (ft_strncmp("/", g_signal.actuel->command[0], 1) == 0
		|| ft_strncmp("./", g_signal.actuel->command[0], 2) == 0
		|| ft_strncmp("../", g_signal.actuel->command[0], 3) == 0)
		all_slash_command_non_pipe(all);
	else
	{
		all_exec_command_non_pipe(all);
		freetokens(g_signal.path);
	}
}
