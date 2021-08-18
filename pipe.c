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

//void	minishell(t_link *cmd)
//{
//	int		fd[2];
//	int		tmp;
//	t_link	*actuel;

//	actuel = cmd;
//	while (actuel)
//	{
//		if (actuel->next)
//		{
//			pipe(fd);
//			dup2(tmp, STDIN_FILENO);
//			dup2(fd[1], STDOUT_FILENO);
//			give_good_path(all);
//		}
//		else
//		{
//			dup2(tmp, STDIN_FILENO);
//			give_good_path(all);
//		}
//		actuel = actuel->next;
//	}
//}
/*
void	minishell(t_all *all, t_link *cmd)
{
	t_link	*actuel;
	int		fd[2];
	int		tmp;

	(void)all;
	actuel = cmd;
	while (actuel)
	{
		if (actuel->next)
		{
			pipe(fd);
			if (fork() == 0)
			{
				dup2(tmp, STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				give_good_path(all);
			}
			close(fd[1]);
			tmp = fd[0];
		}
		else
		{
			if (fork() == 0)
			{
				dup2(tmp, STDIN_FILENO);
				give_good_path(all);
			}
		}
		wait(0);
		actuel = actuel->next;
	}
}
*/



void	minishell(t_all *all, t_link *cmd)
{
	t_link	*actuel;
	int		fd[2];
	int		tmpp;

	(void)all;
	actuel = cmd;
	while (actuel)
	{
		if (actuel->next)
		{
			if ((ft_strcmp(actuel->command[0], "echo") == 0) || (ft_strcmp(actuel->command[0], "cd") == 0) || (ft_strcmp(actuel->command[0], "pwd") == 0) || (ft_strcmp(actuel->command[0], "exit") == 0) || (ft_strcmp(actuel->command[0], "export") == 0) || (ft_strcmp(actuel->command[0], "unset") == 0) || (ft_strcmp(actuel->command[0], "env") == 0))
			{
				pipe(fd);
				if (fork() == 0)
				{
					dup2(fd[1], STDOUT_FILENO);
					dup2(tmpp, STDIN_FILENO);
					execbuiltins(all);
					exit(0);
				}
				wait(0);
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
				i = 0;
				path = ft_split(ft_getenv("PATH", all->headenv), ':');
				while (path[i])
				{
					if (fork() == 0)
					{
						dup2(fd[1], STDOUT_FILENO);
						dup2(tmpp, STDIN_FILENO);
						tmp = ft_joinchar(path[i], '/');
						command = ft_strjoin(tmp, actuel->command[0]);
						if (execve(command, actuel->command, NULL) == -1)
							exit (0);
					}
					wait(0);
					i++;
				}
				close(fd[1]);
				tmpp = fd[0];
			}
		}	
		else 
		{
			if ((ft_strcmp(actuel->command[0], "echo") == 0) || (ft_strcmp(actuel->command[0], "cd") == 0) || (ft_strcmp(actuel->command[0], "pwd") == 0) || (ft_strcmp(actuel->command[0], "exit") == 0) || (ft_strcmp(actuel->command[0], "export") == 0) || (ft_strcmp(actuel->command[0], "unset") == 0) || (ft_strcmp(actuel->command[0], "env") == 0))
			{
				if (fork() == 0)
				{
					dup2(tmpp, STDIN_FILENO);
					execbuiltins(all);
					exit(0);
				}
				wait(0);
			}
			else 
			{
				int		i;
				char	**path;
				char	*tmp;
				char	*command;
				i = 0;
				path = ft_split(ft_getenv("PATH", all->headenv), ':');
				while (path[i])
				{
					if (fork() == 0)
					{
						dup2(tmpp, STDIN_FILENO);
						tmp = ft_joinchar(path[i], '/');
						command = ft_strjoin(tmp, actuel->command[0]);
						if (execve(command, actuel->command, NULL) == -1)
							exit (0);
					}
					wait(0);
					i++;
				}	
			}
		}
		actuel = actuel->next;
	}
}