/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 19:57:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/08/16 09:43:51by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_all *all, t_link *cmd)
{
	t_link	*actuel;
	t_link	*actual;
	t_all	*element;
	int		fd[2];
	int		tmpp = STDIN_FILENO;
	element = all;
	actuel = cmd;
	actual = cmd;
	int taille = 0;
	while (actual)
	{
		taille++;
		actual = actual->next;
	}
	while (actuel)
	{
		if (actuel->next)
		{
			if ((ft_strcmp(actuel->command[0], "echo") == 0) || (ft_strcmp(actuel->command[0], "cd") == 0) || (ft_strcmp(actuel->command[0], "pwd") == 0) || (ft_strcmp(actuel->command[0], "exit") == 0) || (ft_strcmp(actuel->command[0], "export") == 0) || (ft_strcmp(actuel->command[0], "unset") == 0) || (ft_strcmp(actuel->command[0], "env") == 0))
			{
				pipe(fd);
				if (fork() == 0)
				{
					dup2(tmpp, STDIN_FILENO);
					dup2(fd[1], STDOUT_FILENO);
					if (ft_strcmp(actuel->command[0], "pwd") == 0)
						pwd();
					if (ft_strcmp(actuel->command[0], "echo") == 0)
						echo(actuel);
					if (ft_strcmp(actuel->command[0], "env") == 0)
						printenv(element->headenv);
					if (ft_strcmp(actuel->command[0], "cd") == 0)
						cd(actuel, element->headenv);
					if (ft_strcmp(actuel->command[0], "export") == 0)
						export(actuel->command, element->headenv);
					if (ft_strcmp(actuel->command[0], "unset") == 0)
						unset(actuel->command, element);
					if (ft_strcmp(actuel->command[0], "exit") == 0)
						;
					exit(1);
				}
				close(fd[1]);
				tmpp = fd[0];
			}
			else if (ft_strncmp("/", actuel->command[0], 1) == 0 || ft_strncmp("./", actuel->command[0], 2) == 0 || ft_strncmp("../", actuel->command[0], 3) == 0)
			{
				pipe(fd);
				if (fork() == 0)
				{
					dup2(tmpp, STDIN_FILENO);
					dup2(fd[1], STDOUT_FILENO);
					if (execve(actuel->command[0], actuel->command, NULL) == -1)
						exit (printf("bonjour\n"));
				}
				close(fd[1]);
				tmpp = fd[0];
			}
			else
			{
				pipe(fd);
				int		i;
				char	**path;
				char	*tmp;
				char	*command;
				int co = 0;
				int fdd;
				i = -1;
				path = ft_split(ft_getenv("PATH", all->headenv), ':');
				if (!path)
						printf("bash: %s: No such file or directory\n", actuel->command[0]);
				else 
				{
					while (path[++i])
					{
						tmp = ft_joinchar(path[i], '/');
						command = ft_strjoin(tmp, actuel->command[0]);	
						fdd = open(command, O_RDONLY);
						if (fdd != -1)
						{
							co = 1;
							if (fork() == 0)
							{
								dup2(tmpp, STDIN_FILENO);
								dup2(fd[1], STDOUT_FILENO);;
								if (execve(command, actuel->command, NULL) == -1)
								exit (0);
							}
							break;
						}
					}
					close(fd[1]);
					tmpp = fd[0];
					if (co == 0)
						printf("bash: %s: command not found\n", actuel->command[0]);
				}
			}
		}	
		else
		{
			if ((ft_strcmp(actuel->command[0], "echo") == 0) || (ft_strcmp(actuel->command[0], "cd") == 0) || (ft_strcmp(actuel->command[0], "pwd") == 0) || (ft_strcmp(actuel->command[0], "exit") == 0) || (ft_strcmp(actuel->command[0], "export") == 0) || (ft_strcmp(actuel->command[0], "unset") == 0) || (ft_strcmp(actuel->command[0], "env") == 0))
			{
				if ((ft_strcmp(actuel->command[0], "export") == 0) && (taille == 1))
					export(actuel->command, element->headenv);
				else if ((ft_strcmp(actuel->command[0], "unset") == 0) && (taille == 1))
					unset(actuel->command, element);
				else if(ft_strcmp(actuel->command[0], "exit") == 0 && (taille == 1))
					exit(0);
				else if (ft_strcmp(actuel->command[0], "cd") == 0)
					cd(actuel, element->headenv);
				else if (ft_strcmp(actuel->command[0], "pwd") == 0)
					pwd();
				else
				{
					if (fork() == 0)
					{
						dup2(tmpp, STDIN_FILENO);
						if (ft_strcmp(actuel->command[0], "echo") == 0)
							echo(actuel);
						if (ft_strcmp(actuel->command[0], "env") == 0)
							printenv(element->headenv);
						if (ft_strcmp(actuel->command[0], "export") == 0)
							exportt(actuel->command, element->headenv);
						exit(1);
					}
				}
			}
			else if (ft_strncmp("/", actuel->command[0], 1) == 0 || ft_strncmp("./", actuel->command[0], 2) == 0 || ft_strncmp("../", actuel->command[0], 3) == 0)
			{
				if (fork() == 0)
				{
					dup2(tmpp, STDIN_FILENO);
					if (execve(actuel->command[0], actuel->command, NULL) == -1)
						exit (0);
				}
			}
			else
			{
				int		i;
				char	**path;
				char	*tmp;
				char	*command;
				int fd;
				int co = 0;
				i = -1;
				path = ft_split(ft_getenv("PATH", all->headenv), ':');
				if (!path)
						printf("bash: %s: No such file or directory\n", actuel->command[0]);
				else
				{	
					while (path[++i])
					{
						tmp = ft_joinchar(path[i], '/');
						command = ft_strjoin(tmp, actuel->command[0]);	
						fd = open(command, O_RDONLY);
						if (fd != -1)
						{
							co = 1;
							if (fork() == 0)
							{
								dup2(tmpp, STDIN_FILENO);
								if (execve(command, actuel->command, NULL) == -1)
									exit (0);
							}
							break ;
						}
					}				
					if (co == 0)
						printf("bash: %s: command not found\n", actuel->command[0]);
				}
			}
		}
		actuel = actuel->next;
	}
}
