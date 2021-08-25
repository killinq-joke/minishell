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

extern t_signal g_signal;

void	minishell(t_all *all, t_link *cmd)
{
	t_link	*actuel;
	int		fd[2];
	int		tmpp = STDIN_FILENO;
	int		taille;

	taille = linklen(cmd);
	actuel = cmd;
	all->exit_status = 0;
	echo_control_seq(true);
	while (actuel)
	{
		if (actuel->next)
		{
			if ((ft_strcmp(actuel->command[0], "echo") == 0) || (ft_strcmp(actuel->command[0], "cd") == 0) || (ft_strcmp(actuel->command[0], "pwd") == 0) || (ft_strcmp(actuel->command[0], "exit") == 0) || (ft_strcmp(actuel->command[0], "export") == 0) || (ft_strcmp(actuel->command[0], "unset") == 0) || (ft_strcmp(actuel->command[0], "env") == 0))
			{
				pipe(fd);
				g_signal.childpid = fork();
				if (!g_signal.childpid)
				{
					dup2(tmpp, STDIN_FILENO);
					dup2(fd[1], STDOUT_FILENO);
					if (ft_strcmp(actuel->command[0], "pwd") == 0)
						pwd();
					if (ft_strcmp(actuel->command[0], "echo") == 0)
						echo(actuel);
					if (ft_strcmp(actuel->command[0], "env") == 0)
						printenv(all->headenv);
					if (ft_strcmp(actuel->command[0], "cd") == 0)
						cd(actuel, all->headenv);
					if (ft_strcmp(actuel->command[0], "export") == 0)
						export(actuel->command, all->headenv);
					if (ft_strcmp(actuel->command[0], "unset") == 0)
						unset(actuel->command, all);
					if (ft_strcmp(actuel->command[0], "exit") == 0)
						;
					exit(0);
				}
				close(fd[1]);
				tmpp = fd[0];
			}
			else if (ft_strncmp("/", actuel->command[0], 1) == 0 || ft_strncmp("./", actuel->command[0], 2) == 0 || ft_strncmp("../", actuel->command[0], 3) == 0)
			{
				pipe(fd);
				g_signal.childpid = fork();
				if (opendir(actuel->command[0]))
				{
					all->exit_status = 126;
					printf("bash :%s : is a Directory \n", actuel->command[0]);
				}
				else
				{
					if (!g_signal.childpid)
					{
						dup2(tmpp, STDIN_FILENO);
						dup2(fd[1], STDOUT_FILENO);
						if (execve(actuel->command[0], actuel->command, NULL) == -1)
							exit(errno);
					}
					close(fd[1]);
					tmpp = fd[0];
					waitpid(g_signal.childpid, &all->exit_status, 0);
					if (WIFEXITED(g_signal.childpid))
						all->exit_status = 127;
				}
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
				t_redir	*current;

				i = -1;
				path = ft_split(ft_getenv("PATH", all->headenv), ':');
				if (!path)
					printf("bash: %s: No such file or directory\n", actuel->command[0]);
				else 
				{
					current = actuel->redir;
					while (current)
					{
						if (!ft_strcmp(current->redir, "<<"))
						{
							char	*line;
							char	*tmp;

							tmpp = open("/tmp/hd", O_CREAT | O_TRUNC | O_WRONLY, 0600);
							line = readline("> ");
							printf("f\n");
							while (line && ft_strcmp(line, current->arg))
							{
								printf("a\n");
								write(tmpp, line, ft_strlen(line));
								write(tmpp, "\n", 1);
								tmp = line;
								line = readline("> ");
								free(tmp);
							}
							free(line);
							tmpp = open("/tmp/hd", O_RDONLY);
							unlink("/tmp/hd");
						}
						current = current->next;
					}
					while (path[++i])
					{
						tmp = ft_joinchar(path[i], '/');
						command = ft_strjoin(tmp, actuel->command[0]);	
						fdd = open(command, O_RDONLY);
						if (fdd != -1)
						{
							co = 1;
							g_signal.childpid = fork();
							if (!g_signal.childpid)
							{
								dup2(tmpp, STDIN_FILENO);
								dup2(fd[1], STDOUT_FILENO);;
								if (execve(command, actuel->command, NULL) == -1)
									exit (errno);
							}
							waitpid(g_signal.childpid, &all->exit_status, 0);
							if (WEXITSTATUS(all->exit_status))
								all->exit_status = 1;
							break;
						}
					}
					close(fd[1]);
					tmpp = fd[0];
					if (co == 0)
					{
						all->exit_status = 127;
						printf("bash: %s: command not found\n", actuel->command[0]);
					}
				}
			}
		}	
		else
		{
			if ((ft_strcmp(actuel->command[0], "echo") == 0) || (ft_strcmp(actuel->command[0], "cd") == 0) || (ft_strcmp(actuel->command[0], "pwd") == 0) || (ft_strcmp(actuel->command[0], "exit") == 0) || (ft_strcmp(actuel->command[0], "export") == 0) || (ft_strcmp(actuel->command[0], "unset") == 0) || (ft_strcmp(actuel->command[0], "env") == 0))
			{
				t_redir	*current;

				current = actuel->redir;
				while (current)
				{
					if (!ft_strcmp(current->redir, "<<"))
					{
						char	*line;
						char	*tmp;

						tmpp = open("/tmp/hd", O_CREAT | O_TRUNC | O_WRONLY, 0600);
						line = readline("> ");
						printf("b\n");
						while (line && ft_strcmp(line, current->arg))
						{
							write(tmpp, line, ft_strlen(line));
							write(tmpp, "\n", 1);
							tmp = line;
							line = readline("> ");
							free(tmp);
						}
						free(line);
						tmpp = open("/tmp/hd", O_RDONLY);
						unlink("/tmp/hd");
					}
					current = current->next;
				}
				if ((ft_strcmp(actuel->command[0], "export") == 0) && (taille == 1))
					export(actuel->command, all->headenv);
				else if ((ft_strcmp(actuel->command[0], "unset") == 0) && (taille == 1))
					unset(actuel->command, all);
				else if(ft_strcmp(actuel->command[0], "exit") == 0 && (taille == 1))
					exit(0);
				else if (ft_strcmp(actuel->command[0], "cd") == 0)
					cd(actuel, all->headenv);
				else if (ft_strcmp(actuel->command[0], "pwd") == 0)
					pwd();
				else
				{
					g_signal.childpid = fork();
					if (!g_signal.childpid)
					{
						dup2(tmpp, STDIN_FILENO);
						if (ft_strcmp(actuel->command[0], "echo") == 0)
							echo(actuel);
						if (ft_strcmp(actuel->command[0], "env") == 0)
							printenv(all->headenv);
						if (ft_strcmp(actuel->command[0], "export") == 0)
							exportt(actuel->command, all->headenv);
						exit(1);
					}
				}
			}
			else if (ft_strncmp("/", actuel->command[0], 1) == 0 || ft_strncmp("./", actuel->command[0], 2) == 0 || ft_strncmp("../", actuel->command[0], 3) == 0)
			{
				t_redir	*current;

				current = actuel->redir;
				while (current)
				{
					if (!ft_strcmp(current->redir, "<<"))
					{
						char	*line;
						char	*tmp;

						tmpp = open("/tmp/hd", O_CREAT | O_TRUNC | O_WRONLY, 0600);
						line = readline("> ");
						printf("c\n");
						while (line && ft_strcmp(line, current->arg))
						{
							write(tmpp, line, ft_strlen(line));
							write(tmpp, "\n", 1);
							tmp = line;
							line = readline("> ");
							free(tmp);
						}
						free(line);
						tmpp = open("/tmp/hd", O_RDONLY);
						unlink("/tmp/hd");
					}
					current = current->next;
				}
				if (opendir(actuel->command[0]))
				{
					all->exit_status = 126;
					printf("bash :%s : is a Directory \n", actuel->command[0]);
				}
				else 
				{
					g_signal.childpid = fork();
					if (!g_signal.childpid)
					{
						dup2(tmpp, STDIN_FILENO);
						if (execve(actuel->command[0], actuel->command, NULL) == -1)
							exit(errno);
					}
					waitpid(g_signal.childpid, &all->exit_status, 0);
					if (WEXITSTATUS(all->exit_status))
						all->exit_status = 1;
					else if (WIFEXITED(g_signal.childpid))
					{
						all->exit_status = 127;
						printf("%s\n", strerror(errno));
					}
				}
			}
			else
			{
				int		i;
				char	**path;
				char	*tmp;
				char	*command;
				int		fd;
				int		co = 0;
				t_redir	*current;

				current = actuel->redir;
				while (current)
				{
					if (!ft_strcmp(current->redir, "<<"))
					{
						char	*line;
						char	*tmp;

						tmpp = open("/tmp/hd", O_CREAT | O_TRUNC | O_WRONLY, 0600);
						line = readline("> ");
						printf("e\n");
						while (line && ft_strcmp(line, current->arg))
						{
							write(tmpp, line, ft_strlen(line));
							write(tmpp, "\n", 1);
							tmp = line;
							line = readline("> ");
							free(tmp);
						}
						free(line);
						tmpp = open("/tmp/hd", O_RDONLY);
						unlink("/tmp/hd");
					}
					current = current->next;
				}
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
							g_signal.childpid = fork();
							if (!g_signal.childpid)
							{
								dup2(tmpp, STDIN_FILENO);
								if (execve(command, actuel->command, NULL) == -1)
									exit (errno);
							}
							waitpid(g_signal.childpid, &all->exit_status, 0);
							if (WEXITSTATUS(all->exit_status))
								all->exit_status = 1;
							else if (WTERMSIG(all->exit_status))
								all->exit_status = 128 + WTERMSIG(all->exit_status);
							break ;
						}
					}				
					if (co == 0)
					{
						all->exit_status = 127;
						printf("bash: %s: command not found\n", actuel->command[0]);
					}
				}
			}
		}
		actuel = actuel->next;
	}
}
