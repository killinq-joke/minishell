/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 20:01:37 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/12 21:40:32y ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	give_good_path(t_all *all)
{
	if ((ft_strcmp(all->headcmd->command[0], "echo") == 0)
		|| (ft_strcmp(all->headcmd->command[0], "cd") == 0)
		|| (ft_strcmp(all->headcmd->command[0], "pwd") == 0)
		|| (ft_strcmp(all->headcmd->command[0], "exit") == 0)
		|| (ft_strcmp(all->headcmd->command[0], "export") == 0)
		|| (ft_strcmp(all->headcmd->command[0], "unset") == 0)
		|| (ft_strcmp(all->headcmd->command[0], "env") == 0))
		execbuiltins(all);
	else
		execcmd(all->headcmd);
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

int		execplusredir(t_link *cmd)
{
	//if (!ft_strcmp(">", cmd->command[1]))
	//{
		
	//}
	if (execve(cmd->command[0], cmd->command, NULL) == -1)
		return (-1);
	return (0);
}

void	execcmd(t_link *cmd)
{
	int		i;
	char	**path;
	char	*tmp;

	if (good_path_for_cmd(cmd) == false)
	{
		if (fork() == 0)
			if (execve(cmd->command[0], cmd->command, NULL) == -1)
				exit(0);
	}
	else
	{
		i = -1;
		path = ft_split(cmd->path_bis, ':');
		while (path[++i])
		{
			if (fork() == 0)
			{
				tmp = path[i];
				path[i] = ft_joinchar(path[i], '/');
				free(tmp);
				tmp = cmd->command[0];
				cmd->command[0] = ft_strjoin(path[i], cmd->command[0]);
				free(tmp);
				//if (execplusredir(cmd) == -1)
				if (execve(cmd->command[0], cmd->command, NULL) == -1)
					exit(0);
			}
		}
	}
}
