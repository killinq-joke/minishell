/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_non_pipe2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/08 10:28:17 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_signal	g_signal;

void	exec_builtins_non_pipe_2(t_all *all)
{
	if (ft_strcmp(g_signal.actuel->command[0], "cd") == 0)
		cd(g_signal.actuel, all->headenv, all);
	else if (ft_strcmp(g_signal.actuel->command[0], "export") == 0)
		export(g_signal.actuel->command, all->headenv);
	else
		exec_builtins_non_pipe_3(all);
	dup2(g_signal.out, STDOUT_FILENO);
}
