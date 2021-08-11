/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 20:01:37 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/11 20:04:41 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	give_good_path(t_link *cmd)
{
	if ((ft_strcmp(cmd->command[0], "echo") == 0)
		|| (ft_strcmp(cmd->command[0], "cd") == 0)
		|| (ft_strcmp(cmd->command[0], "pwd") == 0)
		|| (ft_strcmp(cmd->command[0], "exit") == 0)
		|| (ft_strcmp(cmd->command[0], "export") == 0)
		|| (ft_strcmp(cmd->command[0], "unset") == 0)
		|| (ft_strcmp(cmd->command[0], "env") == 0))
		execbuiltin(cmd);
	else
		execcmd(cmd);
}

t_bool	good_path_for_cmd(t_link *cmd)
{
	if ((ft_strncmp("/", cmd->command[0], 1))
		|| (ft_strncmp("./", cmd->command[0], 2))
		|| (ft_strncmp("../", cmd->command[0], 3)))
		return (true);
	else
		return (false);
}

void	execcmd(t_link *cmd)
{
	int	i;

	if (good_path_for_cmd(cmd) == true)
	{
		if (fork() == 0)
			if (execve(cmd->command[0], cmd->command, NULL) == -1)
				exit(0);
		wait(0);
	}
	else
	{
		i = -1;
		while (cmd->path[++i])
		{
			if (fork() == 0)
				if (execve(ft_strcat(cmd->path[i], \
					cmd->command[0]), cmd->command, NULL) == -1)
					exit(0);
			wait(0);
		}
	}
}
