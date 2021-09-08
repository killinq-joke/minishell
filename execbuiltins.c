/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbuiltins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:40:27 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/06 15:46:53 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	isdashn(char *str)
{
	int	i;

	i = 2;
	if (!ft_strncmp(str, "-n", 2))
	{
		while (str[i] == 'n')
			i++;
		if (str[i])
			return (false);
	}
	else
		return (false);
	return (true);
}

void	echo(t_link *cmd)
{
	t_bool	nl;
	int		i;

	nl = true;
	i = 1;
	while (cmd->command[i] && isdashn(cmd->command[i]))
	{
		nl = false;
		i++;
	}
	while (cmd->command[i])
	{
		ft_putstr(cmd->command[i]);
		if (cmd->command[i + 1] && ft_strlen(cmd->command[i]))
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
		{	
			printf("Read or search permission was denied");
			printf(" for a component of the pathname\n");
		}
		else if (errno == ERANGE)
		{	
			printf("The size argument is greater than zero ");
			printf("but smaller than the length of the pathname plus 1.\n");
		}
	}
}

void	exportt(char **command, t_env *env)
{
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
}

void	execbuiltins(t_all *all)
{
	if (ft_strcmp(all->headcmd->command[0], "pwd") == 0)
		pwd();
	if (ft_strcmp(all->headcmd->command[0], "echo") == 0)
		echo(all->headcmd);
	if (ft_strcmp(all->headcmd->command[0], "env") == 0)
		printenv(all->headenv);
	if (ft_strcmp(all->headcmd->command[0], "cd") == 0)
		cd(all->headcmd, all->headenv, all);
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
