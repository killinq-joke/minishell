/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbuiltins3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:40:27 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/09 23:49:36 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cderror(char *path)
{
	int	error;

	error = errno;
	ft_puterr("cd: ");
	ft_puterr(path);
	ft_puterr(": ");
	if (error == EACCES)
		ft_puterr("Permission denied.\n");
	else if (error == EFAULT)
		ft_puterr("Outside of the process's allocated address space.\n");
	else if (error == EIO)
		ft_puterr("I/O error.\n");
	else if (error == ELOOP)
		ft_puterr("Too many symbolic links were encountered.\n");
	else if (error == ENAMETOOLONG)
		ft_puterr("File name too long\n");
	else if (error == ENOENT)
		ft_puterr("No such file of directory\n");
	else if (error == ENOTDIR)
		ft_puterr("Not a directory\n");
}

void	cd2(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->name, "PWD"))
		{
			if (current->value && ft_strlen(current->value))
				free(current->value);
			current->value = getcwd(NULL, 0);
			if (!current->value)
			{	
				ft_puterr("cd: error retrieving current directory: ");
				ft_puterr("getcwd: cannot access parent directories: ");
				ft_puterr("No such file or directory\n");
			}
		}
		current = current->next;
	}
}

void	cd(t_link *cmd, t_env *env, t_all *all)
{
	char	*path;

	if (splitlen(cmd->command) == 1 || !ft_strcmp("~", cmd->command[1]))
	{
		path = ft_getenv("HOME", env);
		if (!path)
		{
			ft_puterr("cd: HOME not set\n");
			return ;
		}
	}
	else if (ft_strlen(cmd->command[1]))
		path = ft_strdup(cmd->command[1]);
	else
		return ;
	if (chdir(path) == -1)
	{
		all->exit_status = 1;
		cderror(path);
	}
	else
		cd2(env);
	free(path);
}
