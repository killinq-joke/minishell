/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbuiltins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:40:27 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/14 13:59:26 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_link *cmd)
{
	t_bool	nl;
	int		i;

	nl = true;
	i = 1;
	while (cmd->command[i] && !ft_strcmp(cmd->command[i], "-n"))
	{
		nl = false;
		i++;
	}
	while (cmd->command[i])
	{
		ft_putstr(cmd->command[i]);
		if (cmd->command[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (nl)
		ft_putchar('\n');
}

void	pwd(void)
{
	char	*workingdir;

	workingdir = getcwd(NULL, 0);
	if (workingdir)
		ft_putstrnl(workingdir);
	if (errno)
	{
		if (errno == EACCES)
			printf("Read or search permission was denied for a component of the pathname\n");
		else if (errno == EINVAL)
			printf("The size argument is zero.\n");
		else if (errno == ERANGE)
			printf("The size argument is greater than zero but smaller than the length of the pathname plus 1.\n");
	}
}

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

void	cd(t_link *cmd)
{
	int		len;
	char	*path;

	len = linklen(cmd);
	if (!len)
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_puterr("cd: HOME not set\n");
			return ;
		}
	}
	else
		path = cmd->command[1];
	if (chdir(path) == -1)
		cderror(path);
}

char	*getvalue(const char *name)
{
	int	i;
	int	len;

	if (!name)
		return (ft_strdup(""));
	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	if (name[i] == '=')
		i++;
	else
		return (NULL);
	len = i;
	while (name[len])
		len++;
	return (ft_substr(name, i, len));
}

void	export(char **command, t_env *env)
{
	int		i;
	t_env	*current;

	current = env;
	if (splitlen(command) == 1)
	{
		while (current)
		{
			if (current->value)
				printf("declare -x %s=\"%s\"\n", current->name, current->value);
			else
				printf("declare -x %s\n", current->name);
			current = current->next;
		}
	}
	else
	{
		while (current->next)
			current = current->next;
		i = 1;
		while (command[i])
		{
			current->next = envinit(getname(command[i]), getvalue(command[i]));
			current = current->next;
			i++;
		}
	}
}

void	freeenv(t_env *node)
{
	if (node->value)
		free(node->value);
	if (node->name)
		free(node->name);
	free(node);
}

void	unset(char **namelist, t_all *all)
{
	int		i;
	int		isfirst;
	t_env	*current;
	//t_env	*prev;
	//t_env	*tmp;

	isfirst = true;
	current = all->headenv;
	if (!namelist || !all->headenv)
		return ;
	if (envlen(all->headenv) == 1)
		freeenv(all->headenv);
	while (current)
	{
		i = 0;
		while (namelist[i])
		{
			if (isfirst && !ft_strcmp(current->name, namelist[i]))
			{
				all->headenv = current->next;
				//freeenv(current);
				return ;
			}
			else if (!ft_strcmp(current->name, namelist[i]))
			{
				return ;
			}
			i++;
		}
		current = current->next;
		isfirst = false;
	}
}

void	execbuiltins(t_all *all)
{
	if (ft_strcmp(all->headcmd->command[0], "pwd") == 0)
		pwd();
	if (ft_strcmp(all->headcmd->command[0], "echo") == 0)
		echo(all->headcmd);
	if (ft_strcmp(all->headcmd->command[0], "env") == 0)
	{
		printf("salut\n");
		printenv(all->headenv);
	}
	if (ft_strcmp(all->headcmd->command[0], "cd") == 0)
		cd(all->headcmd);
	if (ft_strcmp(all->headcmd->command[0], "export") == 0)
		export(all->headcmd->command, all->headenv);
	if (ft_strcmp(all->headcmd->command[0], "unset") == 0)
		unset(all->headcmd->command, all);
	if (ft_strcmp(all->headcmd->command[0], "exit") == 0)
	{
		ft_putstrnl("exit");
		exit(0);
	}
}
