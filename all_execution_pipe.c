/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_execution_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/08 10:28:04 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal	g_signal;

void	all_builtin_execution_pipe(t_all *all)
{
	pipe(g_signal.fd);
	g_signal.tmpp = heredoc_non_pipe_command(g_signal.actuel, g_signal.tmpp);
	redirection_builtins_pipe();
	file_error_and_close_builtins_pipe(1);
	exec_builtins_pipe(all);
	file_error_and_close_builtins_pipe(2);
}

void	all_slash_command_pipe(t_all *all)
{
	pipe(g_signal.fd);
	g_signal.tmpp = heredoc_non_pipe_command(g_signal.actuel, g_signal.tmpp);
	redirection_slash_command_pipe();
	exec_slash_command(all);
	file_error_and_close_slash_command_pipe(all);
}

void	all_exec_command_pipe(t_all *all)
{
	pipe(g_signal.fd);
	error_path_exec_command_pipe(all);
	if (g_signal.path)
		exec_command_pipe(all);
}

void	all_pipe_execution(t_all *all)
{
	if ((ft_strcmp(g_signal.actuel->command[0], "echo") == 0)
		|| (ft_strcmp(g_signal.actuel->command[0], "cd") == 0)
		|| (ft_strcmp(g_signal.actuel->command[0], "pwd") == 0)
		|| (ft_strcmp(g_signal.actuel->command[0], "exit") == 0)
		|| (ft_strcmp(g_signal.actuel->command[0], "export") == 0)
		|| (ft_strcmp(g_signal.actuel->command[0], "unset") == 0)
		|| (ft_strcmp(g_signal.actuel->command[0], "env") == 0))
		all_builtin_execution_pipe(all);
	else if (ft_strncmp("/", g_signal.actuel->command[0], 1) == 0
		|| ft_strncmp("./", g_signal.actuel->command[0], 2) == 0
		|| ft_strncmp("../", g_signal.actuel->command[0], 3) == 0)
		all_slash_command_pipe(all);
	else
		all_exec_command_pipe(all);
}
